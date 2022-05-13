/** @file*/

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "SFML/Graphics.hpp"
#include "state_base.hpp"

#include <memory>
#include <stack>

/** Klasa zarz¹dzaj¹ca stanami w programie.*/

class state_machine {
public:
	enum command : char;

private:
	std::stack<std::unique_ptr<state_base>> m_stack_of_ptr_states; ///< Stos inteligentnych wskaŸników na stany w programie
	std::unique_ptr<state_base> m_ptr_new_state; ///< Inteligentny wskaŸnik na nowy stan, który ma trafiæ na stos
	bool m_wait; ///< Zmienna sygnalizuj¹ca czy maszyna stanów ma wykonywaæ okreœlone polecenie

	state_machine::command m_command; ///< Polecenie dla maszyny stanów

public:

	/// Silny typ wyliczeniowy okreœlaj¹cy dostêpne polecenia dla maszyny stanów
	enum command : char { 
		ADD, ///< Polecenie powoduj¹ce dodanie na stos nowy stan
		REMOVE, ///< Polecenie powoduj¹ce usuniêcie ze szczytu stosu stanu 
		REPLACE ///< Polecenie bêd¹ce po³¹czeniem polecenia ADD i REMOVE
	};

	/** Domyœlny konstruktor klasy @ref state_machine*/
	state_machine();

	/** Statyczna metoda klasy @ref state_machine
	* @param[in] state Inteligentny wskaŸnik na stan bazowy
	* @param[in] command Polecenie dla maszyny stanów
	*/
	void run_state(std::unique_ptr<state_base> state, state_machine::command command);

	/** Metoda klasy @ref state_machine
	* Usuwa aktualny stan ze stosu.
	*/
	void remove_state();

	/** Metoda klasy @ref state_machine
	* Wykonuje operacje na stosie, które s¹ zwi¹zane z aktualnie wydanym poleceniem.
	*/
	void process_state_changes();

	/** Metoda klasy @ref state_machine
	* Wywo³uje metodê poll_events stanu ze szczytu stosu.
	*/
	void poll_events();

	/** Metoda klasy @ref state_machine
	* Wywo³uje metodê update stanu ze szczytu stosu.
	*/
	void update(sf::Time delta_time);

	/** Metoda klasy @ref state_machine
	* Wywo³uje metodê render stanu ze szczytu stosu.
	*/
	void render();

	/** Statyczny szablon metody klasy @ref state_machine
	* Zwraca inteligentny wskaŸnik na nowo utworzony stan.
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	* @return Inteligentny wskaŸnik na nowo utworzony stan
	*/
	template <typename T>
	static std::unique_ptr<T> create_state(state_machine& machine, sf::RenderWindow& window);

};

#endif
