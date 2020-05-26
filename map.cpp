#include "map.h"

Map::Map()
	:Map(10,10)
{
}

Map::Map(int x, int y)
	: xSize(x), ySize(y)
{
	createAllCells();
	giveAllCellsNeighbors();
}

void Map::createAllCells()
{
	allCells.reserve(ySize);
	for (size_t y = 0; y < ySize; y++)//for each row
	{
		allCells.push_back(std::vector<std::shared_ptr<Cell>>());
		allCells[y].reserve(xSize);
		for (size_t x = 0; x < xSize; x++)//for each column
		{
			allCells[y].push_back(std::make_shared<Cell>());
		}
	}
}

void Map::giveAllCellsNeighbors()//give all cells a list of neighbors, so it can calculate it's next state
{
	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)//for each existing cell
		{
			giveCellNeighbors(x,y);
		}
	}
}

void Map::giveCellNeighbors(int x, int y)
{
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)//for all 9 cells in a 3x3 area
		{
			if (isInBounds(j, i) and !(i == y and j == x)) allCells[y][x]->giveNeighbor(allCells[i][j]);
		}
	}
}

bool Map::isInBounds(int x, int y) const
{
	if (x < 0 or x >= xSize or y < 0 or y >= ySize) return false;
	return true;
}

void Map::runAllCells()
{
	for (auto row : allCells)
		for (auto cell : row)
			cell->calculateNextState();
}

void Map::updateAllCells()
{
	for (auto row : allCells)
		for (auto cell : row)
			cell->update();
}


void Map::simulationStep()
{
	runAllCells();
	updateAllCells();
}

bool Map::getCellState(int x, int y) const
{
	if (!isInBounds(x, y)) throw std::out_of_range("Trying to get a nonexistant cell. You shouldn't do that.");
	return allCells[y][x]->getState();
}

bool Map::hasCellChanged(int x, int y) const
{
	if (!isInBounds(x, y)) throw std::out_of_range("Trying to get a nonexistant cell. You shouldn't do that.");
	return allCells[y][x]->hasChanged();
}



void Map::forceCellFlip(int x, int y)
{
	if (!isInBounds(x, y)) throw std::out_of_range("Trying to get a nonexistant cell. You shouldn't do that.");
	else allCells[y][x]->forceFlip();
}
