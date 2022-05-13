#include "state_settings.hpp"
#include "state_machine.hpp"
#include "difficulty_settings.hpp"
#include "game.hpp"

#include <iostream>

state_settings::state_settings(state_machine& machine, sf::RenderWindow& window) : state_base(machine, window) {
    if (m_font.loadFromFile("fonts/PIXEARG_.TTF") == false) {
        std::cout << "blad przy ladowaniu czcionki";
    }

    switch (difficulty_settings::get_selected_difficulty()) {
        case difficulty_settings::difficulty::EASY: m_selected_index = 0; break;
        case difficulty_settings::difficulty::NORMAL: m_selected_index = 1; break;
        case difficulty_settings::difficulty::HARD: m_selected_index = 2; break;
    
    }

    m_title = button(m_font, "Select difficulty", 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);

    for (auto& single_button : m_array_of_buttons) {
        single_button = button(m_font, 24, sf::Color::White, sf::Text::Style::Bold, sf::Color::Transparent);
    }

    m_array_of_buttons[0].set_button_text(difficulty_settings::get_difficulty_name(difficulty_settings::difficulty::EASY));
    m_array_of_buttons[0].set_button_position({game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 + m_array_of_buttons[0].get_button_size().y / 2 });

    m_array_of_buttons[1].set_button_text(difficulty_settings::get_difficulty_name(difficulty_settings::difficulty::NORMAL));
    m_array_of_buttons[1].set_button_position({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 + m_array_of_buttons[1].get_button_size().y / 2 });

    m_array_of_buttons[2].set_button_text(difficulty_settings::get_difficulty_name(difficulty_settings::difficulty::HARD));
    m_array_of_buttons[2].set_button_position({ game::m_WINDOW_WIDTH / 2, game::m_WINDOW_HEIGHT / 2 + m_array_of_buttons[2].get_button_size().y / 2 });


    button widest_letter = button(m_font, "W", 24);

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

    m_triangles[0].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x - m_triangles[0].getOrigin().x - 10.0f - m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });
    m_triangles[1].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x + m_triangles[1].getOrigin().x + 10.0f + m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });

    m_title.set_button_position({ m_array_of_buttons[m_selected_index].get_button_position().x, m_array_of_buttons[m_selected_index].get_button_position().y - m_array_of_buttons[m_selected_index].get_button_size().y / 2 - m_title.get_button_size().y / 2 - 10.0f });
}

void state_settings::poll_events() {
    if (m_window.pollEvent(m_event)) {
        switch (m_event.type) {
        case sf::Event::Closed: m_window.close(); break;

        case sf::Event::KeyReleased: switch (m_event.key.code) {
                                        case sf::Keyboard::Escape: if(m_selected_index == 0) difficulty_settings::change_selected_difficulty_to(difficulty_settings::difficulty::EASY);
                                                                   else if (m_selected_index == 1) difficulty_settings::change_selected_difficulty_to(difficulty_settings::difficulty::NORMAL);
                                                                   else if (m_selected_index == 2) difficulty_settings::change_selected_difficulty_to(difficulty_settings::difficulty::HARD);
                                                                   m_machine.remove_state(); 
                                                                   break;

                                        case sf::Keyboard::Left: if (m_selected_index == 0) m_selected_index = m_array_of_buttons.size() - 1;
                                                                 else m_selected_index--;

                                                                 m_triangles[0].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x - m_triangles[0].getOrigin().x - 10.0f - m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });
                                                                 m_triangles[1].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x + m_triangles[1].getOrigin().x + 10.0f + m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });

                                                                 break;

                                        case sf::Keyboard::Right: if (m_selected_index == m_array_of_buttons.size() - 1) m_selected_index = 0;
                                                                  else m_selected_index++;
                                                                  
                                                                  m_triangles[0].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x - m_triangles[0].getOrigin().x - 10.0f - m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });
                                                                  m_triangles[1].setPosition({ m_array_of_buttons[m_selected_index].get_button_position().x + m_triangles[1].getOrigin().x + 10.0f + m_array_of_buttons[m_selected_index].get_button_size().x / 2, m_array_of_buttons[m_selected_index].get_button_position().y });

                                                                  break;

                                     }
                                     
                                     break;
        }

    }

}

void state_settings::update(sf::Time delta_time) {

}

void state_settings::render() {
    m_window.clear(sf::Color::Black);
    
    m_title.draw_button(m_window);

    for (auto& triangle : m_triangles) m_window.draw(triangle);

    m_array_of_buttons[m_selected_index].draw_button(m_window);

    m_window.display();
}