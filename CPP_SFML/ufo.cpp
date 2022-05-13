#include "ufo.hpp"
#include "hud.hpp"

#include <iostream>
#include <cmath>

sf::Texture ufo::load_ufo_spritesheet() {
	sf::Texture texture;

	if (!texture.loadFromFile("sprites/ufo_spritesheet.png")) std::cout << "blad przy ladowaniu tekstury ufo";

	return texture;
}

ufo::ufo() : collidable({ 70, 35 }), m_ufo_spritesheet(load_ufo_spritesheet()), m_animation(&m_ufo_spritesheet, { 5, 1 }, sf::seconds(0.1f)) { //56 28 //70, 35
	m_sprite.setSize({ m_box.x, m_box.y });
	m_sprite.setOrigin(m_box.x / 2, m_box.y / 2);

	m_sprite.setTexture(&m_ufo_spritesheet);
}

void ufo::update_position(sf::Time delta_time) {
	sf::Vector2f distance{ 0, 0 };

	distance.x = -m_speed * delta_time.asSeconds();

	if (this->m_moving_right == true) distance.x = abs(distance.x);

	m_sprite.move(distance);

}

void ufo::reset() {
	m_moving_right = false;
	m_points_returned = true;
	m_speed = m_default_speed;
	m_state = ufo_state::WAITING;
	m_time_of_movement = sf::seconds(0.0f);
	m_currrent_time_interval_between_appearances = m_default_time_interval_between_appearances;

}

unsigned int ufo::return_points() {
	if ((m_state == ufo_state::DESTROYED || m_state == ufo_state::WAITING) && m_points_returned == false) {
		return m_points;
		m_points_returned = true;

	} else {
		return 0;

	}

}

void ufo::update(sf::Time delta_time) {
	m_time_of_movement += delta_time;

	switch (m_state) {
	case ufo_state::DESTROYED: m_state = ufo_state::WAITING;

								if (m_moving_right == true) m_moving_right = false;
								else m_moving_right = true;
								break;

	case ufo_state::ALIVE: update_position(delta_time);
							
							m_animation.update(0, delta_time);
							m_sprite.setTextureRect(m_animation.get_image_rect());

							if (m_time_of_movement >= m_min_time_interval_between_appearances) {
								if (m_moving_right == false && m_sprite.getPosition().x + m_box.x / 2  <= 0 || m_moving_right == true && m_sprite.getPosition().x - m_box.x / 2 >= game::m_WINDOW_WIDTH) m_state = ufo_state::DESTROYED;
							}

							break;

	case ufo_state::WAITING: if (m_time_of_movement >= m_currrent_time_interval_between_appearances) {
								 m_time_of_movement = sf::seconds(0.0f);
							 	 
							 	 m_state = ufo_state::ALIVE;
							 	 if (m_moving_right == false) this->set_position({ game::m_WINDOW_WIDTH + this->m_box.x / 2, m_box.y / 2 + hud::m_HUD_TOP_HEIGHT });
							 	 else this->set_position({ -this->m_box.x / 2, m_box.y / 2 + hud::m_HUD_TOP_HEIGHT });
							 
							 }
							 break;

	}

}

bool ufo::projectile_collision(const projectile& projectile) {
	if (m_state == ufo_state::ALIVE && m_sprite.getGlobalBounds().contains(projectile.get_position()) == true) {
		m_state = ufo_state::DESTROYED;
		m_points_returned = false;
		return true;

	} else {
		return false;

	}
}

void ufo::set_position(sf::Vector2f position) {
	m_sprite.setPosition(position);
}

void ufo::draw(sf::RenderWindow& window) const {
	if (m_state == ufo_state::ALIVE) {
		window.draw(m_sprite);
	}
}
