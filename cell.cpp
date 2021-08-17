#include "cell.h"

Cell::Cell()
	:Cell(0)
{
}

Cell::Cell(bool initialState)
	:state(initialState?alive:dead), nextState(undefined)
{
}

Cell::Cell(std::vector<std::shared_ptr<Cell>> neighborsToAdd)
	:Cell(0)
{
	giveMultipleNeighbors(neighborsToAdd);
}

void Cell::giveNeighbor(std::shared_ptr<Cell> neighbor)
{
	neighbors.push_back(neighbor);
}

void Cell::giveMultipleNeighbors(std::vector<std::shared_ptr<Cell>> neighborsToAdd)
{
	for (auto neighbor : neighborsToAdd)
	{
		giveNeighbor(neighbor);
	}
}

int Cell::getState() const
{
	return state==alive;
}

void Cell::calculateNextState()
{
	int neighborCount = getLivingNeighborCount();

	switch (state)
	{
	case dead:
		checkNextStateDead(neighborCount);
		break;
	case alive:
		checkNextStateAlive(neighborCount);
		break;
	default:
		throw std::domain_error("The cell is neither dead nor alive. Odd.");
		break;
	}
	
}

void Cell::update()
{
	state = nextState;
	nextState = undefined;
}

bool Cell::hasChanged() const
{
	return hasChangedOnLastTurn;
}

bool Cell::forceFlip()
{
	state = state == alive ? dead : alive;
	return state == alive;
}

void Cell::checkNextStateAlive(int n)
{
	if (n <= LIVE_UNDERPOPULATION or n >= LIVE_OVERPOPULATION)
	{
		nextState = dead;
		hasChangedOnLastTurn = true;
	}
	else
	{
		nextState = alive;
		hasChangedOnLastTurn = false;
	}
	
}

void Cell::checkNextStateDead(int n)
{
	if (n == DEAD_ANIMATE)
	{
		nextState = alive;
		hasChangedOnLastTurn = true;
	}
	else
	{
		nextState = dead;
		hasChangedOnLastTurn = false;
	}
}

int Cell::getLivingNeighborCount()
{
	unsigned int neighborSum = 0;
	for (auto n : neighbors)
	{
		if (!n.expired())
			neighborSum += n.lock()->getState();
	}
	return neighborSum;
}
