/*************************************************************
 * File              : NPuzzle.cpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 30.07.2022
 * Last Modified Date: 30.07.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#include "NPuzzle.hpp"

NPuzzle::NPuzzle(std::string filename)
	: start(new Node()), goal(new Node())
{
	openFile(filename);
	fillGoal();
}

NPuzzle::~NPuzzle()
{
	delete start;
	delete goal;
}

void	NPuzzle::openFile(const std::string &filename)
{
	std::ifstream file(filename);
	if (file.is_open()) {
		for (std::string line; std::getline(file, line);) {
			if (std::isdigit(line[0])) {
				size = std::stoi(line);
				break;
			}
		}
		for (std::string line; std::getline(file, line);) {
			appendLine(line);
		}
	}
}

void	NPuzzle::appendLine(const std::string &line)
{
	std::vector<int> vec;
    std::istringstream iss(line);
	for (std::string elem; iss; iss >> elem) {
		if (!elem.empty())
			vec.push_back(std::stoi(elem));	
	}
	start->grid.push_back(vec);
}

void	NPuzzle::fillGoal()
{
	int num = 1;
	std::vector<int> vec;
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++)
			vec.push_back(num++);
		goal->grid.push_back(vec);
		vec.clear();
	}
}

/*
void	NPuzzle::show() const
{
	std::cout << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << "-----";
	std::cout << "-" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << "|";
		for (int k = 0; k < size; k++) {
			if (start->grid[i][k] == 0)
				std::cout << " [] |";
			else if (start->grid[i][k] > 9)
				std::cout << " " << start->grid[i][k] << " |";
			else
				std::cout << " " << start->grid[i][k] << "  |";
		}
		std::cout << std::endl;
		for (int i = 0; i < size; i++)
			std::cout << "-----";
		std::cout << "-" << std::endl;
	}
	std::cout << std::endl;
}
*/

// A* Algorithm //
void	NPuzzle::solve()
{
	openList.push_back(start);
	
	start->manhattanDistance();
	while (!openList.empty())
	{
		Node *current = findLeastF();
		current->show();
		openList.remove(current);
		closedList.push_back(current);
		std::list<Node *> nextNodes = fromCurrent(*current);

		for (auto next : nextNodes) {
			next->show();
			if (next->comp(*goal))
				return ;
		}
	}
}

Node	*NPuzzle::findLeastF()
{
	Node *found {openList.front()};

	for (Node *elem : openList) {
		if  (elem->f < found->f)
			found = elem;
	}
	return found;
}

std::list<Node *>	NPuzzle::fromCurrent(const Node &current)
{			
	std::list<Node *> nodes;
	Node *next;

	if ((next = current.up()))
		nodes.push_back(next);
	if ((next = current.down()))
		nodes.push_back(next);
	if ((next = current.left()))
		nodes.push_back(next);
	if ((next = current.right()))
		nodes.push_back(next);

	return nodes;
}
