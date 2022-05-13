/** @file*/

#ifndef STATE_SETTINGS_HPP
#define STATE_SETTINGS_HPP

#include "state_base.hpp"
#include "button.hpp"

#include <array>

/** Klasa-stan ustawienia gry.*/

class state_settings final : public state_base {
private:
	sf::Font m_font; ///< Czcionka
	unsigned int m_selected_index; ///< Indeks wybranego poziomu trudnoœci

	button m_title; ///< Tytu³ "Select difficulty"
	std::array<button, 3> m_array_of_buttons; ///< Tablica przycisków z nazwami poziomów trudnoœci
	std::array <sf::ConvexShape, 2> m_triangles; ///< Tablica dwóch trójk¹tów równobocznych

public:

	/** Konstruktor klasy @ref state_settings
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	*/
	state_settings(state_machine& machine, sf::RenderWindow& window);

	/** Przes³oniêta metoda wirtualna klasy @ref state_settings
	* Zbiera informacje o wydarzeniach.
	*/
	void poll_events() override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_settings
	* Aktualizuje stan rozgrywki uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time) override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Rysuje i wyœwietla w oknie gry napis "Select difficulty" oraz nazwê wybranego poziomu trudnoœci.
	*/
	void render() override;

};

#endif