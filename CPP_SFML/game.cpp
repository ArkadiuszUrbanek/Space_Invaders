#include "game.hpp"
#include "state_machine.hpp"
#include "state_main_menu.hpp"

#include <string>
#include <iostream>

game::game() : m_window({ m_WINDOW_WIDTH, m_WINDOW_HEIGHT }, "Cosmic Intruders", sf::Style::Titlebar | sf::Style::Close) {
	m_window.setFramerateLimit(m_FPS_LIMIT);

	sf::Image icon;
	icon.loadFromFile("sprites/icon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().x, icon.getPixelsPtr());
}

game::~game() = default;

void game::run() {
	m_machine.run_state(state_machine::create_state<state_main_menu>(m_machine, m_window), state_machine::command::ADD);
	
	sf::Clock timer;
	sf::Time delta_time = sf::Time::Zero;


	while (m_window.isOpen()) {

		m_machine.process_state_changes();
		m_machine.poll_events();

		delta_time = timer.restart();

		m_machine.update(delta_time);
		m_machine.render();
	}
}