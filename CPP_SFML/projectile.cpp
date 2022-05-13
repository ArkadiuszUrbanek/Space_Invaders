#include "projectile.hpp"

#include <iostream>
#include <cmath>

//#include <cstdlib>
//#include <ctime>

projectile::projectile(sf::Vector2f position, float speed) : collidable({ 4, 12 }), m_speed(speed) {
	if (!m_projectile_texture.loadFromFile("sprites/projectile_texture.png")) {
		std::cout << "blad przy ladowaniu tekstury pocisku";
	}
	
	m_sprite.setSize({ m_box.x, m_box.y });

	//m_speed < 0 ? m_moving_up = true : m_moving_up = false;

	m_moving_up = m_speed < 0;

	if (m_moving_up == true) {
		m_sprite.setOrigin(m_sprite.getSize().x / 2.0f, 0.0f);
		m_sprite.setPosition({ position.x, position.y - m_box.y });

	} else {
		m_sprite.setOrigin(m_sprite.getSize().x / 2.0f, m_sprite.getSize().y);
		m_sprite.setPosition({ position.x, position.y + m_box.y });

	}

	m_sprite.setTexture(&m_projectile_texture);


	//m_sprite.setFillColor(sf::Color::Magenta);
	
}


void projectile::update_position(sf::Time delta_time) {
	sf::Vector2f distance{ 0, 0 };

	distance.y = m_speed * delta_time.asSeconds();

	m_sprite.move(distance);
}

void projectile::set_position(sf::Vector2f position) {
	if (this->m_moving_up == true) {
		m_sprite.setPosition({ position.x, position.y - m_box.y });

	} else {
		m_sprite.setPosition({ position.x, position.y + m_box.y });

	}

}

sf::Vector2f projectile::get_position() const {
	return m_sprite.getPosition();
}

bool projectile::projectile_collision(const projectile& other_projectile) {
	if (m_sprite.getGlobalBounds().intersects(other_projectile.m_sprite.getGlobalBounds())) {
		this->m_destroyed = true;
		return true;
	}
}

void projectile::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}
