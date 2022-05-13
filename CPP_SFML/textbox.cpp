#include "textbox.hpp"

template<size_t character_limit>
bool textbox<character_limit>::is_backspace(unsigned char key_code) const {
    return key_code == 8;
}

template<size_t character_limit>
bool textbox<character_limit>::is_valid_char(unsigned char key_code) const {
    return (key_code >= 'a' && key_code <= 'z') || (key_code >= 'A' && key_code <= 'Z') || (key_code >= '0' && key_code <= '9');
}

template<size_t character_limit>
textbox<character_limit>::textbox(sf::Font& font, unsigned int character_size, sf::Color text_color, sf::Text::Style text_style, sf::Color button_color, sf::Vector2f textbox_size) : m_text(font, character_size, text_color, text_style, button_color) {
    for (size_t index = 0; index < character_limit; index++) {
        m_entered_text[index] = ' ';
    }

    m_entered_text[character_limit] = '\0';

    //m_text.set_button_text(m_entered_text);
    m_text.set_button_size(textbox_size);
    m_text.set_button_outline_thickness(3);
    m_text.set_button_outline_color(sf::Color::White);

}

template<size_t character_limit>
void textbox<character_limit>::handle_input(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::TextEntered: { unsigned char key_code = event.text.unicode;

                                       if (is_valid_char(key_code)) {
                                           if (m_current_char_index <= character_limit) {
                                               m_entered_text[m_current_char_index] = key_code;

                                               if (m_current_char_index + 1 < character_limit) m_current_char_index++;

                                               break;
                                           }

                                       } else if (is_backspace(key_code)) {
                                           m_entered_text[m_current_char_index] = ' ';

                                           if (m_current_char_index > 0) m_current_char_index--;


                                       }

                                       m_text.set_button_text(m_entered_text);

                                       break; }
    
        default: break;
    }

}

template<size_t character_limit>
const sf::Vector2f& textbox<character_limit>::get_textbox_size() const {
    return m_text.get_button_size();

}

template<size_t character_limit>
void textbox<character_limit>::set_positon(sf::Vector2f textbox_position) {
    m_text.set_button_position(textbox_position);

}

template<size_t character_limit>
void textbox<character_limit>::draw(sf::RenderWindow& window) const {
    m_text.draw_button(window);

}

template<size_t character_limit>
std::string textbox<character_limit>::return_text_string() const {
    return std::string(m_entered_text);
}

template class textbox<3>;