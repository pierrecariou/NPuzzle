#ifndef NODE_HPP
# define NODE_HPP

#include <vector>

class Node
{
	public:
		Node();
		Node(int &g);
		~Node();
		Node(const Node &obj);

		void	manhattanDistance();
		void	show() const;

		Node	*up() const;
		Node	*down() const;
		Node	*left() const;
		Node	*right() const;

		bool	comp(const Node &obj) const;

		// Attributes
		std::vector<std::vector<int>> grid;
		int g;
		int h; //heuristic
		int f;
		const Node *parent;	
};

#endif
