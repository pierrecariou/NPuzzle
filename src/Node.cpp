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

Node::Node(const Node &obj)
{
	for (std::vector<int> line : obj.grid)
		grid.push_back(line);
	g = obj.g;
	h = obj.h;
	f = obj.f;
	parent = nullptr;
}

bool	Node::comp(const Node &obj) const
{
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (grid[i][k] != obj.grid[i][k])
				return false;
		}
	}
	return true;
}

Node	*Node::up() const
{
	Node *up = new Node(*this);
	up->parent = this;
	up->g = g + 1;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (up->grid[i][k] == 0 && i == 0) {
				delete up;
				return nullptr;
			}
			if (up->grid[i][k] == 0) {
				up->grid[i - 1][k] = 0;
				up->grid[i][k] = grid[i - 1][k];
				goto finish;
			}
		}
	}
	finish:
	return up;
}

Node	*Node::down() const
{
	Node *down = new Node(*this);
	down->parent = this;
	down->g = g + 1;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (down->grid[i][k] == 0 && i == grid.size() - 1) {
				delete down;
				return nullptr;
			}
			if (down->grid[i][k] == 0) {
				down->grid[i + 1][k] = 0;
				down->grid[i][k] = grid[i + 1][k];
				goto finish;
			}
		}
	}
	finish:
	return down;
}

Node	*Node::left() const
{
	Node *left = new Node(*this);
	left->parent = this;
	left->g = g + 1;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (left->grid[i][k] == 0 && k == 0) {
				delete left;
				return nullptr;
			}
			if (left->grid[i][k] == 0) {
				left->grid[i][k - 1] = 0;
				left->grid[i][k] = grid[i][k - 1];
				goto finish;
			}
		}
	}
	finish:
	return left;
}

Node	*Node::right() const
{
	Node *right = new Node(*this);
	right->parent = this;
	right->g = g + 1;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (right->grid[i][k] == 0 && k == grid.size() - 1) {
				delete right;
				return nullptr;
			}
			if (right->grid[i][k] == 0) {
				right->grid[i][k + 1] = 0;
				right->grid[i][k] = grid[i][k + 1];
				goto finish;
			}
		}
	}
	finish:
	return right;
}

void	Node::manhattanDistance()
{
	int x;
	int y;
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid.size(); k++) {
			if (grid[i][k] != 0 && grid[i][k] != (k + 1 + (grid.size() * i))) { // tile is away from its goal state
				//std::cout << grid[i][k]<< std::endl;
				y = (grid[i][k] - 1) / grid.size(); // y goal
				x = (grid[i][k] - 1 ) % grid.size(); // x goal
				//std::cout << " y: " << y << " x: " << x << std::endl;
				//std::cout << " i: " <<i << " k: " << k<<  std::endl;
				//std::cout << " DIFF: "<< std::abs(y - i) + std::abs(x - k) << std::endl;;
				h+=(std::abs(y - i) + std::abs(x - k));
			}
		}
	}
	f = g + h;
}

void	Node::show() const
{
	std::cout << std::endl;
	for (int i = 0; i < grid.size(); i++)
		std::cout << "-----";
	std::cout << "-" << std::endl;
	for (int i = 0; i < grid.size(); i++) {
		std::cout << "|";
		for (int k = 0; k < grid.size(); k++) {
			if (grid[i][k] == 0)
				std::cout << " [] |";
			else if (grid[i][k] > 9)
				std::cout << " " << grid[i][k] << " |";
			else
				std::cout << " " << grid[i][k] << "  |";
		}
		std::cout << std::endl;
		for (int i = 0; i < grid.size(); i++)
			std::cout << "-----";
		std::cout << "-" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "g: " <<  g << std::endl;
	std::cout << "h: " <<  h << std::endl;
	std::cout << "f: " <<  f << std::endl << std::endl;
}
