/*************************************************************
 * File              : Gui.cpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 16.10.2022
 * Last Modified Date: 16.10.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#include "Gui.hpp"

#define WIN_SIZE 400
#define FRAME_RATE 60

Gui::Gui(const NPuzzle &puzzle)
	: puzzle(puzzle), tile(new Tile)
{
	for (Node *elem : puzzle.closedList)
		states.push_back(elem);
	tile->nextPosX = 0;
	tile->nextPosY = 0;
	moveDist = (static_cast<float>(WIN_SIZE) / puzzle.size) / static_cast<float>(FRAME_RATE);
	initTile();
	setTile(0);
	windowInit();
	initialize();
}

Gui::~Gui()
{
	delete window;
}

void	Gui::windowInit()
{
	window = new sf::RenderWindow(sf::VideoMode(WIN_SIZE, WIN_SIZE), "n-puzzle");
	window->setFramerateLimit(60);
}

void	Gui::initialize()
{
	sf::Texture *texture;
	sf::Image image;
	int x;
	int y;

	image.loadFromFile("bjarne_stoustrup.png");

	std::vector<sf::Sprite> sprites_line(puzzle.size);
	sprites = std::vector<std::vector<sf::Sprite>>();
	for (int i = 0; i < puzzle.size; i++)
		sprites.push_back(sprites_line);
	for (int i = 0; i < puzzle.size; i++) {
		for (int k = 0; k < puzzle.size; k++) {
			texture = new sf::Texture;
			if (states.front()->grid[i][k] == 0)
				continue ;
			y = (states.front()->grid[i][k] - 1) / puzzle.size; // y goal
			x = (states.front()->grid[i][k] - 1) % puzzle.size; // x goal
			texture->loadFromImage(image, sf::IntRect(((x) * ((WIN_SIZE / puzzle.size))),
				((y) * ((WIN_SIZE / puzzle.size))),
				WIN_SIZE/puzzle.size, WIN_SIZE/puzzle.size));
			sprites[i][k].setTexture(*texture);
			sprites[i][k].setPosition(sf::Vector2f(k * (WIN_SIZE/puzzle.size), i * (WIN_SIZE/puzzle.size)));
		}
	}
}

void	Gui::initTile()
{
	tile->posX = tile->nextPosX;
	tile->posY = tile->nextPosY;
	tile->nextPosX = 0;
	tile->nextPosY = 0;
	tile->offsetX = 0;
	tile->offsetY = 0;
}

/*
void	Gui::movePath(const int &diffX, const int &diffY)
{
	switch (diffX) {
		case 1:
			
		case -1:

		default:
			
	}
}
*/

void	Gui::setTile(int pos)
{
	std::cout << "pos :  " <<pos << std::endl;
	std::cout << "size :  " <<states.size() << std::endl;
	for (int posY = 0; posY < puzzle.size; posY++) {
		for (int posX = 0; posX < puzzle.size; posX++) {
			if (states[pos]->grid[posY][posX] == 0) {
				tile->nextPosX = posX;
				tile->nextPosY = posY;
				goto finish;
			}
		}
	}
	finish:
	tile->offsetX = tile->posX - tile->nextPosX;
	tile->offsetY = tile->posY - tile->nextPosY;

	std::cout << "Y " << tile->posY << std::endl;
	std::cout << "X " << tile->posX << std::endl;
	std::cout << "nY " << tile->nextPosY << std::endl;
	std::cout << "nX " << tile->nextPosX << std::endl;
	std::cout << "offsetY " << tile->offsetY << std::endl;
	std::cout << "offsetX " << tile->offsetX << std::endl<< std::endl;


	//std::cout << "sprite y " << tile->posY + tile->offsetY << std::endl << std::endl;
	//std::cout << "sprite x " << tile->posX + tile->offsetX << std::endl << std::endl;
	//movePath();
}

void	Gui::moveTile(int &frame, int &pos)
{
	if (frame == 0 && pos < states.size()) {
		states[pos - 1]->show();
		initTile();
		setTile(pos);
		pos++;
	}
	if (frame < FRAME_RATE)	{
		frame++;
		sprites[tile->nextPosY][tile->nextPosX].move(moveDist * tile->offsetX, moveDist * tile->offsetY);
	} else if (pos >= states.size())
		frame = FRAME_RATE;
	else {
		std::swap(sprites[tile->nextPosY][tile->nextPosX], sprites[tile->posY][tile->posX]);
		frame = 0;
	}
}

void	Gui::run()
{
//	states.front()->show();
	int frame = 0;
	int pos = 1;
	while (window->isOpen())
	{
		// on gère les évènements
		sf::Event event;
		while (window->pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window->close();
		}
		
		// on dessine le niveau
		window->clear();
		for (auto line : sprites) {
			for (auto sprite : line) {
				window->draw(sprite);
			}
		}
		window->display();
		
		moveTile(frame, pos);
	}
}
