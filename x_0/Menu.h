#pragma once
#include "Project.h"
#include "f3x3.h"
#include "Rules.h"
#include "f10x10.h"

class Menu : public Screen
{
private:
	const int GRID_SIZE = 384;
	Input* input;
	Graphics* graphics;
	Image* menu;
	int grid[3][3];
	void StartSettings();
	void LoadingImage();
	void Reset();
	int WINAPI Field(Screen* startscreen,std::string st);
public:
	Menu();
	virtual ~Menu();
	void Start();
	void Update();
};

