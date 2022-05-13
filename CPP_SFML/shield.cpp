#include "shield.hpp"

#include <iostream>

shield::shield() : collidable({ 112, 84 }) {
	if (!m_square_texture.loadFromFile("sprites/shield_square.png")) {
		std::cout << "blad przy ladowaniu tekstury kwadratu oslony";
	}

	if (!m_triangle_texture.loadFromFile("sprites/shield_triangle.png")) {
		std::cout << "blad przy ladowaniu tekstury trojkata oslony";
	}

	sf::RectangleShape square, triangle;

	square.setSize({ m_box.x / 4, m_box.y / 3 });
	triangle.setSize({ m_box.x / 4, m_box.y / 3 });

	square.setOrigin({ square.getSize().x / 2, square.getSize().y / 2 });
	triangle.setOrigin({ square.getSize().x / 2, square.getSize().y / 2 });

	square.setTexture(&m_square_texture);
	triangle.setTexture(&m_triangle_texture);

	

	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {
			m_array_of_shield_sections[row][column].m_destroyed = false;
			
			if (row == 0 && column == 0) {
				m_array_of_shield_sections[row][column].m_style = section_style::slope_0;
				m_array_of_shield_sections[row][column].m_sprite = triangle;

			} else if (row == 0 && column == 3) {
				m_array_of_shield_sections[row][column].m_style = section_style::slope_90;
				m_array_of_shield_sections[row][column].m_sprite = triangle;
				m_array_of_shield_sections[row][column].m_sprite.setRotation(90.0f);

			} else if (row == 2 && column == 1) {
				m_array_of_shield_sections[row][column].m_style = section_style::slope_180;
				m_array_of_shield_sections[row][column].m_sprite = triangle;
				m_array_of_shield_sections[row][column].m_sprite.setRotation(180.0f);

			} else if (row == 2 && column == 2) {
				m_array_of_shield_sections[row][column].m_style = section_style::slope_270;
				m_array_of_shield_sections[row][column].m_sprite = triangle;
				m_array_of_shield_sections[row][column].m_sprite.setRotation(270.0f);

			} else {
				m_array_of_shield_sections[row][column].m_style = section_style::square;
				m_array_of_shield_sections[row][column].m_sprite = square;

			}

		}

	}

}

void shield::reset() {
	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {
			m_array_of_shield_sections[row][column].m_destroyed = false;
		}
	}
}

void shield::set_position(sf::Vector2f position) {
	sf::Vector2f position_to_set = { position.x - m_box.x / 2 + m_box.x / 8, position.y - m_box.y / 2 + m_box.y / 6 };

	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {
			m_array_of_shield_sections[row][column].m_sprite.setPosition(position_to_set);
			position_to_set.x += m_box.x / 4;

		}
		position_to_set.x -= m_box.x;
		position_to_set.y += m_box.y / 3;

	}

}

void shield::draw(sf::RenderWindow& window) const {
	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {
			if (m_array_of_shield_sections[row][column].m_destroyed == false) {
				window.draw(m_array_of_shield_sections[row][column].m_sprite);

			}

		}

	}

}

void shield::intruders_collision(const std::vector<sf::FloatRect>& collsion_boxes) {
	sf::FloatRect section_rect;
	section_rect.width = m_box.x / 4;
	section_rect.height = m_box.y / 3;

	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {
			if (m_array_of_shield_sections[row][column].m_destroyed == false) {
				section_rect.left = m_array_of_shield_sections[row][column].m_sprite.getPosition().x - m_box.x / 8;
				section_rect.top = m_array_of_shield_sections[row][column].m_sprite.getPosition().y - m_box.y / 6;

				for (size_t index = 0; index < collsion_boxes.size(); index++) {
					if (section_rect.intersects(collsion_boxes[index])) {
						m_array_of_shield_sections[row][column].m_destroyed = true;
						break;
					}
				}

			}

		}

	}

}

void shield::projectile_collision(projectile& projectile) {
	sf::FloatRect section_rect;
	section_rect.width = m_box.x / 4;
	section_rect.height = m_box.y / 3;

	sf::Vector2f projectile_point_A { projectile.get_position().x - projectile.get_box().x / 2, projectile.get_position().y };
	sf::Vector2f projectile_point_B { projectile.get_position().x + projectile.get_box().x / 2, projectile.get_position().y };

	for (unsigned int row = 0; row < m_TOTAL_NUMBER_OF_ROWS; row++) {
		for (unsigned int column = 0; column < m_TOTAL_NUMBER_OF_COLUMNS; column++) {

			if (m_array_of_shield_sections[row][column].m_destroyed == false) {

				section_rect.left = m_array_of_shield_sections[row][column].m_sprite.getPosition().x - m_box.x / 8;
				section_rect.top = m_array_of_shield_sections[row][column].m_sprite.getPosition().y - m_box.y / 6;

				if (section_rect.contains(projectile_point_A) == true || section_rect.contains(projectile_point_B) == true) {
					switch (m_array_of_shield_sections[row][column].m_style) {
					case section_style::square: m_array_of_shield_sections[row][column].m_destroyed = true;
												projectile.destroy();
												break;

					case section_style::slope_0: if (projectile_point_B.y >= -projectile_point_B.x + section_rect.top + m_array_of_shield_sections[row][column].m_sprite.getSize().y + section_rect.left) {
												 m_array_of_shield_sections[row][column].m_destroyed = true;
												 projectile.destroy();
												 }
												 
												 break;

					case section_style::slope_90: if (projectile_point_A.y >= projectile_point_A.x + section_rect.top - section_rect.left) {
												  m_array_of_shield_sections[row][column].m_destroyed = true;
												  projectile.destroy();
												  }
												  
												  break;

					case section_style::slope_180: if (projectile_point_A.y <= -projectile_point_A.x + section_rect.top + m_array_of_shield_sections[row][column].m_sprite.getSize().y + section_rect.left) {
												   m_array_of_shield_sections[row][column].m_destroyed = true;
												   projectile.destroy();
												   }
												   
												   break;

					case section_style::slope_270: if (projectile_point_B.y <= projectile_point_B.x + section_rect.top - section_rect.left) {
												   m_array_of_shield_sections[row][column].m_destroyed = true;
												   projectile.destroy();
												   }
												   
												   break;

					}

				}

			}

		}

	}

}
