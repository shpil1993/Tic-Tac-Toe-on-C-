#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "Project.h"
class Graphics;
class Input;
class Screen;

class Game
{
private:
	bool run;
	Graphics* graphics;
	Input* input;
	Screen* screen;
public:
	Game();
	int Execute(Screen* startscreen, int width, int height);
	int Execute(Screen* startscreen, int width, int height, std::string);
	Graphics* GetGraphics();
	Input* GetInput();
	Screen* GetScreen();
	void SetScreen(Screen* screen);
	void Exit();
};

#endif
