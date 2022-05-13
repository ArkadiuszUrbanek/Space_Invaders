/** @file*/

#ifndef STATE_MAIN_MENU_HPP
#define STATE_MAIN_MENU_HPP

#include "state_base.hpp"
#include "menu.hpp"

/** Klasa-stan menu g³ówne.*/

class state_main_menu final : public state_base {
private:

	menu m_menu; ///< Obiekt klasy @ref menu

public:

	/** Konstruktor klasy @ref state_main_menu
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	*/
	state_main_menu(state_machine& machine, sf::RenderWindow& window);

	/** Przes³oniêta metoda wirtualna klasy @ref state_main_menu
	* Zbiera informacje o wydarzeniach.
	*/
	void poll_events() override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_main_menu
	* Aktualizuje stan main menu uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time) override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_main_menu
	* Rysuje i wyœwietla w oknie gry opcje klasy @ref menu.
	*/
	void render() override;

};

#endif