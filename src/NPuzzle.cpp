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
	goal->grid[size - 1][size -1] = 0;
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
/*
void	NPuzzle::solve()
{
	Node *current;
	Node *find_node;
	closedList.push_back(start);
	
	start->manhattanDistance();
	while ((current = closedList.back()) && current->h != 0)
	{
		current->show();
		openList.remove(current);
		std::list<Node *> nextNodes = fromCurrent(*current);

		for (Node *next : nextNodes) {
			if (next->exists(openList))
				continue ;
			next->manhattanDistance();
			if (closedList.back()->g == next->g) {
				if (closedList.back()->f <= next->f)
					continue ;
				else
					closedList.pop_back();
			}
			closedList.push_back(next);
		}
		openList.splice(openList.begin(), nextNodes);
	}
	current->show();
}
*/

void	NPuzzle::solve()
{
	//int i = 0;
	Node *current = nullptr;
	Node *find_node;
	openList.push_back(start);
	
	start->manhattanDistance();
	while (!openList.empty() && (current = findLeastF(current)) && current->h != 0)
	{
		current->show();
		openList.remove(current); // OPEN: States to be examined and candidates to expansion
		closedList.push_back(current); // CLOSED: States already selected by the algorithm, compared to the solution, and expanded 
		//std::list<Node *> nextNodes = fromCurrent(*current);
		openList.splice(openList.begin(), fromCurrent(*current, openList, closedList));
		
		std::cout << "open size: " << openList.size() <<  std::endl;
		std::cout << "close size: " << closedList.size() <<  std::endl;
/*
		for (Node *next : nextNodes) {
			if (next->exists(closedList))
				continue ;
			next->manhattanDistance();
			if (closedList.back()->g == next->g) {
				if (closedList.back()->f <= next->f)
					continue ;
				else
					closedList.pop_back();
			}
			closedList.push_back(next);
		}
		*/
	//	openList.splice(openList.begin(), nextNodes);
	}
	closedList.push_back(current);
	current->show();
}

Node	*NPuzzle::findLeastF(Node *current)
{
	Node *found = nullptr;
	std::list<Node *>::iterator first;

	if (current == nullptr)
		return openList.back();
	for (std::list<Node *>::iterator it=openList.begin(); it != openList.end(); it++) {
		if ((*it)->g - current->g == 1) {
			found = *it;
			first = it;
			break ;
		}
	}
	for (std::list<Node *>::iterator it=first; it != openList.end(); it++) {
		if  ((*it)->f < found->f && (*it)->g - current->g == 1) // Check the movement cost
			found = *it;
	}
	return found;
}

/*
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
*/

std::list<Node *>	NPuzzle::fromCurrent(const Node &current, const std::list<Node *> &openList, const std::list<Node *> &closedList)
{			
	std::list<Node *> nodes;
	Node *next;
	Node *oldNext;

	if ((next = current.up()) && !next->exists(closedList)) {
		if (oldNext = next->exists(openList, 1)) {
			oldNext->g = next->g;
			oldNext->f = next->f;
		}
		else {
			nodes.push_back(next);
			next->manhattanDistance();
		}
	}
	if ((next = current.down()) && !next->exists(closedList)) {
		if (oldNext = next->exists(openList, 1)) {
			oldNext->g = next->g;
			oldNext->f = next->f;
		}
		else {
			nodes.push_back(next);
			next->manhattanDistance();
		}

	}
	if ((next = current.left()) && !next->exists(closedList)) {
		if (oldNext = next->exists(openList, 1)) {
			oldNext->g = next->g;
			oldNext->f = next->f;
		}
		else {
			nodes.push_back(next);
			next->manhattanDistance();
		}

	}
	if ((next = current.right()) && !next->exists(closedList)) {
		if (oldNext = next->exists(openList, 1)) {
			oldNext->g = next->g;
			oldNext->f = next->f;
		}
		else {
			nodes.push_back(next);
			next->manhattanDistance();
		}

	}

	return nodes;
}
