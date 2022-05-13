/** @file*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "collidable.hpp"
#include "projectile.hpp"
#include "animation.hpp"

/** Klasa reprezentujaca statek gracza, dziedzicz¹ca po @ref collidable.*/

class player final : public collidable {
private:

	sf::Texture m_player_texture; ///< Tekstura statku gracza

	sf::RectangleShape m_sprite_top; ///< Górna czêœæ statku gracza
	sf::RectangleShape m_sprite_bottom; ///< Dolna czêœæ statku gracza

	sf::Texture m_player_death_spritesheet; ///< Tekstura wybuchaj¹cego statku gracza
	animation m_player_death_animation; ///< Animacja wybuchu statku gracza
	sf::RectangleShape m_sprite_player_destroyed; ///< Kszta³t prostok¹ta, na który jest nak³adana jest tekstura wybuchu statku gracza

	const float m_max_speed = 100.0f; ///< Domyœlna prêdkoœæ maksymalna statku gracza
	const float m_acceleration = 81.25f; ///< Domyœlne przyspieszenie statku gracza
	const sf::Time m_time_to_reach_max_speed = sf::seconds(m_max_speed / m_acceleration); ///< Czas potrzebny do osi¹gniêcia prêdkoœci maksymalnej

	sf::Time m_time_of_movement = sf::seconds(0.0f); ///< Aktualny czas ruchu statku gracza w okreœlon¹ stronê

	bool m_alive = true; ///< Zmienna sygnalizuj¹ca czy gracz ¿yje

	bool m_stopped = true; ///< Zmienna sygnalizuj¹ca czy gracz zatrzyma³ swój statek w miejscu
	bool m_moving_right = false; ///< Zmienna sygnalizuj¹ca czy statek gracza porusza siê w prawo
	bool m_moving_left = false; ///< Zmienna sygnalizuj¹ca czy statek gracza porusza siê w lewo

	const sf::Time m_time_interval_between_shots = sf::seconds(0.2f); ///< Czas prze³adowania dzia³a
	sf::Clock m_shot_clock; ///< Zegar zliczaj¹cy czas od momentu oddania nowego strza³u przez gracza
	bool m_shot_fired = false; ///< Zmienna sygnalizuj¹ca czy gracz odda³ strza³

	sf::Clock m_death_timer; ///< Zegar zliczaj¹cy czas od momentu zniszczenia statku gracza
	bool m_death_timer_restarted = false; ///< Zmienna sygnalizuj¹ca czy zegar odliczaj¹cy czas do odrodzenia gracza zosta³ uprzednio zrestartowany

	/** Prywatna metoda statyczna klasy @ref player
	* £aduje teksturê wybuchu gracza.
	* @return Tekstura wybuchu gracza
	*/
	static sf::Texture load_player_death_spritesheet();

	/** Prywatna metoda klasy @ref player
	* Aktualizuje pozycjê gracza w oknie gry.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update_position(sf::Time delta_time);

public:

	/** Konstruktor klasy @ref player
	* @param[in] speed Prêdkoœæ maksymalna gracza
	* @param[in] acceleration Przyspieszenie gracza
	* @param[in] time_interval_between_shots Czas prze³adowania dzia³a
	*/
	player(float speed, float acceleration, sf::Time time_interval_between_shots);

	/** Metoda klasy @ref player
	* Przywraca pocz¹tkowe wartoœci pól klasy.
	*/
	void reset();

	/** Metoda klasy @ref player
	* Odradza gracza.
	*/
	void respawn();

	/** Metoda klasy @ref player
	* Obs³uguje sterowanie statkiem gracza.
	*/
	void handle_input();

	/** Niemodyfikuj¹ca metoda inline klasy @ref player
	* Sprawdza czy gracz ¿yje.
	* @return Wartoœæ true lub false
	*/
	bool is_alive() const { return m_alive; }

	/** Metoda klasy @ref player
	* Sprawdza czy gracz w danej klatce wystrzeli³ pocisk. Je¿eli gracz wystrzeli³ pocisk to pod pole m_shot_fired jest podstawiana wartoœæ false.
	* @return Wartoœæ true lub false
	*/
	bool shot_fired();

	/** Metoda klasy @ref player
	* Aktualizuje wszelkie informacje o graczu.
	* @param[in] delta_time Czas miêdzy kolejnymi klatkami
	*/
	void update(sf::Time delta_time);

	/** Przes³oniêta metoda wirtualna klasy @ref player
	* Ustawia pozycjê statku gracza.
	* @param[in] position Nowa pozycja statku gracza
	*/
	virtual void set_position(sf::Vector2f position) override;

	/** Niemodyfikuj¹ca metoda klasy @ref player
	* Zwraca aktualn¹ pozycjê statku gracza.
	* @return Wektor matematyczny
	*/
	sf::Vector2f get_position() const;

	/** Niemodyfikuj¹ca metoda klasy @ref player
	* Zwraca aktualn¹ pozycje dzia³a statku gracza.
	* @return Wektor matematyczny
	*/
	sf::Vector2f get_gun_position() const;

	/** Metoda klasy @ref player
	* Sprawdza kolizjê statku gracza z boxami kolizyjnymi intruderów.
	* @param[in] collsion_boxes Boxy kolizyjne
	* @return Wartoœæ true lub false
	*/
	bool intruders_collision(const std::vector<sf::FloatRect>& collsion_boxes);

	/** Metoda klasy @ref player
	* Sprawdza kolizjê statku gracza z boxami kolizyjnymi intruderów.
	* @param[in] enemy_projectile Pocisk intrudera, z którym jest sprawdzana kolizja
	* @return Wartoœæ true lub false
	*/
	bool projectile_collision(const projectile& enemy_projectile);

	/** Przes³oniêta niemodyfikuj¹ca metoda wirtualna klasy @ref player
	* Rysuje statek gracza w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	virtual void draw(sf::RenderWindow& window) const override;

};

#endif
