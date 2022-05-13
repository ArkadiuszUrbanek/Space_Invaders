/** @file*/

#ifndef INTRUDER_HPP
#define INTRUDER_HPP

#include "collidable.hpp"
#include "projectile.hpp"

/** Klasa reprezentujaca intrudera, dziedzicz¹ca po @ref collidable.*/

class intruder final : public collidable {
public:

	/// Silny typ wyliczeniowy okreœlaj¹cy rodzaj intrudera
	enum class intruder_type : char { 
		OCTOPUS = 10, ///< Oœmiornica
		CRAB = 20, ///< Krab
		SQUID = 30 ///< Ka³amarnica
	};

private:

	const intruder_type m_intruder_type; ///< Zmienna przechowuj¹ca informacjê o rodzaju intrudera
	sf::RectangleShape m_sprite; ///< Kszta³t prostok¹ta, na który jest nak³adana odpowiednia tekstura intrudera
	
	/// Silny typ wyliczeniowy okreœlaj¹cy fazê odrywania siê intrudera od grupy
	enum class detached_intruder_state : unsigned char { 
		FIRST_PHASE = 1, ///< Pierwsza faza odrywania siê od grupy
		SECOND_PHASE, ///< Druga faza odrywania siê od grupy
		THIRD_PHASE ///< Trzecia faza odrywania siê od grupy
	};

	detached_intruder_state m_detached_intruder_state; ///< Zmienna przechowuj¹ca informacjê o aktualnej fazie odrywania siê intrudera

	bool m_alive = true; ///< Zmienna sygnalizuj¹ca czy dany intruder ¿yje

	bool m_detached = false; ///< Zmienna sygnalizuj¹ca czy dany intruder od³¹czy³ siê od grupy
	bool m_moving_left; ///< Zmienna sygnalizuj¹ca czy intruder od³¹czony od grupy porusza siê w lewo

public:

	/** Konstruktor klasy @ref intruder
	* @param[in] texture WskaŸnik na teksturê intrudera
	* @param[in] intruder_type Rodzaj intrudera
	*/
	intruder(sf::Texture* texture, intruder_type intruder_type);

	/** Metoda klasy @ref intruder
	* Przywraca pocz¹tkowe wartoœci pól klasy.
	*/
	void reset();

	/** Metoda klasy @ref intruder
	* Zwraca punkty za zestrzelenie intrudera.
	* @return Punkty za zestrzelenie intrudera
	*/
	unsigned int return_points();

	/** Metoda klasy @ref intruder
	* Sprawdza kolizjê intrudera z pociskiem.
	* @param[in] projectile Sta³a referencja do pocisku, z którym bêdzie badana kolizja
	* @return Wartoœæ true lub false
	*/
	bool projectile_collision(const projectile& projectile);

	/** Metoda klasy @ref intruder
	* Uaktualnia koordynaty obrazka intrudera.
	* @param[in] rect Sta³a referencja do obiektu klasy IntRect
	*/
	void update_texture_rect(const sf::IntRect& rect);

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder
	* Zwraca rodzaj intrudera.
	* @return Rodzaj intrudera
	*/
	const intruder_type& get_intruder_type() const { return m_intruder_type; }

	/** Metoda klasy @ref intruder
	* Przesuwa nieod³¹czonego intrudera w oknie gry o zadany wektor.
	* @param[in] distance Matematyczny wektor 
	*/
	void move(sf::Vector2f distance);

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder
	* Sprawdza czy intruder ¿yje.
	* @return Wartoœæ true lub false
	*/
	bool is_alive() const { return m_alive; }

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder
	* Sprawdza czy intruder od³¹czy³ siê od grupy.
	* @return Wartoœæ true lub false
	*/
	bool is_detached() const { return m_detached;  }

	/** Metoda inline klasy @ref intruder
	* Od³¹cza intrudera od grupy.
	*/
	void detach() { m_detached = true; m_detached_intruder_state = detached_intruder_state::FIRST_PHASE; }

	/** Metoda klasy @ref intruder
	* Przesuwa od³¹czonego intrudera w oknie gry o zadany wektor.
	* @param[in] distance Matematyczny wektor
	*/
	void move_detached(sf::Vector2f distance);

	/** Metoda inline klasy @ref intruder
	* Ustawia kierunek ruchu intrudera w lewo.
	*/
	void set_moving_left() { m_moving_left = true; }

	/** Metoda inline klasy @ref intruder
	* Ustawia kierunek ruchu intrudera w prawo.
	*/
	void set_moving_right() { m_moving_left = false; }

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder
	* Sprawdza czy od³¹czony od grupy intruder porusza siê w lewo.
	* @return Wartoœæ true lub false
	*/
	bool is_moving_left() const { return m_moving_left; }

	/** Metoda inline klasy @ref intruder
	* Zmienia kierunek ruchu od³¹czonego intrudera na przeciwny.
	*/
	void switch_moving_direction() { if (m_detached_intruder_state == detached_intruder_state::THIRD_PHASE) m_moving_left = !m_moving_left; }

	/** Niemodyfikuj¹ca metoda inline klasy @ref intruder
	* Zwraca aktualn¹ pozycjê intrudera.
	* @return Sta³y matematyczny wektor
	*/
	const sf::Vector2f& get_position() const { return m_sprite.getPosition(); }

	/** Przes³oniêta metoda wirtualna klasy @ref intruder
	* Ustawia pozycjê intrudera.
	* @param[in] position Nowa pozycja intrudera
	*/
	virtual void set_position(sf::Vector2f position) override;

	/** Przes³oniêta niemodyfikuj¹ca metoda wirtualna klasy @ref intruder
	* Rysuje intrudera w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	virtual void draw(sf::RenderWindow& window) const override;

};

#endif
