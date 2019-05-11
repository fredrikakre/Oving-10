#include "MinesweeperWindow.h"

int main()
{

	Fl::background(200, 200, 200);
	constexpr int width = 20;
	constexpr int height = 20;
	constexpr int mines = 0;

	Point startPoint{ 200,300 };
	MinesweeperWindow mw{ startPoint, width, height, mines, "Minesweeper" };
	return gui_main();

}
 