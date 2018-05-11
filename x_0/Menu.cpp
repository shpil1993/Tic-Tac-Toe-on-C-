#pragma once
#include "Menu.h"



Menu::Menu()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
				this->grid[i][j] = 0;
		}
	}
	this->grid[0][0] = 1;
	this->grid[0][2] = 3;
	this->grid[2][0] = 2;
	this->grid[2][2] = 4;
}


Menu::~Menu()
{

}

void Menu::Start()
{
	StartSettings();
	LoadingImage();
	Reset();
}

void Menu::Update()
{
	char* message = "Вы уверены что хотите выйти?";
	if (input->IsExit()) {
		game->Exit();
	}
	if (input->IsMouseButtonDown(1)) {
		int x = input->GetButtonDownCoords().x / (GRID_SIZE / 3), y = input->GetButtonDownCoords().y / (GRID_SIZE / 3);
		if (grid[x][y] != 0) {
			switch (grid[x][y])
			{
			case 1:
				Field(new f3x3(),"f3x3");
				Reset();
				break;
			case 2:
				Field(new f10x10(), "f10x10");
				Reset();
				break;
			case 3:
				Field(new Rules(), "Rules");
				Reset();
				break;
			case 4:
				if (MessageBox(0, message, "Выход.", MB_YESNO) == IDYES)
					game->Exit(); 
				else
					Reset();
				break;
			default:
				break;
			}
		}
	}
}

void Menu::StartSettings()
{
	input = game->GetInput();
	graphics = game->GetGraphics();
	SDL_WM_SetCaption("X and 0", 0);
}

void Menu::LoadingImage()
{
	menu = graphics->NewImage("pic/menu.bmp");
}

void Menu::Reset()
{
	graphics->DrawImage(menu, 0, 0);
	graphics->Flip();
}

int Menu::Field(Screen* startscreen, std::string st)
{
	Game gamefield;
	return gamefield.Execute(startscreen, GRID_SIZE, GRID_SIZE,st);
}
