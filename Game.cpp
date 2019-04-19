#include "Game.h"

Game::Game() :
	m_window("Snake - Waz", sf::Vector2u(800, 600)),
	m_snake(m_world.GetBlockSize(), &m_textbox),
	m_world(sf::Vector2u(800, 600))
{
	m_clock.restart();
	srand(time(nullptr));
	m_elapsed = 0.0f;
	m_textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
	//m_textbox.Add("Ziarno generatora liczb losowych: " + std::to_string(time(NULL)));
	m_textbox.Add("Gra \"Snake 1.0\"");
	m_textbox.Add("Kierujesz strzalkami. Masz 3 zycia.");
	m_textbox.Add("Gdy dotkniesz wlasnego ogona, tracisz jedno.");
	m_textbox.Add("Gdy dotkniesz sciany, przegrywasz od razu.");
	m_textbox.Add("Powodzenia :-)");
}

Game::~Game() { }

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& m_snake.GetPhysicalDirection() != Direction::Down)
	{
		m_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& m_snake.GetPhysicalDirection() != Direction::Up)
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& m_snake.GetPhysicalDirection() != Direction::Right)
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& m_snake.GetPhysicalDirection() != Direction::Left)
	{
		m_snake.SetDirection(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();	//Aktualizuj zmiany okna
	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed >= timestep)
	{
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;
		if (m_snake.HasLost())
		{
			m_textbox.Add("KONIEC GRY! Wynik: "
				+ std::to_string((long long)m_snake.GetScore()));
			m_snake.Reset();
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw();	//Czysci okno

	//Rendery elementow ponizej
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textbox.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();		//Wyswietla nowa zawartosc okna na ekranie
}

Window * Game::GetWindow()
{
	return &m_window;
}

float Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart().asSeconds();
}