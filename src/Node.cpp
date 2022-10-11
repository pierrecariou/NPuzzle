/*************************************************************
 * File              : Node.cpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 11.10.2022
 * Last Modified Date: 11.10.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#include "Node.hpp"
#include <iostream>

Node::Node()
	: g(0), h(0)
{
}

Node::Node(int &g)
	: g(g), h(0)
{
}

Node::~Node()
{
}

void	Node::manhattanDistance()
{
	int x;
	int y;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (grid[i][k] != 0 && grid[i][k] != (k + 1 + (grid.size() * i))) { // tile is away from its goal state
				//std::cout << grid[i][k]<< std::endl;
				y = (grid[i][k] - 1) / grid.size();
				x = (grid[i][k] - 1 ) % grid.size();
				//std::cout << " y: " << y << " x: " << x << std::endl;
				//std::cout << " i: " <<i << " k: " << k<<  std::endl;
				//std::cout << " DIFF: "<< std::abs(y - i) + std::abs(x - k) << std::endl;;
				h+=(std::abs(y - i) + std::abs(x - k));
			}
		}
	}
	std::cout << std::endl << "h: " <<  h << std::endl;
}
