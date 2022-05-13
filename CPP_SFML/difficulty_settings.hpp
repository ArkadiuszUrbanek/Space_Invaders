/** @file*/

#ifndef DIFFICULTY_SETTINGS_HPP
#define DIFFICULTY_SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <array>

/** Klasa przechowuj¹ca informacjê o ustawieniach gry.*/

class difficulty_settings {
public:

	/// Silny typ wyliczeniowy okreœlaj¹cy poziomy trudnoœci w grze
	enum class difficulty : char { 
		EASY, ///< £atwy
		NORMAL, ///< Normalny
		HARD ///< Trudny
	};

private:
	static difficulty m_selected_difficulty; ///< Zmienna statyczna przechowuj¹ca informacjê o aktualnie wybranym poziomie trudnoœci

	/** Struktura przechowuj¹ca ustawienia dla klasy @ref state_playing*/
	struct state_playing_settings {
		unsigned char m_max_player_lives; ///< Maksymalna iloœæ ¿yæ gracza
	};

	static std::array<std::pair<difficulty_settings::difficulty, state_playing_settings>, 3> m_state_playing_settings; ///< Tablica ustawieñ dla trzech poziomów trudnoœci dla klasy @ref state_playing 

	/** Struktura przechowuj¹ca ustawienia dla klasy @ref player*/
	struct player_settings {
		float m_player_max_speed; ///< Maksymalna prêdkoœæ gracza
		float m_player_acceleration; ///< Maksymalne przyœpieszenie gracza
		sf::Time m_time_interval_between_shots; ///< Czas prze³adowania dzia³a gracza
	};

	static std::array<std::pair<difficulty_settings::difficulty, player_settings>, 3> m_player_settings; ///< Tablica ustawieñ dla trzech poziomów trudnoœci dla klasy @ref player 

	/** Struktura przechowuj¹ca ustawienia dla klasy @ref intruder_manager*/
	struct intruder_manager_settings {
		sf::Time m_step_gap; ///< Odstêp czasu pomiêdzy kolejnymi krokami intruderów
		sf::Time m_time_interval_between_shots; ///< Odstêp czasu pomiêdzy kolejnymi pociskami wystrzelonymi przez intruderów
	};

	static std::array<std::pair<difficulty_settings::difficulty, intruder_manager_settings>, 3> m_intruder_manager_settings; ///< Tablica ustawieñ dla trzech poziomów trudnoœci dla klasy @ref intruder_manager 

public:

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca ustawienia dla aktualnie wybranego poziomu trudnoœci dla klasy @ref state_playing.
	* @return Para wartoœci: poziom trudnoœci i struktura z ustawieniami
	*/
	static std::pair<difficulty_settings::difficulty, state_playing_settings> get_state_playing_difficulty_settings();

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca ustawienia dla aktualnie wybranego poziomu trudnoœci dla klasy @ref player.
	* @return Para wartoœci: poziom trudnoœci i struktura z ustawieniami
	*/
	static std::pair<difficulty_settings::difficulty, player_settings> get_player_difficulty_settings();

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca ustawienia dla aktualnie wybranego poziomu trudnoœci dla klasy @ref intruder_manager.
	* @return Para wartoœci: poziom trudnoœci i struktura z ustawieniami
	*/
	static std::pair<difficulty_settings::difficulty, intruder_manager_settings> get_intruder_manager_difficulty_settings();

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca nazwê aktualnie wybranego poziomu trudnoœci.
	* @return Sta³y ³añcuch znaków
	*/
	static const std::string get_selected_difficulty_name(); 

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca nazwê przekazanego przez argument poziomu trudnoœci.
	* @param[in] difficulty Poziom trudnoœci
	* @return Sta³y ³añcuch znaków
	*/
	static const std::string get_difficulty_name(difficulty_settings::difficulty difficulty);

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zwraca aktualnie wybrany poziom trudnoœci.
	* @return Poziom trudnoœci
	*/
	static difficulty_settings::difficulty get_selected_difficulty() { return m_selected_difficulty;  }

	/** Metoda statyczna klasy @ref difficulty_settings
	* Zmienia poziom trudnoœci na taki jaki zosta³ przekazany jako argument.
	* @param[in] difficulty Poziom trudnoœci
	*/
	static void change_selected_difficulty_to(difficulty_settings::difficulty difficulty) { m_selected_difficulty = difficulty; }

};

#endif