#include "state_base.hpp"

state_base::state_base(state_machine& machine, sf::RenderWindow& window) : m_machine(machine), m_window(window) {}