#include "Tile.h"
#include <sstream>

// For å sette labelfarge i henhold til hvor mange miner som er rundt
const map<int, Color> minesToColor{ {1, Color::blue},
								   {2, Color::red},
								   {3,Color::dark_green},
								   {4, Color::dark_magenta},
								   {5, Color::dark_blue},
								   {6, Color::dark_cyan},
								   {7, Color::dark_red},
								   {8, Color::dark_yellow} };

// For å sette Tilelabel i henhold til state
const map<Cell, string> cellToSymbol{ {Cell::closed, ""},
									 {Cell::open, ""},
									 {Cell::flagged, "@<"} };

void Tile::open() {
	if (state == Cell::flagged) return; //Terminate if flagged

	static_cast<Fl_Button*>(pw)->set();//Setter en button som trykket på, tilsvarer åpnet rute
	state = Cell::open; //Set open
	if (isMine) {
		set_label("X");
		set_label_color(Color::red);
	}
	redraw();
}

void Tile::flag() {
	if (state == Cell::flagged) {
		state = Cell::closed;
		set_label_color(Color::black);
	}
	else {
		state = Cell::flagged;
		set_label_color(Color::blue);
	}
	set_label(cellToSymbol.at(state)); 
	redraw();
}

void Tile::setAdjMines(int n){
	/*stringstream ss; ss << n; string stringN; ss >> stringN;
	set_label(stringN);
	map<int, Color>::iterator it = minesToColor.find(n);
	set_label_color( it->second);*/
	set_label(to_string(n));
	set_label_color(minesToColor.at(n));
}
