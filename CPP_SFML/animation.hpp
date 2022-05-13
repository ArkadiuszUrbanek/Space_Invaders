/** @file*/

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

/** Klasa zmieniaj¹ca obrazek w okreœlonych odstêpach czasu.*/

class animation {
private:
	sf::IntRect m_image_rect; ///< Obiekt klasy IntRect, który przechowuje informacjê o aktualnych koordynatach obrazka  

	const sf::Vector2u m_image_count; ///< Sta³y obiekt klasy Vector2u, informuj¹cy o liczebnoœci obrazków w cyklu animacji 
	sf::Vector2u m_current_image; ///< Obiekt klasy Vector2u, informuj¹cy o aktualnym rzêdzie i kolumnie, w którym znajduje siê obrazek 

	sf::Time m_total_time; ///< Obiekt klasy Time, s³u¿¹cy do zliczania czasu, który up³yn¹³ od pocz¹tku kolejnej klatki animacji
	const sf::Time m_switch_time; ///< Sta³y obiekt klasy Time, przechowuj¹cy informacjê o tym ile czasu ma byæ wyœwietlana jedna klatka animacji

public:

	/** Konstruktor trójargumentowy klasy @ref animation
	* @param[in] texture WskaŸnik na teksturê
	* @param[in] image_count Iloœæ obrazków w rzêdzie oraz iloœæ rzêdów obrazków
	* @param[in] switch_time Czas wyœwietlania jednej klatki animacji
	*/
	animation(sf::Texture* texture, sf::Vector2u image_count, sf::Time switch_time);

	/** Metoda klasy @ref animation
	* Aktualizuje czas, który up³yna³ od ostatniego wywo³ania metody update i w razie koniecznoœci zmienia obrazek na kolejny w podanym rzêdzie.
	* @param[in] row Rz¹d obrazków
	* @param[in] delta_time Czas, który up³yn¹³ od ostatniego wywo³ania metody update
	*/
	void update(int row, sf::Time delta_time);

	/** Metoda klasy @ref animation
	* Wymusza zmianê obrazka.
	* @param[in] row Rz¹d obrazków
	*/
	void force_update(int row);

	/** Metoda klasy @ref animation
	* Resetuje animacjê. Ustawia na pierwszy obrazek animacji.
	* @param[in] row Rz¹d obrazków
	*/
	void reset(int row);

	/** Metoda klasy @ref animation
	* Zwraca koordynaty aktualnego obrazka.
	* @return sta³y obiekt klasy IntRect, który przechowuje informacjê o koordynatach aktualnego obrazka 
	*/
	const sf::IntRect& get_image_rect() const { return m_image_rect; }

};

#endif
