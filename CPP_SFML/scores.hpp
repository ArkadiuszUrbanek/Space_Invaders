/** @file*/

#ifndef SCORES_HPP
#define SCORES_HPP

#include <fstream>
#include <string>
#include <vector>
#include <tuple>

/** Klasa s³u¿¹ca do zapisu i odczytu wyników.*/

using trio = std::tuple<std::string, std::string, unsigned int>;

class scores {
private:

	std::vector<trio> m_scores; ///< Tablica trójek ( pseudonim gracza, poziom trudnoœci, wynik )

	const std::string m_file_path; ///< Œcie¿ka do pliku z wynikami
	const char m_separator; ///< Separator u¿yty do oddzielania wartoœci w pliku .csv

	std::fstream m_file_stream; ///< Strumieñ WE/WY plikowy

	bool m_scores_sorted = false; ///< Zmienna sygnalizuj¹ca czy wyniki zosta³y posortowane
	bool m_all_scores_were_loaded = false; ///< Zmienna sygnalizuj¹ca czy wszystkie wyniki zosta³y za³adowane

public:

	/** Konstruktor klasy @ref scores
	* @param[in] file_path Œcie¿ka do pliku z wynikami
	* @param[in] separator Separator u¿yty do oddzielania wartoœci w pliku .csv
	*/
	scores(std::string file_path = "scores.csv", const char separator = ';');

	/** Metoda klasy @ref scores
	* Dopisuje wynik gracza do tablicy wyników i do pliku.
	* @param[in] nickname Pseudonim gracza
	* @param[in] difficulty Poziom trudnoœci
	* @param[in] score Uzyskany wynik
	*/
	void append_score(std::string nickname, std::string difficulty, unsigned int score);

	/** Metoda klasy @ref scores
	* £aduje wyniki z pliku do tablicy wyników.
	*/
	void load_scores();

	/** Metoda klasy @ref scores
	* Sortuje tablicê wyników po wynikach malej¹co.
	*/
	void sort_scores_desc();

	/** Metoda klasy @ref scores
	* Zwraca najlepszy wynik z tablicy wyników.
	* @return Najlepszy wynik
	*/
	const unsigned int get_highest_score();

	/** Niemodyfikuj¹ca metoda inline klasy @ref scores
	* Zwraca d³ugoœæ tablicy wyników.
	* @return D³ugoœæ tablicy wyników
	*/
	size_t get_number_of_scores() const { return m_scores.size(); }

	/** Przeci¹¿ony operator tablicowy klasy @ref scores
	* Zwraca (tylko do odczytu) trójkê ( pseudonim gracza, poziom trudnoœci, wynik ) z tablicy wyników.
	* @return Trójka ( pseudonim gracza, poziom trudnoœci, wynik )
	*/
	const trio& operator [](size_t index);

};

#endif