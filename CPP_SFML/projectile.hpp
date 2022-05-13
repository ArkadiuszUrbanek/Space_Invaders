/** @file*/

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "collidable.hpp"

/** Klasa reprezentujaca wszystkie pociski w grze. Dziedziczy po @ref collidable.*/

class projectile final : public collidable {
private:

	sf::Texture m_projectile_texture; ///< Tekstura pocisku
	sf::RectangleShape m_sprite; ///< Kszta³t prostok¹ta, na który jest nak³adana tekstura pocisku

	float m_speed; ///< Prêdkoœæ pocisku

	bool m_destroyed = false; ///< Zmienna sygnalizuj¹ca czy pocisk zosta³ zniszczony

	bool m_moving_up; ///< Zmienna sygnalizuj¹ca czy pocisk porusza siê w górê

public:

	/** Konstruktor klasy @ref projectile
	* @param[in] position Pozycja startowa pocisku
	* @param[in] speed Prêdkoœæ pocisku
	*/
	projectile(sf::Vector2f position, float speed);

	/** Metoda klasy @ref projectile
	* Aktualizuje pozycjê pocisku w oknie gry.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update_position(sf::Time delta_time);

	/** Przes³oniêta metoda wirtualna klasy @ref projectile
	* Ustawia pozycjê pocisku.
	* @param[in] position Nowa pozycja pocisku
	*/
	virtual void set_position(sf::Vector2f position) override;

	/** Niemodyfikuj¹ca metoda inline klasy @ref projectile
	* Sprawdza czy pocisk porusza siê w górê.
	* @return Wartoœæ true lub false
	*/
	bool is_moving_up() const { return m_moving_up; }

	/** Niemodyfikuj¹ca metoda inline klasy @ref projectile
	* Sprawdza czy pocisk zosta³ zniszczony.
	* @return Wartoœæ true lub false
	*/
	bool is_destroyed() const { return m_destroyed; }

	/** Metoda inline klasy @ref projectile
	* Niszczy pocisk.
	*/
	void destroy() { m_destroyed = true; }

	/** Niemodyfikuj¹ca metoda klasy @ref projectile
	* Zwraca aktualn¹ pozycjê pocisku.
	* @return Wektor matematyczny
	*/
	sf::Vector2f get_position() const;

	/** Metoda klasy @ref projectile
	* Sprawdza kolizjê pocisku z innym pociskiem.
	* @param[in] other_projectile Pocisk, z którym jest sprawdzana kolizja
	* @return Wartoœæ true lub false
	*/
	bool projectile_collision(const projectile& other_projectile);

	/** Niemodyfikuj¹ca metoda inline klasy @ref projectile
	* Zwraca globalne koordynaty pocisku.
	* @return Sta³y obiekt klasy FloatRect
	*/
	const sf::FloatRect get_global_bounds() const { return m_sprite.getGlobalBounds(); }

	/** Przes³oniêta niemodyfikuj¹ca metoda wirtualna klasy @ref projectile
	* Rysuje pocisk w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	virtual void draw(sf::RenderWindow& window) const override;

};

#endif