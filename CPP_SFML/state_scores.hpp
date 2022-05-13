/** @file*/

#ifndef STATE_SCORES_HPP
#define STATE_SCORES_HPP

#include "state_base.hpp"
#include "scores.hpp"
#include "button.hpp"
#include "game.hpp"

#include <array>

#define MAX_RECORDS_PER_PAGE 10
#define RECORD_OUTLINE_THICKNESS 4.0f
#define NUMBER_OF_HEADERS 4

/** Klasa-stan wyniki.*/

class state_scores final : public state_base {
private:

	/** Struktura reprezentuj¹ca wiersz w tabeli*/
	struct record {
		sf::RectangleShape m_inner_rect; ///< Kolor wewnêtrzny wiersza
		sf::RectangleShape m_outer_rect; ///< Kolor zewnêtrzny wiersza (obramowanie)

		/** Konstruktor struktury @ref record
		* @param[in] inner_rect_color Kolor wewnêtrzny wiersza
		*/
		record(sf::Color inner_rect_color) {
			m_outer_rect.setFillColor(sf::Color::Black);
			m_outer_rect.setSize({ game::m_WINDOW_WIDTH - 50.0f, 48.0f });
			m_outer_rect.setOrigin({ m_outer_rect.getSize().x / 2, m_outer_rect.getSize().y / 2 });

			m_inner_rect.setFillColor(inner_rect_color);
			m_inner_rect.setSize({ m_outer_rect.getSize().x - RECORD_OUTLINE_THICKNESS, m_outer_rect.getSize().y - RECORD_OUTLINE_THICKNESS });
			m_inner_rect.setOrigin({ m_inner_rect.getSize().x / 2, m_inner_rect.getSize().y / 2 });
		}

		/** Metoda struktury @ref record
		* Ustawia pozycjê wiersza.
		* @param[in] record_position Pozycja wiersza
		*/
		void set_position(sf::Vector2f record_position) {
			m_outer_rect.setPosition(record_position);
			m_inner_rect.setPosition(record_position);

		}
		
		/** Niemodyfikuj¹ca metoda struktury @ref record
		* Zwraca rozmiar wiersza, bior¹c pod uwagê szerokoœæ obramowania.
		* @return Sta³y rozmiar wiersza
		*/
		const sf::Vector2f get_size() const {
			return m_outer_rect.getSize();
		}

		/** Niemodyfikuj¹ca metoda struktury @ref record
		* Rysuje wiersz w oknie gry.
		* @param[in,out] window Referencja do okna gry
		*/
		void draw(sf::RenderWindow& window) const {
			window.draw(m_outer_rect);
			window.draw(m_inner_rect);

		}

	};

	sf::Font m_font; ///< Czcionka

	scores m_scores; ///< Obiekt klasy @ref scores

	sf::Text m_number_of_page; ///< Teskt bêd¹cy numeracj¹ strony
	std::array <sf::ConvexShape, 2> m_triangles; ///< Tablica dwóch trójk¹tów równobocznych

	unsigned short m_index_of_current_page = 0; ///< Indeks aktualnej strony
	unsigned short m_number_of_pages; ///< Liczba stron
	unsigned short m_number_of_records_on_the_last_page; ///< Liczba wyników wyœwietlanych na ostatniej stronie

	std::array<record, MAX_RECORDS_PER_PAGE> m_array_of_records; ///< Tablica wierszy tabeli
	std::array<sf::Text, NUMBER_OF_HEADERS> m_array_of_headers; ///< Tablica nag³ówków kolumn tabeli
	std::array<sf::RectangleShape, NUMBER_OF_HEADERS> m_array_of_horizontal_rects; ///< Tablica pionowych dzia³ek tabeli
	std::array<std::array<sf::Text, NUMBER_OF_HEADERS>, MAX_RECORDS_PER_PAGE> m_matrix_of_textes; ///< Macierz tekstów do wyœwietlenia w tabeli

	/** Prywatna metoda klasy @ref state_scores
	* Uaktualnia zawartoœæ m_matrix_of_textes.
	* @param[in] row_index Indeks wiersza z m_matrix_of_textes
	*/
	void update_page_contents(size_t row_index);

public:

	/** Konstruktor klasy @ref state_scores
	* @param[in] machine Referencja do maszyny stanów
	* @param[in] window Referencja do okna gry
	*/
	state_scores(state_machine& machine, sf::RenderWindow& window);

	/** Przes³oniêta metoda wirtualna klasy @ref state_scores
	* Zbiera informacje o wydarzeniach.
	*/
	void poll_events() override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_scores
	* Aktualizuje stan rozgrywki uwzglêdniaj¹c czas jaki up³yna³.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time) override;

	/** Przes³oniêta metoda wirtualna klasy @ref state_playing
	* Rysuje i wyœwietla w oknie gry wype³nion¹ tabelê wyników oraz numeracjê stron.
	*/
	void render() override;

};

#endif