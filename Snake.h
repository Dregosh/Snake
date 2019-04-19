#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Textbox.h"

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) { }
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int l_blockSize, Textbox* l_log);
	~Snake();

	//Metody pomocnicze
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	Direction GetPhysicalDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	void Lose();	//Obsluga przegranej
	void ToggleLost();

	void Extend();	//Zwiekszenie dlugosci weza
	void Reset();	//Reset na pozycje startowa

	void Move();	//Metoda obslugujaca ruch
	void Tick();	//Update method
	void Cut(int l_segments);	//Metoda przeciecia weza
	void Render(sf::RenderWindow& l_window);

private:
	void CheckCollision();	//Sprawdzenie kolizji
	
	SnakeContainer m_snakeBody;	//Wektor segmentow weza
	int m_size;			//rozmiar grafiki
	Direction m_dir;	//Aktualny kierunek weza
	int m_speed;		//Szybkosc weza
	int m_lives;		//Liczba zyc
	int m_score;		//Punktacja
	bool m_lost;		//Stan przegranej
	sf::RectangleShape m_bodyRect;	//Ksztalt renderowany
	Textbox* m_log;		//Wskaznik na pole tekstowe
};