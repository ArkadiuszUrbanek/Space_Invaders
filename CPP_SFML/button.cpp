#include "button.hpp"

button::button(sf::Font& font, std::string text, unsigned int character_size, sf::Color text_color, sf::Text::Style text_style, sf::Color button_color) {
	m_text.setFont(font);
	m_text.setString(text);
	m_text.setCharacterSize(character_size);
	m_text.setFillColor(text_color);
	m_text.setStyle(text_style);
	m_text.setPosition(0.0f, 0.0f);

	m_button.setSize({ m_text.getLocalBounds().width, m_text.getLocalBounds().height });
	m_text.setOrigin(m_button.getSize().x / 2.0f, m_button.getSize().y / 2.0f);
	
	m_button.setFillColor(button_color);
	m_button.setPosition(0.0f, 0.0f);
	m_button.setOrigin(m_button.getSize().x / 2.0f, m_button.getSize().y / 2.0f);

}

button::button(sf::Font& font, unsigned int character_size, sf::Color text_color, sf::Text::Style text_style, sf::Color button_color) {
	m_text.setFont(font);
	m_text.setCharacterSize(character_size);
	m_text.setFillColor(text_color);
	m_text.setStyle(text_style);
	m_text.setPosition(0.0f, 0.0f);

	m_button.setFillColor(button_color);
	m_button.setPosition(0.0f, 0.0f);
}

void button::set_button_text(std::string text) {
	m_text.setString(text);
	m_button.setSize({ m_text.getLocalBounds().width, m_text.getLocalBounds().height });
	m_text.setOrigin(m_button.getSize().x / 2.0f, m_button.getSize().y / 2.0f);
	m_button.setOrigin(m_button.getSize().x / 2.0f, m_button.getSize().y / 2.0f);

}

const sf::Vector2f& button::get_button_size() const {
	return m_button.getSize();
}

const sf::Vector2f& button::get_button_position() const {
	return m_button.getPosition();
}

void button::set_button_text_color(sf::Color new_text_color) {
	m_text.setFillColor(new_text_color);
}

void button::set_button_position(sf::Vector2f button_position) {
	m_text.setPosition(button_position);
	m_button.setPosition(button_position);
}

void button::draw_button(sf::RenderWindow& window) const {
	window.draw(m_button);
	window.draw(m_text);
}

bool button::is_mouse_over(const sf::RenderWindow& window) const {
	sf::Vector2f mouse_coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	sf::FloatRect button_coordinates(m_button.getGlobalBounds());

	if (button_coordinates.contains(mouse_coordinates)) return true;
	else return false;

}