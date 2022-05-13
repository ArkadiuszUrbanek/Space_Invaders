#include "state_scores.hpp"

#include <iostream>

static const sf::Color LightGray(0x44, 0x44, 0x44);
static const sf::Color Gray(0x22, 0x22, 0x22);

state_scores::state_scores(state_machine& machine, sf::RenderWindow& window) : 
	state_base(machine, window),
	m_array_of_records{ LightGray, Gray, LightGray, Gray, LightGray, Gray, LightGray, Gray, LightGray, Gray } {


	if (m_font.loadFromFile("fonts/PIXEARG_.TTF") == false) std::cout << "blad przy ladowaniu czcionki";

	m_scores.load_scores();
	m_scores.sort_scores_desc();

	m_number_of_records_on_the_last_page = m_scores.get_number_of_scores() % MAX_RECORDS_PER_PAGE;
	
	m_number_of_pages = m_scores.get_number_of_scores() / MAX_RECORDS_PER_PAGE;

	if (m_number_of_pages == 0) {
		m_number_of_pages++;

	} else if (m_number_of_pages != 0 && m_number_of_records_on_the_last_page == 0) {
		m_number_of_records_on_the_last_page = MAX_RECORDS_PER_PAGE;

	} else if (m_number_of_pages != 0 && m_number_of_records_on_the_last_page != 0) {
		m_number_of_pages++;

	}

	for (auto& rect : m_array_of_horizontal_rects) {
		rect.setFillColor(sf::Color::Black);
		rect.setSize({ RECORD_OUTLINE_THICKNESS / 2, MAX_RECORDS_PER_PAGE * 48 - (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2 });

	}

	m_array_of_headers[0].setString("Position");
	m_array_of_headers[1].setString("Nickname");
	m_array_of_headers[2].setString("Difficulty");
	m_array_of_headers[3].setString("Score");
	
	for (size_t index = 0; index < m_array_of_headers.size(); index++) {
		m_array_of_headers[index].setFont(m_font);
		m_array_of_headers[index].setFillColor(sf::Color::White);
		m_array_of_headers[index].setStyle(sf::Text::Bold);
		m_array_of_headers[index].setCharacterSize(24);

		if (index == 0) {
			m_array_of_headers[index].setPosition({ 50 / 2 + RECORD_OUTLINE_THICKNESS / 2 + 20.0f / 2, (game::m_WINDOW_HEIGHT - MAX_RECORDS_PER_PAGE * 48 + (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2) / 4 });

		} else {
			m_array_of_headers[index].setPosition({ m_array_of_headers[index - 1].getPosition().x + m_array_of_headers[index - 1].getLocalBounds().width + 20.0f + RECORD_OUTLINE_THICKNESS / 2, (game::m_WINDOW_HEIGHT - MAX_RECORDS_PER_PAGE * 48 + (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2) / 4 });

		}

		m_array_of_horizontal_rects[index].setPosition({ m_array_of_headers[index].getPosition().x - RECORD_OUTLINE_THICKNESS / 2 - 20.0f / 2,  (game::m_WINDOW_HEIGHT - MAX_RECORDS_PER_PAGE * 48 + (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2) / 2 });


	}


	float y_pos = 48 / 2 + (game::m_WINDOW_HEIGHT - MAX_RECORDS_PER_PAGE * 48 + (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2) / 2;
	for (auto& record : m_array_of_records) {
		record.set_position({game::m_WINDOW_WIDTH / 2, y_pos });
		y_pos = y_pos + record.get_size().y - RECORD_OUTLINE_THICKNESS / 2;

	}


	for (size_t row = 0; row < MAX_RECORDS_PER_PAGE; row++) {
		for (size_t column = 0; column < NUMBER_OF_HEADERS; column++) {
			m_matrix_of_textes[row][column].setFont(m_font);
			m_matrix_of_textes[row][column].setFillColor(sf::Color::White);
			m_matrix_of_textes[row][column].setCharacterSize(20);
			
			if (row < m_scores.get_number_of_scores()) {
				switch (column) {
					case 0: m_matrix_of_textes[row][column].setString(std::to_string(row + 1)); break;		
					case 1: m_matrix_of_textes[row][column].setString(std::get<0>(m_scores[row])); break;
					case 2: m_matrix_of_textes[row][column].setString(std::get<1>(m_scores[row])); break;
					case 3: m_matrix_of_textes[row][column].setString(std::to_string(std::get<2>(m_scores[row]))); break;

				}

			} else {
				m_matrix_of_textes[row][column].setString("");

			}

			m_matrix_of_textes[row][column].setOrigin({ 0.0f, m_matrix_of_textes[row][column].getLocalBounds().height / 2 });
			m_matrix_of_textes[row][column].setPosition({ m_array_of_headers[column].getPosition().x,  m_array_of_horizontal_rects[column].getPosition().y + (2 * row + 1) * (48 / 2 - RECORD_OUTLINE_THICKNESS / 2) + (row + 1) * (RECORD_OUTLINE_THICKNESS / 2) });

		}
	}
	

	m_number_of_page.setFont(m_font);
	m_number_of_page.setFillColor(sf::Color::White);
	m_number_of_page.setCharacterSize(20);

	std::string page_text= "Page 1 / ";
	page_text += std::to_string(m_number_of_pages);
	
	m_number_of_page.setString(page_text);
	m_number_of_page.setOrigin({ m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getLocalBounds().height / 2 });
	m_number_of_page.setPosition({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT - (game::m_WINDOW_HEIGHT - MAX_RECORDS_PER_PAGE * 48 + (MAX_RECORDS_PER_PAGE - 1) * RECORD_OUTLINE_THICKNESS / 2) / 4 });

	button widest_letter = button(m_font, "W", 20);

	for (auto& triangle : m_triangles) {
		triangle.setFillColor(sf::Color::White);
		triangle.setOutlineColor(sf::Color::White);
		triangle.setOutlineThickness(2);
		triangle.setPointCount(3);

	}

	sf::Vector2f m_single_letter_box_size = widest_letter.get_button_size();

	m_triangles[0].setPoint(0, { 0.0f, m_single_letter_box_size.y / 2 });
	m_triangles[0].setPoint(1, { m_single_letter_box_size.y, 0.0f });
	m_triangles[0].setPoint(2, { m_single_letter_box_size.y, m_single_letter_box_size.y });
	m_triangles[0].setOrigin({ m_single_letter_box_size.y / 2, m_single_letter_box_size.y / 2 });

	m_triangles[1].setPoint(0, { 0.0f, 0.0f });
	m_triangles[1].setPoint(1, { m_single_letter_box_size.y, m_single_letter_box_size.y / 2 });
	m_triangles[1].setPoint(2, { 0.0f, m_single_letter_box_size.y });
	m_triangles[1].setOrigin({ m_single_letter_box_size.y / 2, m_single_letter_box_size.y / 2 });

	m_triangles[0].setPosition({ m_number_of_page.getPosition().x - m_triangles[0].getOrigin().x - 10.0f - m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });
	m_triangles[1].setPosition({ m_number_of_page.getPosition().x + m_triangles[1].getOrigin().x + 10.0f + m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });

}

void state_scores::update_page_contents(size_t row_index) {
	for (size_t row = 0; row < MAX_RECORDS_PER_PAGE; row++) {
		for (size_t column = 0; column < NUMBER_OF_HEADERS; column++) {
			if (row_index < m_scores.get_number_of_scores()) {
				switch (column) {
					case 0: m_matrix_of_textes[row][column].setString(std::to_string(row_index + 1)); break;
					case 1: m_matrix_of_textes[row][column].setString(std::get<0>(m_scores[row_index])); break;
					case 2: m_matrix_of_textes[row][column].setString(std::get<1>(m_scores[row_index])); break;
					case 3: m_matrix_of_textes[row][column].setString(std::to_string(std::get<2>(m_scores[row_index]))); break;

				}

			} else {
				m_matrix_of_textes[row][column].setString("");

			}

			m_matrix_of_textes[row][column].setPosition({ m_array_of_headers[column].getPosition().x,  m_array_of_horizontal_rects[column].getPosition().y + (2 * row + 1) * (48 / 2 - RECORD_OUTLINE_THICKNESS / 2) + (row + 1) * (RECORD_OUTLINE_THICKNESS / 2) });

		}

		row_index++;
	}

}

void state_scores::poll_events() {
	if (m_window.pollEvent(m_event)) {
		switch (m_event.type) {
			case sf::Event::Closed: m_window.close(); break;

			case sf::Event::KeyReleased: switch (m_event.key.code) {
											case sf::Keyboard::Escape: m_machine.remove_state(); break;
											
											case sf::Keyboard::Left: { if (m_index_of_current_page == 0) {
																	 	m_index_of_current_page = m_number_of_pages - 1;
																	 
																	 
																	 } else {
																	 	m_index_of_current_page--;
																	 
																	 
																	 }
																	 
																	 std::string page_text = "Page ";
																	 page_text += std::to_string(m_index_of_current_page + 1);
																	 page_text += " / ";
																	 page_text += std::to_string(m_number_of_pages);

																	 m_number_of_page.setString(page_text);
																	 
																	 m_triangles[0].setPosition({ m_number_of_page.getPosition().x - m_triangles[0].getOrigin().x - 10.0f - m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });
																	 m_triangles[1].setPosition({ m_number_of_page.getPosition().x + m_triangles[1].getOrigin().x + 10.0f + m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });

																	 this->update_page_contents(m_index_of_current_page * MAX_RECORDS_PER_PAGE);

																	 break; }

											case sf::Keyboard::Right: { if (m_index_of_current_page == m_number_of_pages - 1) {
																	  	m_index_of_current_page = 0;
																	  
																	  
																	  } else {
																	  	m_index_of_current_page++;
																	  
																	  
																	  }
																	    
																	  std::string page_text = "Page ";
																	  page_text += std::to_string(m_index_of_current_page + 1);
																	  page_text += " / ";
																	  page_text += std::to_string(m_number_of_pages);
																	  
																	  m_number_of_page.setString(page_text);
																	  
																	  m_triangles[0].setPosition({ m_number_of_page.getPosition().x - m_triangles[0].getOrigin().x - 10.0f - m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });
																	  m_triangles[1].setPosition({ m_number_of_page.getPosition().x + m_triangles[1].getOrigin().x + 10.0f + m_number_of_page.getLocalBounds().width / 2, m_number_of_page.getPosition().y });

																	  this->update_page_contents(m_index_of_current_page * MAX_RECORDS_PER_PAGE);

																	  break; }
										 }
										 break;

		}
	}
}

void state_scores::update(sf::Time delta_time) {
	
}

void state_scores::render() {
    m_window.clear(sf::Color::Black);

	for (const auto& record : m_array_of_records) record.draw(m_window);

	for (const auto& rect : m_array_of_horizontal_rects) m_window.draw(rect);

	for (const auto& header : m_array_of_headers) m_window.draw(header);

	for (size_t row = 0; row < MAX_RECORDS_PER_PAGE; row++) {
		for (size_t column = 0; column < NUMBER_OF_HEADERS; column++) {
			m_window.draw(m_matrix_of_textes[row][column]);
		}
	}

	if (m_number_of_pages > 1) {
		for (const auto& triangle : m_triangles) m_window.draw(triangle);
	}

	m_window.draw(m_number_of_page);

    m_window.display();
}