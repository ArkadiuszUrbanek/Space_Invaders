/** @file*/

#ifndef UFO_HPP
#define UFO_HPP

#include "collidable.hpp"
#include "projectile.hpp"
#include "animation.hpp"
#include "game.hpp"

/** Klasa reprezentujaca statek ufo, za zestrzelenie którego gracz otrzymuje punkty i ¿ycie. Dziedziczy po @ref collidable.*/

class ufo final : public collidable {
private:
	const unsigned int m_points = 100; ///< Liczba punktów przyznawanych graczowi za zestrzelenie ufo
	bool m_points_returned = true; ///< Zmienna sygnalizuj¹ca czy punkty za zestrzelenie ufo zosta³y ju¿ zwrócone

	sf::Texture m_ufo_spritesheet; ///< Tekstura statku ufo
	sf::RectangleShape m_sprite; ///< Kszta³t prostok¹ta, na który jest nak³adana odpowiednia tekstura statku ufo
	
	animation m_animation; ///< Obiekt klasy @ref animation

	bool m_moving_right = false; ///< Zmienna sygnalizuj¹ca czy statek ufo porusza siê w prawo

	const float m_default_speed = 200.0f; ///< Domyœlna prêdkoœæ statku ufo
	float m_speed = m_default_speed; ///< Aktualna prêdkoœæ statku ufo

	/// Silny typ wyliczeniowy okreœlaj¹cy status statku ufo
	enum class ufo_state : char { 
		ALIVE, ///< Ufo ¿yje
		DESTROYED, ///< Ufo jest zniszczone
		WAITING ///< Ufo oczekuje na pojawienie siê na ekranie
	};

	ufo_state m_state = ufo_state::WAITING; ///< Aktualny status statku ufo

	const sf::Time m_min_time_interval_between_appearances = sf::seconds((game::m_WINDOW_WIDTH + m_box.x) / m_speed); ///< Minimalny czas, w którym ufo doleci do drugiego koñca okna gry
	const sf::Time m_default_time_interval_between_appearances = m_min_time_interval_between_appearances + sf::seconds(10.0f); ///< Domyœlny czas miêdzy kolejnymi pojawieniami siê ufo w oknie gry + czas, w którym ufo doleci do drugiego koñca okna gry
	sf::Time m_currrent_time_interval_between_appearances = m_default_time_interval_between_appearances; ///< Aktualny czas miêdzy kolejnymi pojawieniami siê ufo w oknie gry + czas, w którym ufo doleci do drugiego koñca okna gry

	sf::Time m_time_of_movement = sf::seconds(0.0f); ///< Czas ruchu statku ufo w oknie gry

	/** Prywatna metoda statyczna klasy @ref ufo
	* £aduje teksturê statku ufo.
	* @return Obiekt klasy Texture
	*/
	static sf::Texture load_ufo_spritesheet();

	/** Prywatna metoda klasy @ref ufo
	* Aktualizuje pozycjê statku ufo w oknie gry.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update_position(sf::Time delta_time);

public:

	/** Domyœlny konstruktor klasy @ref ufo*/
	ufo();

	/** Metoda klasy @ref ufo
	* Przywraca pocz¹tkowe wartoœci pól klasy.
	*/
	void reset();

	/** Metoda klasy @ref ufo
	* Zwraca punkty za zestrzelenie statku ufo.
	* @return Punkty za zestrzelenie statku ufo
	*/
	unsigned int return_points();

	/** Metoda klasy @ref ufo
	* Aktualizuje wszelkie informacje o statku ufo.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time);

	/** Metoda klasy @ref ufo
	* Sprawdza kolizjê statku ufo z pociskiem gracza.
	* @param[in] projectile Pocisk gracza, z którym jest sprawdzana kolizja
	* @return Wartoœæ true lub false
	*/
	bool projectile_collision(const projectile& projectile);

	/** Przes³oniêta metoda wirtualna klasy @ref ufo
	* Ustawia pozycjê statku ufo.
	* @param[in] position Nowa pozycja statku ufo
	*/
	virtual void set_position(sf::Vector2f position) override;

	/** Przes³oniêta niemodyfikuj¹ca metoda wirtualna klasy @ref ufo
	* Rysuje statek ufo w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	virtual void draw(sf::RenderWindow& window) const override;

};

#endif

