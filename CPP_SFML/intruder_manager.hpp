/** @file*/

#ifndef INTRUDER_MANAGER_HPP
#define INTRUDER_MANAGER_HPP

#include <array>
#include <vector>

#include "intruder.hpp"
#include "animation.hpp"

#define INTRUDER_ROWS 6
#define INTRUDER_COLUMNS 8

/** Klasa zarz¹dzaj¹ca grup¹ intruderów.*/

class intruder_manager {
private:
	std::array<sf::Texture, 3> m_intruders_textures; ///< Tablica tekstur intruderów
	std::array<animation, 3> m_intruders_animations; ///< Tablica animacji intruderów

	std::vector<std::vector<intruder>> m_intruders_matrix; ///< Macierz intruderów

	unsigned short m_number_of_living_intruders_in_row[INTRUDER_ROWS]; ///< Tablica ¿ywych intruderów w rzêdzie, z którego ma nastapiæ oderwanie losowego intrudera
	unsigned short m_index_of_lowest_living_row; ///< Indeks najni¿szego rzêdu, w którym ¿yje co najmniej jeden intruder
	bool m_detach_intruder = true; ///< Zmienna sygnalizuj¹ca czy nale¿y oderwaæ intrudera od grupy

	const unsigned short m_default_number_of_enemies_alive = INTRUDER_COLUMNS * INTRUDER_ROWS; ///< Domyœlna liczba ¿ywych intruderów
	unsigned short m_number_of_enemies_alive = m_default_number_of_enemies_alive; ///< Liczba ¿ywych intruderów
	unsigned short m_number_of_enemies_alive_in_group = m_default_number_of_enemies_alive; ///< Liczba ¿ywych intruderów, którzy siê nie oderwali od grupy
	
	bool m_group_moving_left = true; ///< Zmienna sygnalizuj¹ca czy grupa intruderów porusza siê w lewo
	bool m_group_moving_down = false; ///< Zmienna sygnalizuj¹ca czy dany grupa intruderów porusza siê w dó³

	sf::Clock m_step_clock; ///< Zegar zliczaj¹cy czas od ostatniego kroku grupy intruderów

	const sf::Time m_default_step_gap = sf::seconds(0.5f); ///< Domyœlny czas pomiêdzy kolejnymi krokami intruderów
	sf::Time m_step_gap = m_default_step_gap; ///< Aktualny czas pomiêdzy kolejnymi krokami intruderów

	sf::Clock m_intruders_shot_clock; ///< Zegar zliczaj¹cy czas od ostatniego wystrzelenia pocisku ze strony intruderów

	const sf::Time m_default_time_interval_between_shots = sf::seconds(6.0f); ///< Domyœlny czas pomiêdzy kolejnymi wystrza³ami pocisków ze strony intruderów
	sf::Time m_time_interval_between_shots = m_default_time_interval_between_shots; ///< Aktualny czas pomiêdzy kolejnymi wystrza³ami pocisków ze strony intruderów
	
	bool m_points_returned = true; ///< Zmienna sygnalizuj¹ca czy zwrócono punkty za zestrzelenie intrudera
	unsigned int m_points = 0; ///< Punkty za zestrzelenie intrudera

	/** Prywatna metoda statyczna klasy @ref intruder_manager
	* £aduje tekstury intruderów.
	* @return Tablica za³adowanych tekstur intruderów
	*/
	static std::array<sf::Texture, 3> load_textures();

	/** Prywatna niemodyfikuj¹ca metoda klasy @ref intruder_manager
	* Sprawdza czy dany intruder nie wyszed³ poza okno gry.
	* @param[in] intruder Przeciwnik, którego po³o¿enie jest sprawdzane
	* @return Wartoœæ true lub false
	*/
	bool test_intruder_position(const intruder& intruder) const;

	/** Prywatna metoda klasy @ref intruder_manager
	* Uaktualnia czas miêdzy kolejnymi krokami intruderów. Wraz ze zmiejszaj¹c¹ siê liczb¹ intruderów czas miêdzy kolejnymi krokami jest skracany.
	*/
	void update_step_gap();

	/** Prywatny, niemodyfikuj¹cy szablon metody klasy @ref intruder_manager
	* Losuje liczbê z podanego przedzia³u.
	* @tparam[in] low Dolny zakres
	* @tparam[in] high Górny zakres
	* @return Sta³a referencja do wylosowanej liczby
	*/
	template<typename T>
	const T& get_number_in_range(T low, T high) const;

public:

	/** Konstruktor klasy @ref intruder_manager
	* @param[in] step_gap Czas pomiêdzy kolejnymi krokami intruderów
	* @param[in] time_interval_between_shots Czas pomiêdzy kolejnymi wystrza³ami pocisków ze strony intruderów
	*/
	intruder_manager(sf::Time step_gap, sf::Time time_interval_between_shots);

	/** Metoda klasy @ref intruder_manager
	* Przywraca pocz¹tkowe wartoœci pól klasy.
	*/
	void reset();

	/** Metoda klasy @ref intruder_manager
	* Uaktualnia wszelkie informacje o grupie intruderów.
	*/
	void update();

	/** Metoda klasy @ref intruder_manager
	* Zwraca punkty za zestrzelenie intrudera.
	* @return Punkty za zestrzelenie intrudera
	*/
	unsigned int return_points();

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder_manager
	* Sprawdza czy jacykolwiek intruderzy jeszcze ¿yj¹.
	* @return Wartoœæ true lub false
	*/
	bool are_intruders_alive() const { return m_number_of_enemies_alive > 0; }

	/** Metoda klasy @ref intruder_manager
	* Sprawdza czy nastapi³a kolizja pocisku z grup¹ intruderów.
	* @param[in] projectile Sta³a referencja do pocisku, z którym bêdzie badana kolizja
	* @return Wartoœæ true lub false
	*/
	bool projectile_collision(const projectile& projectile);

	/** Niemodyfikuj¹ca metoda klasy @ref intruder_manager
	* Tworzy pionowe boxy kolizujne na podstawie aktualnie ¿yj¹cych intruderów.
	* @return Tablica boxów kolizyjnych
	*/
	const std::vector<sf::FloatRect> get_collision_boxes() const;

	/** Metoda klasy @ref intruder_manager
	* Zwraca pozycjê intrudera, który oddaje strza³. W przypadku, gdy ¿aden intruder nie odda³ strza³u lub wszyscy intruderzy ju¿ nie ¿yj¹ zwracana jest wartoœæ {-1, -1}.
	* @return Matematyczny wektor
	*/
	sf::Vector2f get_shooter_position();

	/** Niemodyfikuj¹ca metoda klasy @ref intruder_manager
	* Rysuje grupê intruderów w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	void draw(sf::RenderWindow& window) const;

};

#endif