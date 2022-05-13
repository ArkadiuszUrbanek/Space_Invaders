#include "difficulty_settings.hpp"

difficulty_settings::difficulty difficulty_settings::m_selected_difficulty = difficulty::NORMAL;

std::array<std::pair<difficulty_settings::difficulty, difficulty_settings::state_playing_settings>, 3> difficulty_settings::m_state_playing_settings = {
	std::pair<difficulty_settings::difficulty, difficulty_settings::state_playing_settings>(difficulty::EASY, {3}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::state_playing_settings>(difficulty::NORMAL, {2}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::state_playing_settings>(difficulty::HARD, {1}) };

std::array<std::pair<difficulty_settings::difficulty, difficulty_settings::player_settings>, 3> difficulty_settings::m_player_settings = {
	std::pair<difficulty_settings::difficulty, difficulty_settings::player_settings>(difficulty::EASY, difficulty_settings::player_settings{150.0f, 100.0f, sf::seconds(0.2f)}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::player_settings>(difficulty::NORMAL, difficulty_settings::player_settings{100.0f, 81.25f, sf::seconds(0.5f)}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::player_settings>(difficulty::HARD, difficulty_settings::player_settings{80.0f, 65.0f, sf::seconds(0.7f)}) };

std::array<std::pair<difficulty_settings::difficulty, difficulty_settings::intruder_manager_settings>, 3> difficulty_settings::m_intruder_manager_settings = {
	std::pair<difficulty_settings::difficulty, difficulty_settings::intruder_manager_settings>(difficulty::EASY, {sf::seconds(0.6f), sf::seconds(7.0f)}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::intruder_manager_settings>(difficulty::NORMAL, {sf::seconds(0.5f), sf::seconds(6.0f)}),
	std::pair<difficulty_settings::difficulty, difficulty_settings::intruder_manager_settings>(difficulty::HARD, {sf::seconds(0.4f), sf::seconds(5.0f)}) };

std::pair<difficulty_settings::difficulty, difficulty_settings::state_playing_settings> difficulty_settings::get_state_playing_difficulty_settings() {
	for(const auto& setting : m_state_playing_settings) 
		if (m_selected_difficulty == setting.first) return setting;
}

std::pair<difficulty_settings::difficulty, difficulty_settings::player_settings> difficulty_settings::get_player_difficulty_settings() {
	for (const auto& setting : m_player_settings)
		if (m_selected_difficulty == setting.first) return setting;
}

std::pair<difficulty_settings::difficulty, difficulty_settings::intruder_manager_settings> difficulty_settings::get_intruder_manager_difficulty_settings() {
	for (const auto& setting : m_intruder_manager_settings)
		if (m_selected_difficulty == setting.first) return setting;
}

const std::string difficulty_settings::get_selected_difficulty_name() {
	switch (m_selected_difficulty) {
		case difficulty_settings::difficulty::EASY: return "Easy"; break;
		case difficulty_settings::difficulty::NORMAL: return "Normal"; break;
		case difficulty_settings::difficulty::HARD: return "Hard"; break;
	}
}

const std::string difficulty_settings::get_difficulty_name(difficulty_settings::difficulty difficulty) {
	switch (difficulty) {
		case difficulty_settings::difficulty::EASY: return "Easy"; break;
		case difficulty_settings::difficulty::NORMAL: return "Normal"; break;
		case difficulty_settings::difficulty::HARD: return "Hard"; break;
	}
}