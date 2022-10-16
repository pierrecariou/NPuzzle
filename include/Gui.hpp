/*************************************************************
 * File              : Gui.hpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 16.10.2022
 * Last Modified Date: 16.10.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#ifndef GUI_HPP
# define GUI_HPP

#include <SFML/Graphics.hpp>
#include "NPuzzle.hpp"

struct Tile {
	int posX;
	int posY;
	int nextPosX;
	int nextPosY;
	int offsetX;
	int offsetY;
};

class Gui
{
	public:
		Gui(const NPuzzle &puzzle);
		~Gui();

		void	run();
	private:

		void	windowInit();
		void	initialize();
		void	moveTile(int &frame, int &pos);

		void	initTile();
		void	setTile(int pos);

		const NPuzzle &puzzle;
		sf::RenderWindow *window;
		std::vector<std::vector<sf::Sprite>> sprites;
		std::vector<Node *> states;
		Tile *tile;
		float moveDist;
};

#endif
