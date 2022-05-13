#include "intruder.hpp"

#include <cmath>
#include <iostream>

intruder::intruder(sf::Texture* texture, intruder_type intruder_type) : collidable({ (float)texture->getSize().x * 2, (float)texture->getSize().y * 4 }), m_intruder_type(intruder_type) {
	m_sprite.setSize({ m_box.x, m_box.y });
	m_sprite.setOrigin(m_box.x / 2, m_box.y / 2);

	m_sprite.setTexture(texture);

}

void intruder::reset() {
	m_alive = true;
	m_detached = false;

}

unsigned int intruder::return_points() {
	return static_cast<unsigned int>(m_intruder_type);
}

void intruder::update_texture_rect(const sf::IntRect& rect) {
	m_sprite.setTextureRect(rect);

}

void intruder::set_position(sf::Vector2f position) {
	m_sprite.setPosition(position);
}

void intruder::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

void intruder::move(sf::Vector2f distance) {
	m_sprite.move(distance);

}

void intruder::move_detached(sf::Vector2f distance) {
	switch (m_detached_intruder_state) {
		case intruder::detached_intruder_state::FIRST_PHASE: m_sprite.move(distance);
															 m_sprite.move({ 0.0f, 21.0f });
															 m_detached_intruder_state = intruder::detached_intruder_state::SECOND_PHASE;
															 break;

		case intruder::detached_intruder_state::SECOND_PHASE: m_sprite.move(distance);
															  m_sprite.move({ 0.0f, 21.0f});
															  m_detached_intruder_state = intruder::detached_intruder_state::THIRD_PHASE;
															  break;

		case intruder::detached_intruder_state::THIRD_PHASE: distance.x = std::abs(distance.x);
															 distance.y = std::abs(distance.y);

															 if (m_moving_left == true) distance.x = -distance.x;
															 m_sprite.move(distance);
															 break;

	}
		
}


bool intruder::projectile_collision(const projectile& projectile) {
	if (m_alive == true) {
		if (m_sprite.getGlobalBounds().contains({ projectile.get_position().x - projectile.get_box().x / 2, projectile.get_position().y }) || m_sprite.getGlobalBounds().contains({ projectile.get_position().x + projectile.get_box().x / 2, projectile.get_position().y })) {
			m_alive = false;
			return true;		
		}
	}
}