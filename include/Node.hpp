#ifndef NODE_HPP
# define NODE_HPP

#include <vector>

class Node
{
	public:
		Node();
		Node(int &g);
		~Node();

		void	manhattanDistance();

		// Attributes
		std::vector<std::vector<int>> grid;
		int g;
		int h; //heuristic
		int f;
		Node *parent;	
};

#endif
