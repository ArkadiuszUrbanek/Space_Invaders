/** @file*/

#ifndef STATE_SUBMIT_SCORE_HPP
#define STATE_SUBMIT_SCORE_HPP

#include "state_base.hpp"
#include "button.hpp"

#include <string>
#include <array>

/** Klasa-stan podsumowanie wyniku.*/

class state_submit_score final : public state_base {
private:

	std::array <sf::ConvexShape, 2> m_triangles; ///< Tablica dwóch trójk¹tów równobocznych
	
	sf::Font m_font; ///< Czcionka
	std::array <char, 3> m_nickname_letters; ///< Tablica trzech liter, które tworz¹ pseudonim gracza 
	size_t m_selected_nickname_letter_index = 0; ///< Indeks wybranej litery w tablicy liter pseudonimu gracza

	sf::Vector2f m_single_letter_box_size; ///< Rozmiar boxa jednej litery
	std::array<button, 3> m_letter_buttons; ///< Tablica trzech przycisków z literami, które tworz¹ pseudonim gracza 

	button m_game_over_button; ///< Przycisk z tekstem "Game over!"
	button m_score_button; ///< Przycisk z tekstem "Your final score is: "
	button m_enter_nickname_button; ///< Przycisk z tekstem "Enter your nickname"

	/** Prywatna, statyczna metoda klasy @ref state_submit_score
	* £aduje czcionkê.
	* @return Obiekt klasy Font
	*/
	static sf::Font load_font();

public:

	/** Konstruktor klasy @ref state_submit_score
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	*/
	state_submit_score(state_machine& machine, sf::RenderWindow& window);

	/** Przes³oniêta metoda wirtualna klasy @ref state_submit_score
	* Zbiera informacje o wydarzeniach.
	*/
	void poll_events() override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_submit_score
	* Aktualizuje stan rozgrywki uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time) override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Rysuje i wyœwietla w oknie gry napisy oraz pseudonim gracza.
	*/
	void render() override;

};

#endif