#include "MinesweeperWindow.h"

MinesweeperWindow::MinesweeperWindow(Point xy, int width, int height, int mines, const string& title) :
	Graph_lib::Window(xy, width * cellSize, height*cellSize, title), width(width), height(height), mines(mines), remainingTiles(width*height-mines)
	//Initialiser medlemsvariabler, bruker også konstruktøren til Windowsklassen
{
	for (int i = 0; i < height; ++i) {	
		for (int j = 0; j < width; ++j) {
			int y = i* cellSize,
				x = j * cellSize;
			tiles.push_back(new Tile{ Point{x, y}, cellSize, cb_click });		//Legg til i tiles
			attach(tiles.back());												// Attach bakerste element i tiles
		}
		
	}
	//Legg til miner på tilfeldige posisjoner
	int i = 0;
	while (i<mines) {
		int pos = rand() % tiles.size();
		if (!tiles[pos].isMine) {
			tiles[pos].isMine = true;
			++i;
		}
	}
	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}

int MinesweeperWindow::countMines(vector<Point> points) { //Point neighbour{ xy.x + di * cellSize, xy.y + dj * cellSize
	int countMines = 0;
	for (int i = 0; i < points.size(); ++i) {
		Tile& tile = at(points[i]);
		if (tile.isMine) ++countMines;
	}
	return countMines;
};
vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize, xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}

	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	Tile& tile = at(xy);
	if (tile.state != Cell::closed) return;
	tile.open();
	if (!tile.isMine) {
		--remainingTiles;
		if (remainingTiles == 0) {
			flush();
			gameEnd(true);
		}
		vector<Point> adjacentToOurPoint = adjacentPoints(xy);
		int numMines = countMines(adjacentToOurPoint);
		if(numMines != 0) tile.setAdjMines(numMines);
		else zeroTile(adjacentToOurPoint);
	}
	else {
		flush();
		gameEnd(false);
	}
}
void MinesweeperWindow::zeroTile(vector<Point> adjacentToOurPoint) {
	for (int i = 0; i < adjacentToOurPoint.size(); ++i) {
		Point targetedPoint = adjacentToOurPoint[i];
		openTile(targetedPoint);
	}
}
void MinesweeperWindow::flagTile(Point xy) {
	Tile& tile = at(xy);
	tile.flag();
	if (tile.state == Cell::flagged);
}

//Kaller opentile ved venstreklikk og flagTile ved høyreklikk
void MinesweeperWindow::cb_click(Address, Address pw)
{
	Point xy{ Fl::event_x(),Fl::event_y() };
	MouseButton mb = static_cast<MouseButton>(Fl::event_button());
	auto& win = reference_to<MinesweeperWindow>(pw);
	if (!win.inRange(xy)) {
		return;
	}

	switch (mb) {
	case MouseButton::left:
		win.openTile(xy);
		break;
	case MouseButton::right:
		win.flagTile(xy);
		break;
	}
	win.flush();


}

void MinesweeperWindow::gameEnd(bool won) {
	string endText;
	if (won) endText = "won";
	else endText = "over";

	Text t{ Point{200, 300}, "Game won!" };
	attach(t)
	
	//set_label("Canvas #8");
	//cout << "Game won!\n";
	system("pause");
	exit(0);
}
int randomNumber_1_100() {
	return (1+ (rand() % 100));
}


