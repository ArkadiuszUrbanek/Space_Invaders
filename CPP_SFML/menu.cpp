#include <iostream>

#include "menu.hpp"
#include "game.hpp"

menu::menu(const sf::RenderWindow& window, std::initializer_list<std::string> options_list) : m_number_of_options(options_list.size()), m_ptr_options_array(new button[m_number_of_options]), m_selected_option_index(0) {
	if (m_font.loadFromFile("fonts/PIXEARG_.TTF") == false) {
		std::cout << "blad przy ladowaniu czcionki";
	}

	auto list = options_list.begin();
	for (int index = 0; index < m_number_of_options; index++) {

		if (index == 0) m_ptr_options_array[index] = button(m_font, list[index], 24, sf::Color::Red, sf::Text::Bold, sf::Color::Transparent);
		else m_ptr_options_array[index] = button(m_font, list[index], 24, sf::Color::White, sf::Text::Bold, sf::Color::Transparent);

		m_ptr_options_array[index].set_button_position(sf::Vector2f(game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / (m_number_of_options + 1) * (index + 1)));
	}

}

menu::~menu() {
	delete[] m_ptr_options_array;
}

void menu::draw(sf::RenderWindow& window) const {
	for (int index = 0; index < m_number_of_options; index++) {
		m_ptr_options_array[index].draw_button(window);
	}

}

void menu::option_previous() {
	m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::White);

	if (--m_selected_option_index && m_selected_option_index < 0) {
		m_selected_option_index = m_number_of_options - 1;
	}

	m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::Red);

}

void menu::option_next() {
	m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::White);

	if (++m_selected_option_index && m_selected_option_index > m_number_of_options - 1) {
		m_selected_option_index = 0;
	}

	m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::Red);

}

int menu::option_mouse_hover(const sf::RenderWindow& window) {
	int index = 0;

	for (index; index < m_number_of_options; index++) {
		if (m_ptr_options_array[index].is_mouse_over(window) == true) {
			m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::White);
			m_selected_option_index = index;
			m_ptr_options_array[m_selected_option_index].set_button_text_color(sf::Color::Red);
			break;
		}
	}
	return index;
}

int menu::get_selected_option_index() const {
	return m_selected_option_index;
}