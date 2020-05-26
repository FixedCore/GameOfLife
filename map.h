#pragma once
#include "cell.h"
#include <vector>//vector
#include <memory>//shared_ptr


class Map
{
public:
	Map();
	Map(int x, int y);

	void simulationStep();
	bool getCellState(int x, int y) const;
	bool hasCellChanged(int x, int y) const;
	void forceCellFlip(int x, int y);
private:
	size_t xSize, ySize;
	std::vector<std::vector<std::shared_ptr<Cell>>> allCells;
	void createAllCells();
	void giveAllCellsNeighbors();
	void giveCellNeighbors(int x, int y);
	bool isInBounds(int x, int y) const;
	void runAllCells();
	void updateAllCells();
};