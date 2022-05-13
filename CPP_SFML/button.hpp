/** @file*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

/** Klasa reprezentuj¹ca przycisk, który siê sk³ada z prostok¹ta i tekstu.*/

class button {
private:
	sf::RectangleShape m_button; ///< Obiekt klasy RectangleShape, który odpowiada za kolor przycisku
	sf::Text m_text; ///< Obiekt klasy Text, który odpowiada za tekst na przycisku

public:
	/** Domyœlny konstruktor klasy @ref button */
	button() = default;

	/** Konstruktor klasy @ref button
	* @param[in] font Referencja do czcionki
	* @param[in] text Tekst na przycisku
	* @param[in] character_size Rozmiar liter tekstu na przycisku
	* @param[in] text_color Kolor tekstu na przycisku
	* @param[in] text_style Styl tekstu na przycisku
	* @param[in] button_color Kolor przycisku
	*/
	button(sf::Font& font, std::string text, unsigned int character_size, sf::Color text_color = sf::Color::White, sf::Text::Style text_style = sf::Text::Style::Regular, sf::Color button_color = sf::Color::Black);

	/** Konstruktor klasy @ref button
	* @param[in] font Referencja do czcionki
	* @param[in] character_size Rozmiar liter tekstu na przycisku
	* @param[in] text_color Kolor tekstu na przycisku
	* @param[in] text_style Styl tekstu na przycisku
	* @param[in] button_color Kolor przycisku
	*/
	button(sf::Font& font, unsigned int character_size, sf::Color text_color = sf::Color::White, sf::Text::Style text_style = sf::Text::Style::Regular, sf::Color button_color = sf::Color::Black);

	/** Domyœlny destruktor klasy @ref button */
	~button() = default;

	/** Niemodyfikuj¹ca metoda klasy @ref button
	* @return Sta³a referencja do obiektu klasy Vector2f, przechowuj¹cego wymiary przycisku
	*/
	const sf::Vector2f& get_button_size() const;

	/** Niemodyfikuj¹ca metoda klasy @ref button
	* @return Sta³a referencja do obiektu klasy Vector2f, przechowuj¹cego po³o¿enie przycisku na ekranie
	*/
	const sf::Vector2f& get_button_position() const;

	/** Metoda klasy @ref button
	* Ustawia napis na przycisku.
	* @param[in] text Nowy napis na przycisku
	*/
	void set_button_text(std::string text);

	/** Metoda klasy @ref button
	* Zmienia kolor tekstu na przycisku.
	* @param[in] new_text_color Nowy kolor tekstu na przycisku
	*/
	void set_button_text_color(sf::Color new_text_color);

	/** Metoda klasy @ref button
	* Zmienia pozycjê przycisku w oknie gry.
	* @param[in] button_position Nowa pozycja przycisku w oknie gry
	*/
	void set_button_position(sf::Vector2f button_position);

	/** Niemodyfikuj¹ca metoda klasy @ref button
	* Rysuje przycisk w oknie gry.
	* @param[in,out] window Referencja do okna gry
	*/
	void draw_button(sf::RenderWindow& window) const;

	/** Niemodyfikuj¹ca metoda klasy @ref button
	* Sprawdza czy kursor myszy znajduje siê na przycisku.
	* @param[in] window Referencja do okna gry
	* @return Wartoœæ true lub false
	*/
	bool is_mouse_over(const sf::RenderWindow& window) const;
};

#endif
