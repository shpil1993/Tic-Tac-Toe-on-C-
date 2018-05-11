#include "Rules.h"



Rules::Rules()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->grid[i][j] = 0;
		}
	}
	this->grid[2][2] = 4;
}


Rules::~Rules()
{
}

void Rules::StartSettings()
{
	input = game->GetInput();
	graphics = game->GetGraphics();
	SDL_WM_SetCaption("X and 0", 0);
}

void Rules::LoadingImage()
{
	back = graphics->NewImage("pic/rules.bmp");
}

void Rules::Reset()
{
	graphics->DrawImage(back, 0, 0);
	graphics->Flip();
}

void Rules::Start()
{
	StartSettings();
	LoadingImage();
	Reset();
}

void Rules::Update()
{
	char* message = "Вернутся назад?";
	if (input->IsExit()) {
		if (MessageBox(0, message, "Назад.", MB_YESNO) == IDYES) {
			game->Exit();
		}
		else {
			Reset();
		}
	}
	if (input->IsMouseButtonDown(1)) {
		int x = input->GetButtonDownCoords().x / (GRID_SIZE / 3), y = input->GetButtonDownCoords().y / (GRID_SIZE / 3);
		if (grid[x][y] != 0) {
			switch (grid[x][y])
			{
			case 4:
				if (MessageBox(0, message, "Назад.", MB_YESNO) == IDYES) {
					game->Exit();
				}
				else {
					Reset();
				}
				break;
			default:
				break;
			}
		}
	}
}
