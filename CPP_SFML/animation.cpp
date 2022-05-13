#include "animation.hpp"

animation::animation(sf::Texture* texture, sf::Vector2u image_count, sf::Time switch_time) : m_image_count(image_count), m_switch_time(switch_time), m_total_time(sf::seconds(0.0f)), m_current_image({ 0, 0 }) {

	m_image_rect.width = texture->getSize().x / float(m_image_count.x);
	m_image_rect.height = texture->getSize().y / float(m_image_count.y);
}

void animation::update(int row, sf::Time delta_time) {
	m_current_image.y = row;
	m_total_time += delta_time;

	if (m_total_time >= m_switch_time) {
		m_total_time -= m_switch_time;
		m_current_image.x++;

		if (m_current_image.x >= m_image_count.x) m_current_image.x = 0;


	}

	m_image_rect.left = m_current_image.x * m_image_rect.width;
	m_image_rect.top = m_current_image.y * m_image_rect.height;

}

void animation::force_update(int row) {
	m_current_image.y = row;
	m_current_image.x++;

	if (m_current_image.x >= m_image_count.x) m_current_image.x = 0;

	m_image_rect.left = m_current_image.x * m_image_rect.width;
	m_image_rect.top = m_current_image.y * m_image_rect.height;

}

void animation::reset(int row) {
	m_current_image.y = row;
	m_current_image.x = 0;

	m_image_rect.left = 0;
	m_image_rect.top = m_current_image.y * m_image_rect.height;
}