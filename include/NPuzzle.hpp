/*************************************************************
 * File              : NPuzzle.hpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 30.07.2022
 * Last Modified Date: 30.07.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

#include "Node.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>

/*
struct Node
{
	std::vector<std::vector<int>> grid;
	int h; //heuristic
	Node *parent;
};
*/

class NPuzzle {
	public:
		NPuzzle(std::string filename);
		~NPuzzle();

	//	void	show() const;
		void	solve();

		int	size;

	//private:
		void	openFile(const std::string &filename);
		void	appendLine(const std::string &line);
		Node	*findLeastF(Node *current);
		void	fillGoal();
	//	std::list<Node *>	fromCurrent(const Node &current);
		std::list<Node *>	fromCurrent(const Node &current, const std::list<Node *> &openList, const std::list<Node *> &closedList);

		// Attributes
		Node *start;
		Node *goal;
		std::list<Node *> openList; // Nodes that have been discovered, but not explored yet
		std::list<Node *> closedList; // Nodes that have already been explored
};

#endif
