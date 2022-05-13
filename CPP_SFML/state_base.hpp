/** @file*/

#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "SFML/Graphics.hpp"

class state_machine;

/** Klasa abstrakcyjna, stanowi¹ca bazê dla ka¿dego stanu, który wystêpuje w programie.*/

class state_base {
protected:
	state_machine& m_machine; ///< Referencja do maszyny stanów
	sf::RenderWindow& m_window; ///< Referencja do okna gry
	sf::Event m_event; ///< Wydarzenie, które jest zwi¹zane z myszk¹ lub klawiatur¹

public:

	/** Konstruktor klasy @ref state_base
	* @param[in] machine Maszyna stanów
	* @param[in] window Okno gry
	*/
	state_base(state_machine& machine, sf::RenderWindow& window);

	/** Metoda czysto wirtualna klasy @ref state_base
	* Zbiera informacje o wydarzeniach.
	*/
	virtual void poll_events() = 0;

	/** Metoda czysto wirtualna klasy @ref state_base
	* Atualizuje stan uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	virtual void update(sf::Time delta_time) = 0;

	/** Metoda czysto wirtualna klasy @ref state_base
	* Rysuje i wyœwietla w oknie gry elementy nale¿¹ce do stanu.
	*/
	virtual void render() = 0;

};

#endif
