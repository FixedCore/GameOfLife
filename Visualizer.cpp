#include "Visualizer.h"


Visualizer::Visualizer()
	:Visualizer(10,10)
{
}

Visualizer::Visualizer(int x, int y)
	:window(new sf::RenderWindow(sf::VideoMode(1200, 900), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close)),
	map(new Map(x, y)), xSize(x), ySize(y), timestep(100.0f), timestepBackup(INFINITY)
{
	calculateCellSize(window->getSize());
	window->setFramerateLimit(60);
}

void Visualizer::go()
{
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				checkKeyPress();
				break;
			case sf::Event::MouseButtonPressed:
				checkMousePress();
				break;
			case sf::Event::Resized:
				calculateCellSize(window->getSize());
				break;
			default:
				break;
			}
		}
		window->clear();
		if (RTC.getElapsedTime().asMilliseconds() >= timestep)
		{
			map->simulationStep();
			RTC.restart();
		}
			renderFrame();
		window->display();
	}
}

void Visualizer::calculateCellSize(sf::Vector2u fullWindowSize)
{
	
	boxX = fullWindowSize.x / xSize;
	boxY = fullWindowSize.y / ySize;
	stamp.setSize(sf::Vector2f(boxX, boxY));
	stamp.setFillColor(sf::Color::Black);
	stamp.setOutlineThickness(std::max((float)boxX / 30.0f, 1.0f));
	stamp.setOutlineColor(sf::Color(125, 125, 125));
	/*auto s = coordsToPixels(3, 5);
	std::cout << "Full window size: " << fullWindowSize.x << '\t' << fullWindowSize.y << std::endl;;
	std::cout << "Coords of 3,5 box: " << s.x << '\t' << s.y << std::endl;
	std::cout << "Size of 3,5 box:" << boxX << '\t' << boxY << std::endl;*/
}

void Visualizer::checkKeyPress()
{
	switch (event.key.code)
	{
	case sf::Keyboard::P:
		pauseUnpause();
		break;
	case sf::Keyboard::Up:
		increaseFrequency();
		break;
	case sf::Keyboard::Down:
		decreaseFrequency();
		break;
	default:
		break;
	}
	std::cout << "Timestep:" << timestep << std::endl;
}

void Visualizer::checkMousePress()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2u cordPosition = pixelsToCoords(event.mouseButton.x, event.mouseButton.y);
		map->forceCellFlip(cordPosition.x, cordPosition.y);
	}
}

void Visualizer::renderFrame()
{
	for (size_t x = 0; x < xSize; x++)
	{
		for (size_t y = 0; y < ySize; y++)
		{
			stamp.setPosition(coordsToPixels(x, y));
			stamp.setFillColor(map->getCellState(x, y) == 1 ? sf::Color::White : sf::Color::Black);
			window->draw(stamp);
		}
	}
}

void Visualizer::pauseUnpause()
{
	std::swap(timestep, timestepBackup);
}

bool Visualizer::isPaused() const
{
	return timestepBackup < timestep;
}

void Visualizer::increaseFrequency()
{
	if (isPaused()) return;
	int orderOfMagnitude = floor(log10f(timestep));
	timestep += powf(10, orderOfMagnitude);
}

void Visualizer::decreaseFrequency()
{
	if (isPaused()) return;
	if (timestep <= 1) return;
	int orderOfMagnitude = floor(log10f(timestep));
	if (timestep == powf(10, orderOfMagnitude)) timestep -= powf(10, orderOfMagnitude - 1);
	else timestep -= powf(10, orderOfMagnitude);
	
}

sf::Vector2u Visualizer::pixelsToCoords(int x, int y)
{
	return sf::Vector2u(x / boxX, y / boxY);
}

sf::Vector2f Visualizer::coordsToPixels(int x, int y)
{
	return sf::Vector2f(x * boxX, y * boxY);
}
