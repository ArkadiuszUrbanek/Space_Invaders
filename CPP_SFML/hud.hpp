/** @file*/

#ifndef HUD_HPP
#define HUD_HPP

#include <array>
#include <vector>

#include "animation.hpp"
#include "button.hpp"

/** Klasa tworz¹ca hud w trakcie rozgrywki.*/

class hud {
private:

	std::array<sf::RectangleShape, 2> m_bars; ///< Tablica dwóch bia³ych belek oddzielaj¹cych hud od obszaru, na którym toczy sie gra
	std::array<sf::RectangleShape, 2> m_fillers; ///< Tablica dwóch czarnych prostok¹tów, które stanowi¹ t³o hudu

	std::vector<sf::RectangleShape> m_hearts; ///< Tablica serc, które reprezentuj¹ ¿ycia gracza
	sf::Texture m_heart_texture; ///< Tekstura serca
	animation m_heart_animation; ///< Obiekt klasy @ref animation, który animuje tablicê serc

	sf::Font m_font; ///< Czcionka napisów hudu 
	
	std::array<button, 6> m_hud_top_textes; ///< Tablica górnych tekstów hudu
	button m_hud_bottom_text; ///< Dolny tekst hudu

	unsigned short m_level = 0; ///< Poziom gry
	unsigned int m_score = 0; ///< Wynik gracza
	unsigned int m_highscore = 0; ///< Najlepszy wynik uzyskany przez gracza

	/** Prywatna metoda statyczna klasy @ref hud
	* £aduje czcionkê.
	* @return Za³adowana czcionka
	*/
	static sf::Font load_font();

	/** Prywatna metoda statyczna klasy @ref hud
	* £aduje Teksturê serca.
	* @return Za³adowana tekstura serca
	*/
	static sf::Texture load_heart_spritesheet();

public:

	static constexpr unsigned short m_HUD_TOP_HEIGHT = 50; ///< Wysokoœæ górnej czêœci hudu
	static constexpr unsigned short m_HUD_BOTTOM_HEIGHT = 30; ///< Wysokoœæ dolnej czêœci hudu

	/** Konstruktor klasy @ref hud
	* @param[in] lives Pocz¹tkowa liczba ¿yæ gracza
	* @param[in] level Pocz¹tkowy numer poziomu
	*/
	hud(unsigned char lives, unsigned short level);

	/** Metoda klasy @ref hud
	* Uaktualnia liczbê ¿yæ gracza.
	* @param[in] lives Liczba ¿yæ gracza
	*/
	void update_lives(const unsigned char& lives);

	/** Metoda klasy @ref hud
	* Uaktualnia wynik gracza.
	* @param[in] score Wynik gracza
	*/
	void update_score(const unsigned int& score) { m_score = score; }

	/** Metoda klasy @ref hud
	* Uaktualnia poziom gry, zwiêkszaj¹c go o jeden.
	*/
	void update_level() { m_level++; }

	/** Metoda klasy @ref hud
	* Rysuje hud w oknie gry.
	* @param[in,out] window Okno gry
	*/
	void draw(sf::RenderWindow& window);

};

#endif
