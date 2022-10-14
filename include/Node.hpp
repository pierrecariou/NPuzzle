#ifndef NODE_HPP
# define NODE_HPP

#include <vector>
#include <list>

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
		bool	exists(const std::list<Node *> list) const;
		Node	*exists(const std::list<Node *> list, int flag) const;
		bool	existsWithSmallerG(const std::list<Node *> list) const;
//		int		cost(const Node &obj) const;

		// Attributes
		std::vector<std::vector<int>> grid;
		int g;
		int h; //heuristic
		int f;
		const Node *parent;	
};

#endif
