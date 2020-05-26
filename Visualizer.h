#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>//swap
#include "map.h"

class Visualizer
{
public:
	Visualizer();
	Visualizer(int x, int y);
	void go();

private:
	void calculateCellSize(sf::Vector2u fullWindowSize);
	void checkKeyPress();
	void checkMousePress();
	void renderFrame();

	void pauseUnpause();
	bool isPaused() const;
	void increaseFrequency();
	void decreaseFrequency();

	sf::Vector2u pixelsToCoords(int x, int y);
	sf::Vector2f coordsToPixels(int x, int y);

	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock RTC;
	sf::RectangleShape stamp;

	Map* map;
	int xSize, ySize;
	float boxX, boxY;
	float timestep, timestepBackup;//one of these is infinite at all times

};

