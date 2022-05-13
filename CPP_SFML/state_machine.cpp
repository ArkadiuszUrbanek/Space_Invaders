#include "state_machine.hpp"
#include "state_base.hpp"

#include "state_main_menu.hpp"
#include "state_playing.hpp"
#include "state_submit_score.hpp"
#include "state_scores.hpp"
#include "state_settings.hpp"

#include <iostream>

state_machine::state_machine() = default;

void state_machine::run_state(std::unique_ptr<state_base> state, state_machine::command command) {
	m_ptr_new_state = std::move(state);
	m_command = command;
	m_wait = false;
}

void state_machine::process_state_changes() {
	if (m_wait == false) {
		if ((m_command == state_machine::command::REMOVE || m_command == state_machine::command::REPLACE) && !m_stack_of_ptr_states.empty()) {
			m_stack_of_ptr_states.pop();

		}

		if (m_command == state_machine::command::ADD || m_command == state_machine::command::REPLACE) {
			m_stack_of_ptr_states.push(std::move(m_ptr_new_state));

		}

		m_wait = true;
	}
}

void state_machine::remove_state() {
	m_command = state_machine::command::REMOVE;
	m_wait = false;

}

void state_machine::poll_events() {
	m_stack_of_ptr_states.top()->poll_events();
}

void state_machine::update(sf::Time delta_time) {
	m_stack_of_ptr_states.top()->update(delta_time);
}

void state_machine::render() {
	m_stack_of_ptr_states.top()->render();
}

template <typename T>
std::unique_ptr<T> state_machine::create_state(state_machine& machine, sf::RenderWindow& window) {
	return std::unique_ptr<T>(new T(machine, window));
}

template std::unique_ptr<state_main_menu> state_machine::create_state(state_machine& machine, sf::RenderWindow& window);
template std::unique_ptr<state_playing> state_machine::create_state(state_machine& machine, sf::RenderWindow& window);
template std::unique_ptr<state_submit_score> state_machine::create_state(state_machine& machine, sf::RenderWindow& window);
template std::unique_ptr<state_scores> state_machine::create_state(state_machine& machine, sf::RenderWindow& window);
template std::unique_ptr<state_settings> state_machine::create_state(state_machine& machine, sf::RenderWindow& window);