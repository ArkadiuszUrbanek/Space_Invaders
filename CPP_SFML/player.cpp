#include "player.hpp"
#include "game.hpp"
#include "hud.hpp"

#include <iostream>
#include <cmath>

sf::Texture player::load_player_death_spritesheet() {
	sf::Texture texture;
	if (texture.loadFromFile("sprites/player_death_spritesheet.png") == false) std::cout << "Nie udalo sie wczytac tekstury wybuchajacego statku gracza.";

	return texture;
}

player::player(float speed, float acceleration, sf::Time time_interval_between_shots) : 
	collidable({ 48, 32 }), m_player_death_spritesheet(load_player_death_spritesheet()),
	m_player_death_animation(&m_player_death_spritesheet, { 2, 1 }, sf::seconds(0.5f)),
	m_max_speed(speed), m_acceleration(acceleration), m_time_interval_between_shots(time_interval_between_shots) {

	if (!m_player_texture.loadFromFile("sprites/player_texture.png")) {
		std::cout << "blad przy ladowaniu tekstury gracza";
	}

	m_sprite_top.setSize({ 12, 12 });
	m_sprite_bottom.setSize({ m_box.x, 20 });
	m_sprite_player_destroyed.setSize({ 48, 32 });

	m_sprite_top.setOrigin(m_sprite_top.getSize().x / 2, m_box.y / 2);
	m_sprite_bottom.setOrigin(m_sprite_bottom.getSize().x / 2, m_box.y / 2 - m_sprite_top.getSize().y);
	m_sprite_player_destroyed.setOrigin(m_sprite_player_destroyed.getSize().x / 2.0f, m_sprite_player_destroyed.getSize().y / 2.0f);

	m_sprite_top.setTexture(&m_player_texture);
	m_sprite_top.setTextureRect(sf::IntRect(4, 0, 3, 3));

	m_sprite_bottom.setTexture(&m_player_texture);
	m_sprite_bottom.setTextureRect(sf::IntRect(0, 3, 11, 5));

	m_sprite_player_destroyed.setTexture(&m_player_death_spritesheet);
	m_sprite_player_destroyed.setTextureRect(m_player_death_animation.get_image_rect());

}

void player::reset() {
	m_alive = true;

	m_death_timer_restarted = false;

	m_time_of_movement = sf::seconds(0.0f);

	m_stopped = true;
	m_moving_right = false;
	m_moving_left = false;

	m_shot_fired = false;

	this->set_position({ this->m_box.x / 2, game::m_WINDOW_HEIGHT - this->m_box.y / 2 - hud::m_HUD_BOTTOM_HEIGHT });
}

void player::respawn() {
	if (m_death_timer_restarted == false) {
		m_death_timer_restarted = true;
		m_death_timer.restart();

	}

	if (m_death_timer.getElapsedTime().asSeconds() >= 1.5f) {
		this->reset();

	}
	
}

void player::handle_input() {
	if (m_alive == true) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_moving_left == false) {
			m_moving_right = true;
			m_stopped = false;

		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_moving_right == false) {
			m_moving_left = true;
			m_stopped = false;

		} else {
			m_stopped = true;
			m_moving_right = false;
			m_moving_left = false;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_shot_clock.getElapsedTime() >= m_time_interval_between_shots) {
			m_shot_fired = true;
			m_shot_clock.restart();

		}
		else {
			m_shot_fired = false;

		}

	}
}

bool player::shot_fired() {
	if (m_shot_fired == true) {
		m_shot_fired = false;
		return true;

	} else {
		return false;

	}	
}

void player::update(sf::Time delta_time) {
	if (m_alive == true) {
		this->update_position(delta_time);

	} else {
		m_player_death_animation.update(0, delta_time);
		m_sprite_player_destroyed.setTextureRect(m_player_death_animation.get_image_rect());

	}
}

void player::update_position(sf::Time delta_time) {
	if (!m_stopped) {
		m_time_of_movement += delta_time;
		sf::Vector2f distance{ 0, 0 };

		if (m_time_to_reach_max_speed <= m_time_of_movement) {
			distance.x = -m_max_speed * delta_time.asSeconds();

		} else {
			distance.x = -0.5f * m_acceleration * m_time_of_movement.asSeconds() * m_time_of_movement.asSeconds();

		}

		if (m_moving_right == true) distance.x = abs(distance.x);

		m_sprite_top.move(distance);
		m_sprite_bottom.move(distance);

		if (this->get_position().x - this->m_box.x / 2 < 0) {
			this->set_position({ this->m_box.x / 2, game::m_WINDOW_HEIGHT - this->m_box.y / 2 - hud::m_HUD_BOTTOM_HEIGHT });
			m_time_of_movement = sf::seconds(0.0f);

		}

		if (this->get_position().x + this->m_box.x / 2 > game::m_WINDOW_WIDTH) {
			this->set_position({ game::m_WINDOW_WIDTH - this->m_box.x / 2, game::m_WINDOW_HEIGHT - this->m_box.y / 2 - hud::m_HUD_BOTTOM_HEIGHT });
			m_time_of_movement = sf::seconds(0.0f);

		}

	} else {
		m_time_of_movement = sf::seconds(0.0f);

	}

}

sf::Vector2f player::get_position() const {
	return m_sprite_top.getPosition();
}

sf::Vector2f player::get_gun_position() const {
	return { this->get_position().x, this->get_position().y - this->m_box.y / 2.0f };
}

void player::set_position(sf::Vector2f position) {
	m_sprite_bottom.setPosition({ position.x, position.y });
	m_sprite_top.setPosition({ position.x, position.y});

}

bool player::intruders_collision(const std::vector<sf::FloatRect>& collsion_boxes) {
	for (size_t index = 0; index < collsion_boxes.size(); index++) {
		if (m_sprite_top.getGlobalBounds().intersects(collsion_boxes[index]) || m_sprite_bottom.getGlobalBounds().intersects(collsion_boxes[index])) {
			m_sprite_player_destroyed.setPosition(this->get_position());
			m_alive = false;
			return true;
		}
	}

	return false;
}

bool player::projectile_collision(const projectile& enemy_projectile) {
	if (m_sprite_top.getGlobalBounds().intersects(enemy_projectile.get_global_bounds()) || m_sprite_bottom.getGlobalBounds().intersects(enemy_projectile.get_global_bounds())) {
		m_sprite_player_destroyed.setPosition(this->get_position());
		m_alive = false;
		return true;

	} else {
		return false;

	}

}

void player::draw(sf::RenderWindow& window) const {
	if (m_alive == true) {
		window.draw(m_sprite_top);
		window.draw(m_sprite_bottom);

	} else {
		window.draw(m_sprite_player_destroyed);

	}
}
