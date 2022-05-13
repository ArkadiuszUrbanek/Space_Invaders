#include "intruder_manager.hpp"
#include "game.hpp"
#include "hud.hpp"

#include <iostream>
#include <random>
#include <chrono>

#define GAP 10.0f

std::array<sf::Texture, 3> intruder_manager::load_textures() {
	std::array<sf::Texture, 3> textures;

	if (textures[0].loadFromFile("sprites/invader_squid_spritesheet.png") == false) std::cout << "Nie udalo sie wczytac tekstury intrudera typu squid. ";
	if (textures[1].loadFromFile("sprites/invader_crab_spritesheet.png") == false) std::cout << "Nie udalo sie wczytac tekstury intrudera typu crab. ";
	if (textures[2].loadFromFile("sprites/invader_octopus_spritesheet.png") == false) std::cout << "Nie udalo sie wczytac tekstury intrudera typu octopus. ";

	return textures;

}

void intruder_manager::update_step_gap() {
	m_step_gap = sf::seconds((float)m_number_of_enemies_alive / m_default_number_of_enemies_alive * m_default_step_gap.asSeconds());
}

intruder_manager::intruder_manager(sf::Time step_gap, sf::Time time_interval_between_shots) : 
	m_intruders_textures(load_textures()),
	m_default_step_gap(step_gap),
	m_default_time_interval_between_shots(time_interval_between_shots),
	m_intruders_animations{ animation(&m_intruders_textures[0], {2, 1}, sf::seconds(0.0f)) ,  animation(&m_intruders_textures[1], {2, 1}, sf::seconds(0.0f)) ,  animation(&m_intruders_textures[2], {2, 1}, sf::seconds(0.0f)) } {

	m_index_of_lowest_living_row = INTRUDER_ROWS - 1;
	for (char index = 0; index <= m_index_of_lowest_living_row; index++) m_number_of_living_intruders_in_row[index] = INTRUDER_COLUMNS;

	for (size_t i = 0; i < INTRUDER_ROWS; i++) {
		float current_x_pos = game::m_WINDOW_WIDTH - 3 - ((INTRUDER_COLUMNS - 1) * GAP + (INTRUDER_COLUMNS - 1) * 48.0f + 48.0f / 2.0f);
		float current_y_pos = 35.0f + hud::m_HUD_TOP_HEIGHT + 32.0f / 2 + GAP + i * (32.0f + GAP); //35.0f

		std::vector<intruder> temp;

		for (size_t j = 0; j < INTRUDER_COLUMNS; j++) {
			switch (i) {
			case 0: case 1: temp.emplace_back(&m_intruders_textures[0], intruder::intruder_type::SQUID);
				temp[j].update_texture_rect(m_intruders_animations[0].get_image_rect());
				break;

			case 2: case 3: temp.emplace_back(&m_intruders_textures[1], intruder::intruder_type::CRAB);
				temp[j].update_texture_rect(m_intruders_animations[1].get_image_rect());
				break;

			case 4: case 5: temp.emplace_back(&m_intruders_textures[2], intruder::intruder_type::OCTOPUS);
				temp[j].update_texture_rect(m_intruders_animations[2].get_image_rect());
				break;

			}

			temp[j].set_position({ current_x_pos, current_y_pos });
			current_x_pos = current_x_pos + 48.0f + GAP;

		}

		m_intruders_matrix.push_back(temp);
	}
}

unsigned int intruder_manager::return_points(){
	if (m_points_returned == false) {
		m_points_returned = true;
		return m_points;

	} else {
		return 0;

	}
}

void intruder_manager::reset() {
	m_index_of_lowest_living_row = INTRUDER_ROWS - 1;
	for (char index = 0; index <= m_index_of_lowest_living_row; index++) m_number_of_living_intruders_in_row[index] = INTRUDER_COLUMNS;

	for (auto& index : m_intruders_animations) index.reset(0);

	m_points_returned = true;
	m_detach_intruder = true;
	m_group_moving_left = true;
	m_group_moving_down = false;

	m_points = 0;

	m_step_gap = m_default_step_gap;
	m_time_interval_between_shots = m_default_time_interval_between_shots;

	m_number_of_enemies_alive = m_default_number_of_enemies_alive;
	m_number_of_enemies_alive_in_group = m_default_number_of_enemies_alive;

	for (size_t row = 0; row < INTRUDER_ROWS; row++) {
		float current_x_pos = game::m_WINDOW_WIDTH - 3 - ((INTRUDER_COLUMNS - 1) * GAP + (INTRUDER_COLUMNS - 1) * 48.0f + 48.0f / 2.0f);
		float current_y_pos = 35.0f + hud::m_HUD_TOP_HEIGHT + 32.0f / 2 + GAP + row * (32.0f + GAP);

		for (size_t column = 0; column < INTRUDER_COLUMNS; column++) {
			m_intruders_matrix[row][column].reset();
			m_intruders_matrix[row][column].set_position({ current_x_pos, current_y_pos });

			switch (m_intruders_matrix[row][column].get_intruder_type()) {
				case intruder::intruder_type::SQUID: m_intruders_matrix[row][column].update_texture_rect(m_intruders_animations[0].get_image_rect()); break;
				case intruder::intruder_type::CRAB: m_intruders_matrix[row][column].update_texture_rect(m_intruders_animations[1].get_image_rect()); break;
				case intruder::intruder_type::OCTOPUS: m_intruders_matrix[row][column].update_texture_rect(m_intruders_animations[2].get_image_rect()); break;
			}

			current_x_pos = current_x_pos + 48.0f + GAP;
		}

	}

	m_step_clock.restart();
	m_intruders_shot_clock.restart();
	
}

template<typename T>
const T& intruder_manager::get_number_in_range(T low, T high) const {
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<T> distribution(low, high);
	return distribution(generator);
}

template const unsigned short& intruder_manager::get_number_in_range(unsigned short low, unsigned short high) const;

bool intruder_manager::test_intruder_position(const intruder& intruder) const {
	if (intruder.is_detached() == false) {
		return (intruder.get_position().x - intruder.get_box().x / 2 < 6 && m_group_moving_left) || (intruder.get_position().x + intruder.get_box().x / 2 > game::m_WINDOW_WIDTH - 6 && !m_group_moving_left);

	} else {
		return (intruder.get_position().x - intruder.get_box().x / 2 < 6 && intruder.is_moving_left() == true) || (intruder.get_position().x + intruder.get_box().x / 2 > game::m_WINDOW_WIDTH - 6 && intruder.is_moving_left() == false);

	}
}

void intruder_manager::update() {
	if (m_step_clock.getElapsedTime() > m_step_gap) {
		for (auto& index : m_intruders_animations) index.force_update(0);
		
		if (m_detach_intruder == true) {
			if (m_number_of_living_intruders_in_row[m_index_of_lowest_living_row] > 0) {

				size_t number_draw = get_number_in_range((unsigned short)1, m_number_of_living_intruders_in_row[m_index_of_lowest_living_row]);

				for (size_t column_index = 0, alive_counter = 0; column_index < INTRUDER_COLUMNS; column_index++) {
					if (m_intruders_matrix[m_index_of_lowest_living_row][column_index].is_alive() == true) alive_counter++;

					if (alive_counter == number_draw) {
						m_intruders_matrix[m_index_of_lowest_living_row][column_index].detach();

						if (m_group_moving_left == true) m_intruders_matrix[m_index_of_lowest_living_row][column_index].set_moving_left();
						else m_intruders_matrix[m_index_of_lowest_living_row][column_index].set_moving_right();

						m_number_of_living_intruders_in_row[m_index_of_lowest_living_row]--;
						m_number_of_enemies_alive_in_group--;

						break;
					}

				}

			}

			m_detach_intruder = false;

		}

		bool move_group_down = false;
		float x_step = m_group_moving_left ? -10.0f : 10.0f;

		for (auto& row : m_intruders_matrix) {
			for (auto& column : row) {
				if (column.is_alive() == true) {
					switch (column.get_intruder_type()) {
						case intruder::intruder_type::SQUID: column.update_texture_rect(m_intruders_animations[0].get_image_rect()); break;
						case intruder::intruder_type::CRAB: column.update_texture_rect(m_intruders_animations[1].get_image_rect()); break;
						case intruder::intruder_type::OCTOPUS: column.update_texture_rect(m_intruders_animations[2].get_image_rect()); break;
					}

					
					if (m_group_moving_down == false) {
						if (column.is_detached() == false) {
							column.move({ x_step, 0.0f });

						} else {
							column.move_detached({ x_step, 0.0f });

							if (m_number_of_enemies_alive_in_group != 0) {
								if (test_intruder_position(column) == true) column.switch_moving_direction();

							} 

						}

					}
					
					if (m_number_of_enemies_alive_in_group != 0) {
						if (m_group_moving_down == true) {
							column.move({ 0, 32.0f / 2.0f });
					
						} else if (move_group_down == false && column.is_detached() == false) { 
							move_group_down = test_intruder_position(column);
					
						}

					} else {
						if (m_group_moving_down == true) {
							column.move({ 0, 32.0f / 2.0f });

						} else if (move_group_down == false && column.is_detached() == true) { 
							if(move_group_down = test_intruder_position(column) == true) column.switch_moving_direction();

						}

					}

				}
			}
		}

		m_group_moving_down = move_group_down;
		if (m_group_moving_down == true) m_group_moving_left = !m_group_moving_left;

		m_step_clock.restart();
	}
	
}

bool intruder_manager::projectile_collision(const projectile& projectile) {
	bool collision_detected = false;

	for (int row = INTRUDER_ROWS - 1; row >= 0; row--) {
		for (size_t column = 0; column < INTRUDER_COLUMNS; column++) {
			if (m_intruders_matrix[row][column].projectile_collision(projectile) == true) {
				if (m_intruders_matrix[row][column].is_detached() == false) {
					m_number_of_living_intruders_in_row[row]--;
					m_number_of_enemies_alive_in_group--;
				}

				m_number_of_enemies_alive--;
				update_step_gap();
				collision_detected = true;

				m_points_returned = false;
				m_points = m_intruders_matrix[row][column].return_points();

				break;

			} 

		}

		if (m_number_of_living_intruders_in_row[row] == 0 && m_index_of_lowest_living_row == row) {
			if (m_index_of_lowest_living_row != 0) {
				m_index_of_lowest_living_row--;
				m_detach_intruder = true;
			}

		} else if (collision_detected == true) {
			break;

		}

	}

	return collision_detected;
}

const std::vector<sf::FloatRect> intruder_manager::get_collision_boxes() const {
	const intruder* intruder_ptr_1 = nullptr, * intruder_ptr_2 = nullptr;
	std::vector<sf::FloatRect> collision_boxes;

	for (size_t column = 0; column < INTRUDER_COLUMNS; column++) {
		for (size_t row = 0; row < INTRUDER_ROWS; row++) {
			if (m_intruders_matrix[row][column].is_alive() == true) {
				if (m_intruders_matrix[row][column].is_detached() == false) {
					if (intruder_ptr_1 == nullptr) intruder_ptr_1 = &m_intruders_matrix[row][column];
					else intruder_ptr_2 = &m_intruders_matrix[row][column];

				} else {
					sf::FloatRect rect;

					rect.left = m_intruders_matrix[row][column].get_position().x - m_intruders_matrix[row][column].get_box().x / 2;
					rect.top = m_intruders_matrix[row][column].get_position().y - m_intruders_matrix[row][column].get_box().y / 2;

					rect.width = m_intruders_matrix[row][column].get_box().x;
					rect.height = m_intruders_matrix[row][column].get_box().y;

					collision_boxes.emplace_back(rect);

				}
			}

		}

		if (intruder_ptr_1 != nullptr) {
			if (intruder_ptr_2 == nullptr) intruder_ptr_2 = intruder_ptr_1;

			sf::FloatRect rect;

			rect.left = intruder_ptr_1->get_position().x - intruder_ptr_1->get_box().x / 2;
			rect.top = intruder_ptr_1->get_position().y - intruder_ptr_1->get_box().y / 2;

			rect.width = intruder_ptr_2->get_position().x + intruder_ptr_2->get_box().x / 2 - rect.left;
			rect.height = intruder_ptr_2->get_position().y + intruder_ptr_2->get_box().y / 2 - rect.top;

			collision_boxes.emplace_back(rect);

			intruder_ptr_1 = nullptr;
			intruder_ptr_2 = nullptr;

		}
	
	}

	return collision_boxes;
}

sf::Vector2f intruder_manager::get_shooter_position() {
	m_time_interval_between_shots = sf::seconds((float)m_number_of_enemies_alive / m_default_number_of_enemies_alive * m_default_time_interval_between_shots.asSeconds());
	if (m_time_interval_between_shots < sf::seconds(0.5f)) m_time_interval_between_shots = sf::seconds(0.5f);

	if (m_intruders_shot_clock.getElapsedTime() < m_time_interval_between_shots) return { -1.0f, -1.0f };
	else m_intruders_shot_clock.restart();

	if(m_number_of_enemies_alive == 0) return { -1.0f, -1.0f };

	sf::Vector2f position = { -1.0f, -1.0f };

	if (m_number_of_enemies_alive_in_group > 0 && m_number_of_enemies_alive == m_number_of_enemies_alive_in_group) { //jezeli zyja jakies w grupie i nie zyja zadne odlaczone
		size_t number_draw = get_number_in_range((unsigned short)1, m_number_of_living_intruders_in_row[m_index_of_lowest_living_row]);

		for (size_t column_index = 0, alive_counter = 0; column_index < INTRUDER_COLUMNS; column_index++) {
			if (m_intruders_matrix[m_index_of_lowest_living_row][column_index].is_alive() == true) alive_counter++;

			if (alive_counter == number_draw) {
				position = m_intruders_matrix[m_index_of_lowest_living_row][column_index].get_position();
				position.y += m_intruders_matrix[m_index_of_lowest_living_row][column_index].get_box().y / 2;
				
				return position;
			}

		}

	} else {
		for (const auto& row : m_intruders_matrix) {
			for (const auto& column : row) {
				if (column.is_detached() == true && column.is_alive() == true) {
					if (position.y < column.get_position().y) {
						position = column.get_position();
						position.y += column.get_box().y / 2;

					}
				}
			}
		}

		return position;
	}

}

void intruder_manager::draw(sf::RenderWindow& window) const {
	for (const auto& row : m_intruders_matrix) {
		for (const auto& column : row) {
			if(column.is_alive() == true) column.draw(window);
		}
	}
}