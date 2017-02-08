//Window.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 05.02.2017
//--------------------------

#ifndef Window_hpp_included
#define Window_hpp_included

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include "Snake.hpp"

class Window 
{
	Game mGame;
	sf::RenderWindow mWindow;
	sf::RenderStates mStates;

	enum
	{
		mCellSize = 20
	};

public:
	Window()
		: mWindow{ sf::VideoMode{ mGame.Width() * mCellSize, mGame.Height() * mCellSize }, "Snake" }
	{
		mWindow.setVerticalSyncEnabled(false);
		mStates.transform.scale(static_cast<float>(mCellSize), static_cast<float>(mCellSize));
	}

	int Run()
	{
		typedef std::chrono::steady_clock ClockT;
		ClockT::time_point Tp = ClockT::now();
		for(;;)
		{
			for(sf::Event Event; mWindow.pollEvent(Event);)
			{
				if(Event.type == Event.Closed)
				{
					mWindow.close();
					return 0;
				}
				else if(Event.type == Event.KeyPressed)
				{
					switch(Event.key.code)
					{
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						mGame.ChangeDirection(Cardinals::Top);
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						mGame.ChangeDirection(Cardinals::Right);
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						mGame.ChangeDirection(Cardinals::Bottom);
						break;
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						mGame.ChangeDirection(Cardinals::Left);
						break;
					}
				}
			}

			const ClockT::time_point Now = ClockT::now();
			if(std::chrono::duration_cast<std::chrono::duration<double, std::chrono::seconds::period>>(Now - Tp).count() > 0.1)
			{
				Tp = Now;
				mGame.Tick();
			}

			mWindow.clear(sf::Color::White);
			mWindow.draw(mGame, mStates);
			mWindow.display();
		}
	}
};

#endif // !Window_hpp_included
