#pragma once
#include <vector>//vector
#include <memory>//shared_ptr, weak_ptr
class Cell
{
public:
	Cell();
	Cell(bool initialState);
	Cell(std::vector<std::shared_ptr<Cell>> neighborsToAdd);
	void giveNeighbor(std::shared_ptr<Cell> neighbor);
	void giveMultipleNeighbors(std::vector<std::shared_ptr<Cell>> neighborsToAdd);
	int getState() const;
	void calculateNextState();
	void update();
	bool hasChanged() const;
	bool forceFlip();

private:
	enum cellState
	{
		dead = 0,
		alive = 1,
		undefined = 2
	};

	void checkNextStateAlive(int n);
	void checkNextStateDead(int n);
	int getLivingNeighborCount();

	std::vector<std::weak_ptr<Cell>> neighbors;
	cellState state;
	cellState nextState;
	bool hasChangedOnLastTurn = false;


	static const unsigned int LIVE_UNDERPOPULATION = 1, LIVE_OVERPOPULATION = 4;
	static const unsigned int DEAD_ANIMATE = 3;
};

