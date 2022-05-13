/** @file*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "state_machine.hpp"

/** Klasa tworz¹ca grê.*/

class game {
private:
	state_machine m_machine; ///< Maszyna stanów
	sf::RenderWindow m_window; ///< Okno gry

public:

	static constexpr unsigned char m_FPS_LIMIT = 75; ///< Limit klatek na sekundê
	static constexpr unsigned short int m_WINDOW_WIDTH = 800; ///< Szerokoœæ okna gry 
	static constexpr unsigned short int m_WINDOW_HEIGHT = 600; ///< Wysokoœæ okna gry

	/** Domyœlny konstruktor klasy @ref game*/
	game();

	/** Domyœlny destruktor klasy @ref game*/
	~game();

	/** Metoda klasy @ref game
	* Rozpoczyna grê.
	*/
	void run();

};

#endif