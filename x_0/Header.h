#pragma once
#include "Project.h"
#include "Menu.h"

const int GRID_SIZE = 384;
class mainclass
{
public:
	mainclass() {}
	~mainclass(){}
	static void start() {
		Game game;
		game.Execute(new Menu(), GRID_SIZE, GRID_SIZE);
	}
private:
	
};