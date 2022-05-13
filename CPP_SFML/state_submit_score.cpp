#include "state_submit_score.hpp"
#include "difficulty_settings.hpp"
#include "state_playing.hpp"
#include "scores.hpp"
#include "game.hpp"

#include <iostream>

#define GAP 5.0f

sf::Font state_submit_score::load_font() {
	sf::Font font;
	if (font.loadFromFile("fonts/PIXEARG_.TTF") == false) std::cout << "blad przy ladowaniu czcionki";

	return font;
}

state_submit_score::state_submit_score(state_machine& machine, sf::RenderWindow& window) : state_base(machine, window), m_font(load_font()), m_nickname_letters{ 'A', 'A', 'A' } {

	button widest_letter = button(m_font, "W", 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Blue);
	
	for (auto& triangle : m_triangles) {
		triangle.setFillColor(sf::Color::Black);
		triangle.setOutlineColor(sf::Color::White);
		triangle.setOutlineThickness(3);
		triangle.setPointCount(3);
		
	}

	m_single_letter_box_size = widest_letter.get_button_size();

	m_triangles[0].setPoint(0, { m_single_letter_box_size.x / 2, 0.0f });
	m_triangles[0].setPoint(1, { 0.0f, m_single_letter_box_size.x });
	m_triangles[0].setPoint(2, { m_single_letter_box_size.x, m_single_letter_box_size.x });
	m_triangles[0].setOrigin({ m_single_letter_box_size.x / 2, m_single_letter_box_size.x / 2 });
	
	m_triangles[1].setPoint(0, { 0.0f, 0.0f });
	m_triangles[1].setPoint(1, { m_single_letter_box_size.x, 0.0f });
	m_triangles[1].setPoint(2, { m_single_letter_box_size.x / 2, m_single_letter_box_size.x });
	m_triangles[1].setOrigin({ m_single_letter_box_size.x / 2, m_single_letter_box_size.x / 2 });

	m_score_button = button(m_font, 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	std::string info_text = "Your final score is: " + std::to_string(state_playing::get_player_score());
	m_score_button.set_button_text(info_text);
	m_score_button.set_button_position({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 - m_score_button.get_button_size().y / 2 - 100.0f});


	m_game_over_button = button(m_font, 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_game_over_button.set_button_text("Game over!");
	m_game_over_button.set_button_position({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 - m_score_button.get_button_size().y - m_game_over_button.get_button_size().y / 2 - GAP - 100.0f });


	m_enter_nickname_button = button(m_font, 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_enter_nickname_button.set_button_text("Enter your nickname");
	m_enter_nickname_button.set_button_position({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 });


	for (size_t index = 0; index < m_letter_buttons.size(); index++) {
		m_letter_buttons[index] = button(m_font, "A", 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
		m_letter_buttons[index].set_button_position({ game::m_WINDOW_WIDTH / 2 - 2 * GAP - m_single_letter_box_size.x + index * m_single_letter_box_size.x + index * 2 * GAP, m_enter_nickname_button.get_button_position().y + m_enter_nickname_button.get_button_size().y / 2 + m_single_letter_box_size.x + 4 * GAP + m_single_letter_box_size.y / 2 });

	}

	m_triangles[0].setPosition({ m_letter_buttons[0].get_button_position().x,  m_letter_buttons[0].get_button_position().y - 2 * GAP - m_single_letter_box_size.y / 2 - m_single_letter_box_size.x / 2 });
	m_triangles[1].setPosition({ m_letter_buttons[0].get_button_position().x,  m_letter_buttons[0].get_button_position().y + 2 * GAP + m_single_letter_box_size.y / 2 + m_single_letter_box_size.x / 2 });

}

void state_submit_score::poll_events() {
	if (m_window.pollEvent(m_event)) {
		switch (m_event.type) {
			case sf::Event::Closed: m_window.close(); break;

			case sf::Event::KeyReleased: switch (m_event.key.code) {
											case sf::Keyboard::Up: { if (m_nickname_letters[m_selected_nickname_letter_index] == 'A') {
																		m_nickname_letters[m_selected_nickname_letter_index] = 'Z';

																	} else {
																		m_nickname_letters[m_selected_nickname_letter_index]--;

																	}
																	
																    std::string letter(1, m_nickname_letters[m_selected_nickname_letter_index]);
																    m_letter_buttons[m_selected_nickname_letter_index].set_button_text(letter);
																    break; }

											case sf::Keyboard::Down: { if (m_nickname_letters[m_selected_nickname_letter_index] == 'Z') {
																	 	m_nickname_letters[m_selected_nickname_letter_index] = 'A';
																	 
																	 } else {
																	 	m_nickname_letters[m_selected_nickname_letter_index]++;
																	 
																	 }
																	 
																	 std::string letter(1, m_nickname_letters[m_selected_nickname_letter_index]);
																	 m_letter_buttons[m_selected_nickname_letter_index].set_button_text(letter);											
																	 break; }

											case sf::Keyboard::Left: if (m_selected_nickname_letter_index == 0) {
																	 	m_selected_nickname_letter_index = m_nickname_letters.size() - 1;

																		for (auto& triangle : m_triangles) triangle.move({ m_selected_nickname_letter_index * (2 * GAP + m_single_letter_box_size.x), 0 });

																	 } else {
																		m_selected_nickname_letter_index--;
																		
																		for (auto& triangle : m_triangles) triangle.move({ -2 * GAP - m_single_letter_box_size.x, 0});

																	 }
																	 break;

											case sf::Keyboard::Right: if (m_selected_nickname_letter_index == m_nickname_letters.size() - 1) {
																	  	m_selected_nickname_letter_index = 0;
																	  
																	  	for (auto& triangle : m_triangles) triangle.move({ (float)(m_nickname_letters.size() - 1) * (-1) * (2 * GAP + m_single_letter_box_size.x), 0 });
																	  
																	  } else {
																	  	m_selected_nickname_letter_index++;
																	  
																	  	for (auto& triangle : m_triangles) triangle.move({ 2 * GAP + m_single_letter_box_size.x, 0 });
																	  
																	  }
																	  break;

											case sf::Keyboard::Return: { scores scores;
																		 std::string nickname;

																		 for (const auto& letter : m_nickname_letters) nickname += letter;

																		 scores.append_score(nickname, difficulty_settings::get_selected_difficulty_name(), state_playing::get_player_score());

																		 
																		 m_machine.remove_state();
																		 break; }
																		 
										 }
										 
										 break;

			default: break;
		}
	}
}

void state_submit_score::update(sf::Time delta_time) {

}

void state_submit_score::render() {
	m_window.clear(sf::Color::Black);

	m_game_over_button.draw_button(m_window);

	m_score_button.draw_button(m_window);

	m_enter_nickname_button.draw_button(m_window);
	
	for (const auto& letter : m_letter_buttons) letter.draw_button(m_window);

	for (const auto& triangle : m_triangles) m_window.draw(triangle);

	m_window.display();
}