#include "hud.hpp"
#include "game.hpp"
#include "scores.hpp"

#include <iostream>

#define BAR_HEIGHT 2.0f

sf::Texture hud::load_heart_spritesheet() {
	sf::Texture texture;
	if (texture.loadFromFile("sprites/heart_spritesheet.png") == false) std::cout << "Nie udalo sie wczytac tekstury serca.";

	return texture;
}

sf::Font hud::load_font() {
	sf::Font font;
	if (font.loadFromFile("fonts/PIXEARG_.TTF") == false) std::cout << "blad przy ladowaniu czcionki";

	return font;
}

hud::hud(unsigned char lives, unsigned short level) : m_heart_texture(load_heart_spritesheet()), m_font(load_font()), m_heart_animation(&m_heart_texture, { 2 , 1 }, sf::seconds(0.0f)), m_level(level) {
	scores scores;
	
	m_highscore = scores.get_highest_score();

	for (auto& bar : m_bars) {
		bar.setSize({ (float)game::m_WINDOW_WIDTH, BAR_HEIGHT });
		bar.setFillColor(sf::Color(255, 255, 255, 255));
	}

	m_bars[0].setOrigin({ 0.0f, BAR_HEIGHT });
	m_bars[0].setPosition({ 0.0f, (float)hud::m_HUD_TOP_HEIGHT });

	m_bars[1].setPosition({ 0.0f, (float)game::m_WINDOW_HEIGHT - hud::m_HUD_BOTTOM_HEIGHT });


	for (auto& filler : m_fillers) {
		filler.setFillColor(sf::Color(0, 0, 0, 255));
	}

	m_fillers[0].setSize({ (float)game::m_WINDOW_WIDTH, m_HUD_TOP_HEIGHT - BAR_HEIGHT });
	m_fillers[1].setSize({ (float)game::m_WINDOW_WIDTH, m_HUD_BOTTOM_HEIGHT - BAR_HEIGHT });

	m_fillers[0].setOrigin({ 0.0f, m_HUD_TOP_HEIGHT - BAR_HEIGHT });
	m_fillers[0].setPosition({ 0.0f, (float)hud::m_HUD_TOP_HEIGHT - BAR_HEIGHT });

	m_fillers[1].setPosition({ 0.0f, (float)game::m_WINDOW_HEIGHT - hud::m_HUD_BOTTOM_HEIGHT + BAR_HEIGHT });


	m_hud_bottom_text = button(m_font, "Lives", 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_hud_bottom_text.set_button_position({ 2.0f + m_hud_bottom_text.get_button_size().x / 2.0f, game::m_WINDOW_HEIGHT - (hud::m_HUD_BOTTOM_HEIGHT - BAR_HEIGHT) / 2 });

	m_hud_top_textes[0] = button(m_font, "Level", 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_hud_top_textes[1] = button(m_font, "Highscore", 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_hud_top_textes[2] = button(m_font, "Score", 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);

	m_hud_top_textes[3] = button(m_font, 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_hud_top_textes[4] = button(m_font, 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
	m_hud_top_textes[5] = button(m_font, 15, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);

	m_hud_top_textes[0].set_button_position({ game::m_WINDOW_WIDTH / 4, 2.0f + m_hud_top_textes[0].get_button_size().y / 2.0f });
	m_hud_top_textes[1].set_button_position({ game::m_WINDOW_WIDTH / 4 + m_hud_top_textes[0].get_button_position().x, 2.0f + m_hud_top_textes[0].get_button_size().y / 2.0f });
	m_hud_top_textes[2].set_button_position({ game::m_WINDOW_WIDTH / 4 + m_hud_top_textes[1].get_button_position().x, 2.0f + m_hud_top_textes[0].get_button_size().y / 2.0f });

	m_hud_top_textes[3].set_button_position({ game::m_WINDOW_WIDTH / 4, 4.0f + m_hud_top_textes[0].get_button_size().y + m_hud_top_textes[0].get_button_size().y / 2.0f });
	m_hud_top_textes[4].set_button_position({ game::m_WINDOW_WIDTH / 4 + m_hud_top_textes[3].get_button_position().x, 4.0f + m_hud_top_textes[0].get_button_size().y + m_hud_top_textes[0].get_button_size().y / 2.0f });
	m_hud_top_textes[5].set_button_position({ game::m_WINDOW_WIDTH / 4 + m_hud_top_textes[4].get_button_position().x, 4.0f + m_hud_top_textes[0].get_button_size().y + m_hud_top_textes[0].get_button_size().y / 2.0f });

	for (unsigned char index = 0; index < lives; index++) {
		m_hearts.emplace_back(sf::Vector2f{ 20.0f, 18.0f });

		m_hearts[index].setOrigin({ m_hearts[index].getSize().x / 2.0f, m_hearts[index].getSize().y / 2.0f });
		
		if (index == 0) m_hearts[index].setPosition({ m_hud_bottom_text.get_button_size().x + 2.0f + 10.0f * (index + 1) + 2.0f * (index + 1), game::m_WINDOW_HEIGHT - (hud::m_HUD_BOTTOM_HEIGHT - BAR_HEIGHT) / 2 });
		else m_hearts[index].setPosition({ m_hearts[index - 1].getPosition().x + 20.0f + 2.0f, m_hearts[index - 1].getPosition().y });

	
		m_hearts[index].setTexture(&m_heart_texture);
		m_hearts[index].setTextureRect(m_heart_animation.get_image_rect());

	}

}

void hud::update_lives(const unsigned char& lives) {
	m_heart_animation.reset(0);
	unsigned char index = 0;
	for (; index < lives; index++) {
		m_hearts[index].setTextureRect(m_heart_animation.get_image_rect());
	}

	m_heart_animation.force_update(0);
	for (; index < m_hearts.size(); index++) {
		m_hearts[index].setTextureRect(m_heart_animation.get_image_rect());
	}
}

void hud::draw(sf::RenderWindow& window) {
	m_hud_top_textes[3].set_button_text(std::to_string(m_level));

	if(m_highscore > m_score) m_hud_top_textes[4].set_button_text(std::to_string(m_highscore));
	else m_hud_top_textes[4].set_button_text(std::to_string(m_score));

	m_hud_top_textes[5].set_button_text(std::to_string(m_score));

	for (const auto& bar : m_bars) window.draw(bar);
	for (auto& filler : m_fillers)  window.draw(filler);

	for (const auto& top_text : m_hud_top_textes) top_text.draw_button(window);

	m_hud_bottom_text.draw_button(window);

	for (const auto& heart : m_hearts) window.draw(heart);

}