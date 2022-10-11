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

void	NPuzzle::solve()
{
	openList.push_back(start);
	
	start->manhattanDistance();
}
