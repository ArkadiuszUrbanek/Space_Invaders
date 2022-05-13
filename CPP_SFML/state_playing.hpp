/** @file*/

#ifndef STATE_PLAYING_HPP
#define STATE_PLAYING_HPP

#include "state_base.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "shield.hpp"
#include "ufo.hpp"
#include "intruder_manager.hpp"
#include "hud.hpp"

/** Klasa-stan rozgrywka.*/

class state_playing final : public state_base {
private:

	/// Silny typ wyliczeniowy okreœlaj¹cy stany w jakich mo¿e znaleŸæ siê gra
	enum class game_states : unsigned char { 
		CHANGING_LEVEL, ///< Zmiana poziomu
		NORMAL_GAMEPLAY, ///< Normalna rozgrywka
		RESPAWNING_PLAYER, ///< Odradzanie gracza
		GAME_OVER ///< Koniec gry
	};

	game_states m_current_game_state = game_states::CHANGING_LEVEL; ///< Aktualny stan gry

	unsigned short m_level; ///< Aktualny numer poziomu
	const unsigned char m_max_player_lives; ///< Maksymalna iloœæ ¿yæ gracza
	unsigned char m_player_lives; ///< Aktualna ilosæ ¿yæ gracza
	static unsigned int m_player_score; ///< Aktualny wynik gracza

	hud m_hud; ///< Obiekt klasy @ref hud

	player m_player; ///< Obiekt klasy @ref player
	std::vector<projectile> m_array_of_players_projectiles; ///< Tablica pocisków gracza

	std::array<shield, 4> m_array_of_shields; ///< Tablica czterech os³on

	ufo m_ufo; ///< Obiekt klasy @ref ufo

	intruder_manager m_intruder_manager; ///< Obiekt klasy @ref intruder_manager
	std::vector<projectile> m_array_of_intruders_projectiles; ///< Tablica pocisków intruderów

	sf::Texture m_background_image; ///< Tekstura t³a gry
	sf::Sprite m_background; ///< T³o gry

	sf::Font m_font; ///< Czcionka
	button m_text_button; ///< Obiekt klasy @ref button
	sf::Time m_time_passed = sf::seconds(0.0f); ///< Czas jaki up³yn¹³ od rozpoczêcia zmiany poziomu

	/** Prywatna metoda klasy @ref state_playing
	* Ustawia na nowo wszystkie obiekty w grze.
	*/
	void load_level();

	/** Prywatna metoda klasy @ref state_playing
	* £aduje nowy poziom gry.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void switching_level(sf::Time delta_time);

public:

	/** Statyczna metoda inline klasy @ref state_playing
	* @return Wynik gracza
	*/
	static unsigned int get_player_score() { return m_player_score; }

	/** Konstruktor klasy @ref state_playing
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	*/
	state_playing(state_machine& machine, sf::RenderWindow& window);

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Zbiera informacje o wydarzeniach.
	*/
	void poll_events() override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Aktualizuje stan rozgrywki uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time) override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Rysuje i wyœwietla w oknie gry hud, statek gracza, os³ony, pociski, ufo oraz intruderów.
	*/
	void render() override;
};

#endif