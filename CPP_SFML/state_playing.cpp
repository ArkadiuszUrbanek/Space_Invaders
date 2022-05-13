#include "state_playing.hpp"
#include "state_submit_score.hpp"
#include "difficulty_settings.hpp"
#include "game.hpp"

#include <iostream>

unsigned int state_playing::m_player_score = 0;

state_playing::state_playing(state_machine& machine, sf::RenderWindow& window) : 
	state_base(machine, window),
	m_player(difficulty_settings::get_player_difficulty_settings().second.m_player_max_speed, difficulty_settings::get_player_difficulty_settings().second.m_player_acceleration, difficulty_settings::get_player_difficulty_settings().second.m_time_interval_between_shots),
	m_intruder_manager(difficulty_settings::get_intruder_manager_difficulty_settings().second.m_step_gap, difficulty_settings::get_intruder_manager_difficulty_settings().second.m_time_interval_between_shots),
	m_level(1),
	m_max_player_lives(difficulty_settings::get_state_playing_difficulty_settings().second.m_max_player_lives), m_player_lives(m_max_player_lives),
	m_hud(m_max_player_lives, m_level - 1) {

	m_player_score = 0;

	if (m_background_image.loadFromFile("sprites/space_image.png") == false) std::cout << "Blad przy ladowaniu tla gry.";
	if (m_font.loadFromFile("fonts/PIXEARG_.TTF") == false) std::cout << "blad przy ladowaniu czcionki";

	m_text_button = button(m_font, 46, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);

	m_background.setTexture(m_background_image);
	m_background.setTextureRect(sf::IntRect{ (int)0, (int)0, (int)m_background_image.getSize().x, (int)m_background_image.getSize().y - hud::m_HUD_TOP_HEIGHT - hud::m_HUD_BOTTOM_HEIGHT });

}

void state_playing::load_level() {
	m_array_of_players_projectiles.clear();
	m_array_of_intruders_projectiles.clear();

	m_ufo.reset();
	m_intruder_manager.reset();
	m_player.reset();

	float current_x_shield_position = (game::m_WINDOW_WIDTH - 112 * m_array_of_shields.size()) / (m_array_of_shields.size() + 1) + 112 / 2;

	for (unsigned int index = 0; index < m_array_of_shields.size(); index++) {
		m_array_of_shields[index].reset();
		m_array_of_shields[index].set_position({ current_x_shield_position, game::m_WINDOW_HEIGHT - 100.0f - hud::m_HUD_BOTTOM_HEIGHT });
		current_x_shield_position += (game::m_WINDOW_WIDTH - 112 * m_array_of_shields.size()) / (m_array_of_shields.size() + 1) + 112;

	}

	m_level++;
	m_hud.update_level();

	m_time_passed = sf::seconds(0.0f);
	m_current_game_state = game_states::NORMAL_GAMEPLAY;
}

void state_playing::switching_level(sf::Time delta_time) {
	m_time_passed += delta_time;

	if (m_time_passed <= sf::seconds(3.0f)) {
		std::string text = "Level ";
		text += std::to_string(m_level);

		m_text_button.set_button_text(text);
		m_text_button.set_button_position({game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2});

	} else {
		load_level();

	}
}

void state_playing::poll_events() {
	if (m_window.pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed) {
			m_window.close();
		}
	}

	switch (m_current_game_state) {
		case game_states::NORMAL_GAMEPLAY: m_player.handle_input(); break;

		case game_states::CHANGING_LEVEL: case game_states::RESPAWNING_PLAYER: case game_states::GAME_OVER: break;

	}
}

void state_playing::update(sf::Time delta_time) {
	switch (m_current_game_state) {
	case game_states::GAME_OVER: m_machine.run_state(state_machine::create_state<state_submit_score>(m_machine, m_window), state_machine::command::REPLACE); break;

	case game_states::CHANGING_LEVEL: this->switching_level(delta_time); break;

	case game_states::RESPAWNING_PLAYER: if (m_player.is_alive() == false) {
										 	 m_player.update(delta_time);
											 m_player.respawn();

										 } else {
										 	 m_current_game_state = game_states::NORMAL_GAMEPLAY;

										 }
										 
										 break;
	
	case game_states::NORMAL_GAMEPLAY: m_intruder_manager.update();
									   

									   m_player.update(delta_time);
									   

									   m_ufo.update(delta_time);
									   
									   for (auto itr = m_array_of_players_projectiles.begin(); itr != m_array_of_players_projectiles.end(); ) {
									    auto& player_projectile = *itr;
									    

									    player_projectile.update_position(delta_time);
									    

									    for (auto itr = m_array_of_intruders_projectiles.begin(); itr != m_array_of_intruders_projectiles.end(); ) {
									    	auto& intruder_projectile = *itr;
									    
									    	if (player_projectile.projectile_collision(intruder_projectile) == true) {
									    		intruder_projectile.destroy();
									    		itr = m_array_of_intruders_projectiles.erase(itr);
									    		break;
									    
									    	} else {
									    		itr++;
									    
									    	}
									    
									    }
									    

									    for (size_t i = 0; i < m_array_of_shields.size(); i++) {
									    	m_array_of_shields[i].projectile_collision(player_projectile);
									    }
									    

									    if (m_intruder_manager.projectile_collision(player_projectile) == true) {
									    	player_projectile.destroy();

									    	m_player_score += m_intruder_manager.return_points();
									    	m_hud.update_score(m_player_score);

											if (m_intruder_manager.are_intruders_alive() == false) {
												m_current_game_state = game_states::CHANGING_LEVEL;
												this->switching_level(sf::seconds(0.0f));
												return;

											}
									    
									    }
									    

									    if (m_ufo.projectile_collision(player_projectile) == true) {
									    	player_projectile.destroy();
									    
									    	m_player_score += m_ufo.return_points();
									    	m_hud.update_score(m_player_score);
									    
									    	if (m_player_lives < m_max_player_lives) {
									    		m_player_lives++;
									    		m_hud.update_lives(m_player_lives);
									    	}
									    
									    }
									    

									    if (player_projectile.get_position().y < hud::m_HUD_TOP_HEIGHT) player_projectile.destroy();
									    

									    if (player_projectile.is_destroyed() == true) itr = m_array_of_players_projectiles.erase(itr);
									    else itr++;
									   }
									   
									   for (auto itr = m_array_of_intruders_projectiles.begin(); itr != m_array_of_intruders_projectiles.end(); ) {
									   	auto& intruder_projectile = *itr;
									   

									   	intruder_projectile.update_position(delta_time);
									   

									   	for (size_t i = 0; i < m_array_of_shields.size(); i++) {
									   		m_array_of_shields[i].projectile_collision(intruder_projectile);
									   	}
									   

									   	if (m_player.projectile_collision(intruder_projectile) == true) {
									   		intruder_projectile.destroy();

											if (m_player_lives != 0) {
												m_player.respawn();

												m_current_game_state = game_states::RESPAWNING_PLAYER;

												m_player_lives--;
												m_hud.update_lives(m_player_lives);

											} else {
												m_current_game_state = game_states::GAME_OVER;
												return;

											}

									   	}
									   
									   
									   	if (intruder_projectile.get_position().y > game::m_WINDOW_HEIGHT - hud::m_HUD_BOTTOM_HEIGHT) intruder_projectile.destroy();
									   
									   	if (intruder_projectile.is_destroyed() == true) itr = m_array_of_intruders_projectiles.erase(itr);
									   	else itr++;
									   }
									   
									   const std::vector<sf::FloatRect> intruder_collision_boxes = m_intruder_manager.get_collision_boxes();
									   for (size_t i = 0; i < m_array_of_shields.size(); i++) m_array_of_shields[i].intruders_collision(intruder_collision_boxes);
									   

									   if (m_player.intruders_collision(intruder_collision_boxes) == true) {
										m_current_game_state = game_states::GAME_OVER;
									   
									   } else {
									   	for (const auto& element : intruder_collision_boxes) {
									   		if (element.top + element.height > game::m_WINDOW_HEIGHT - hud::m_HUD_BOTTOM_HEIGHT) {
												m_current_game_state = game_states::GAME_OVER;
									   			break;
									   		}
									   	}
									   
									   }
									   
									   sf::Vector2f gunner_pos = m_intruder_manager.get_shooter_position();
									   if (gunner_pos.x != -1) {
									   	m_array_of_intruders_projectiles.emplace_back(gunner_pos, 100.0f);
									   
									   }
									   
									   if (m_player.shot_fired()) m_array_of_players_projectiles.emplace_back(m_player.get_gun_position(), -600.0f);

									   break;
	}
}

void state_playing::render() {
    m_window.clear(sf::Color::Black);
	
	switch (m_current_game_state) {

		case game_states::CHANGING_LEVEL: m_text_button.draw_button(m_window); break;

		case game_states::NORMAL_GAMEPLAY: case game_states::RESPAWNING_PLAYER: m_window.draw(m_background);
																				m_player.draw(m_window);

																				for (unsigned int index = 0; index < m_array_of_shields.size(); index++) {
																					m_array_of_shields[index].draw(m_window);

																				}

																				for (const auto& index : m_array_of_players_projectiles) {
																					index.draw(m_window);
																				}

																				for (const auto& index : m_array_of_intruders_projectiles) {
																					index.draw(m_window);
																				}

																				m_ufo.draw(m_window);

																				m_intruder_manager.draw(m_window);

																				m_hud.draw(m_window);

																				break;

		case game_states::GAME_OVER: break;

	}

    m_window.display();
}
