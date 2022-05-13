#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "button.hpp"

template<size_t character_limit>
class textbox {
private:
	char m_entered_text[character_limit + 1];
	size_t m_current_char_index = 0;

	button m_text;

	bool is_backspace(unsigned char key_code) const;
	bool is_valid_char(unsigned char key_code) const;

public:
	textbox() = default;
	textbox(sf::Font& font, unsigned int character_size, sf::Color text_color, sf::Text::Style text_style, sf::Color button_color, sf::Vector2f textbox_size);
	void handle_input(const sf::Event& event);
	const sf::Vector2f& get_textbox_size() const;
	void set_positon(sf::Vector2f textbox_position);
	void draw(sf::RenderWindow& window) const;
	std::string return_text_string() const;

};

#endif
