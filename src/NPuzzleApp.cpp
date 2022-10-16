/*************************************************************
 * File              : NPuzzleApp.cpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 28.07.2022
 * Last Modified Date: 28.07.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#include "NPuzzle.hpp"
#include "Gui.hpp"

int	main()
{
	NPuzzle puzzle("resources/taquin1.txt");
	puzzle.solve();

	Gui gui(puzzle);
	gui.run();

	return (0);
}
