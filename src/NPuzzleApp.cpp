/*************************************************************
 * File              : NPuzzleApp.cpp
 * Author            : Pierre Cariou <pierrecariou@outlook.fr>
 * Date              : 28.07.2022
 * Last Modified Date: 28.07.2022
 * Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>
 *************************************************************/

#include "NPuzzle.hpp"

int	main()
{
	NPuzzle puzzle("resources/t.txt");

//	puzzle.show();

	puzzle.solve();
	return (0);
}
