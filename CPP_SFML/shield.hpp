/** @file*/

#ifndef SHIELD_HPP
#define SHIELD_HPP

#include "collidable.hpp"
#include "projectile.hpp"

/** Klasa reprezentuj¹ca os³ony, za którymi mo¿e schowaæ siê gracz. Dziedziczy po klasie @ref collidable. Pojedyncza os³ona jest podzielona na dwanaœcie sekcji, które s¹ kwadratami lub trójk¹tami.*/

class shield final : public collidable {
private:

	sf::Texture m_square_texture; ///< Tekstura kwadratu
	sf::Texture m_triangle_texture; ///< Tekstura trójk¹ta

	/// Silny typ wyliczeniowy okreœlaj¹cy rodzaj sekcji os³ony
	enum class section_style { 
		square, ///< Kwadrat
		slope_0, ///< Trójk¹t obrócony rogiem w lewo
		slope_90, ///< Trójk¹t obrócony rogiem w prawo
		slope_180, ///< Trójk¹t odwrócony do góry nogami i obrócony rogiem w prawo
		slope_270 ///< Trójk¹t odwrócony do góry nogami i obrócony rogiem w lewo
	};

	/** Struktura przechowuj¹ca informacje o danej sekcji os³ony*/
	struct shield_section {
		sf::RectangleShape m_sprite; ///< Kszta³t prostok¹ta, na który jest nak³adana tekstura kwadratu lub tekstura trójk¹ta
		shield::section_style m_style; ///< Rodzaj sekcji os³ony
		bool m_destroyed; ///< Zmienna sygnalizuj¹ca czy sekcja zosta³a zniszczona
	};
	
	static constexpr unsigned int m_TOTAL_NUMBER_OF_ROWS = 3; ///< Liczba rzêdów sekcji os³ony
	static constexpr unsigned int m_TOTAL_NUMBER_OF_COLUMNS = 4; ///< Liczba kolumn sekcji os³ony

	shield_section m_array_of_shield_sections[m_TOTAL_NUMBER_OF_ROWS][m_TOTAL_NUMBER_OF_COLUMNS]; ///< Macierz informacji o wszystkich sekcjach os³ony

public:

	/** Domyœlny konstruktor klasy @ref shield*/
	shield();

	/** Metoda klasy @ref shield
	* Przywraca pocz¹tkowe wartoœci pól klasy.
	*/
	void reset();

	/** Przes³oniêta metoda wirtualna klasy @ref shield
	* Ustawia pozycjê os³ony.
	* @param[in] position Nowa pozycja os³ony
	*/
	virtual void set_position(sf::Vector2f position) override;

	/** Przes³oniêta niemodyfikuj¹ca metoda wirtualna klasy @ref shield
	* Rysuje os³onê w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	virtual void draw(sf::RenderWindow& window) const override;

	/** Metoda klasy @ref shield
	* Sprawdza kolizjê os³ony z boxami kolizyjnymi intruderów.
	* @param[in] collsion_boxes Boxy kolizyjne
	*/
	void intruders_collision(const std::vector<sf::FloatRect>& collsion_boxes);

	/** Metoda klasy @ref shield
	* Sprawdza kolizjê os³ony z pociskiem.
	* @param[in] projectile Pocisk, z którym jest badana kolizja
	*/
	void projectile_collision(projectile& projectile);

};

#endif
