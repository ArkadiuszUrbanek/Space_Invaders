#include "state_main_menu.hpp"
#include "state_playing.hpp"
#include "state_machine.hpp"
#include "state_scores.hpp"
#include "state_settings.hpp"

#include <iostream>

state_main_menu::state_main_menu(state_machine& machine, sf::RenderWindow& window) : state_base(machine, window), m_menu(m_window, { "Play", "Leaderboards", "Options", "Exit" }) {}

void state_main_menu::poll_events() {
    if (m_window.pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::KeyReleased: switch (m_event.key.code) {
                                             case sf::Keyboard::Up: m_menu.option_previous();
                                                                    break;
                                            
                                             case sf::Keyboard::Down: m_menu.option_next();
                                                                      break;
                                            
                                             case sf::Keyboard::Return: switch (m_menu.get_selected_option_index()) {
                                                                            case 0: m_machine.run_state(state_machine::create_state<state_playing>(m_machine, m_window), state_machine::command::ADD);
                                                                                    break;
                                                                            
                                                                            case 1: m_machine.run_state(state_machine::create_state<state_scores>(m_machine, m_window), state_machine::command::ADD);
                                                                                    break;
                                                                            
                                                                            case 2: m_machine.run_state(state_machine::create_state<state_settings>(m_machine, m_window), state_machine::command::ADD);
                                                                                    break;
                                                                            
                                                                            case 3: m_window.close();
                                                                                    break;
                                                                            }
                                                                        
                                                                        break;
                                            
                                         }
                                         
                                         break;
            
            case sf::Event::MouseMoved: m_menu.option_mouse_hover(m_window);
                                        break;
            
            case sf::Event::MouseButtonPressed: if (m_event.mouseButton.button == sf::Mouse::Left) {
                                                    switch (m_menu.option_mouse_hover(m_window)) {
                                                        case 0: m_machine.run_state(state_machine::create_state<state_playing>(m_machine, m_window), state_machine::command::ADD);
                                                                break;
                                                                
                                                        case 1: m_machine.run_state(state_machine::create_state<state_scores>(m_machine, m_window), state_machine::command::ADD);
                                                                break;
                                                                
                                                        case 2: m_machine.run_state(state_machine::create_state<state_settings>(m_machine, m_window), state_machine::command::ADD);
                                                                break;
                                                                
                                                        case 3: m_window.close();
                                                                break;

                                                    }

                                                }
                                                
                                                break;
    
            case sf::Event::Closed: m_window.close();
                                    break;
    
        }
    
    }

}

void state_main_menu::update(sf::Time delta_time) {}

void state_main_menu::render() {
    m_window.clear(sf::Color::Black);
    m_menu.draw(m_window);
    m_window.display();
}