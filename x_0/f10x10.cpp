#include "f10x10.h"



f10x10::f10x10()
{
	this->pl = 1;
	this->pc = 2;
}


f10x10::~f10x10()
{
}

void f10x10::StartSettings()
{
	input = game->GetInput();
	graphics = game->GetGraphics();
	SDL_WM_SetCaption("Field 10x10", 0);
}

void f10x10::LoadingImage()
{
	back = graphics->NewImage("pic/back10.bmp");
	player[0] = graphics->NewImage("pic/x10.bmp", 255, 255, 255);
	player[1] = graphics->NewImage("pic/010.bmp", 255, 255, 255);
}

void f10x10::Reset()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			grid[i][j] = 0;
		}
	}
	graphics->DrawImage(back, 0, 0);
	graphics->Flip();
}

int f10x10::GameOver()
{
	for (int pl = 1; pl < 3; pl++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (grid[i][j] != 0) {
					if ((grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3] && grid[i][j + 3] == grid[i][j + 4] && j <= 5 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i][j - 1] && grid[i][j - 1] == grid[i][j - 2] && grid[i][j - 2] == grid[i][j - 3] && grid[i][j - 3] == grid[i][j - 4] && j >= 4 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j] && grid[i + 3][j] == grid[i + 4][j] && i <= 5 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i - 1][j] && grid[i - 1][j] == grid[i - 2][j] && grid[i - 2][j] == grid[i - 3][j] && grid[i - 3][j] == grid[i - 4][j] && i >= 4 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2] && grid[i + 2][j + 2] == grid[i + 3][j + 3] && grid[i + 3][j + 3] == grid[i + 4][j + 4] && i <= 5 && j <= 5 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i - 1][j + 1] && grid[i - 1][j + 1] == grid[i - 2][j + 2] && grid[i - 2][j + 2] == grid[i - 3][j + 3] && grid[i - 3][j + 3] == grid[i - 4][j + 4] && i >= 4 && j <= 5 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i + 1][j - 1] && grid[i + 1][j - 1] == grid[i + 2][j - 2] && grid[i + 2][j - 2] == grid[i + 3][j - 3] && grid[i + 3][j - 3] == grid[i + 4][j - 4] && i <= 5 && j >= 4 && grid[i][j] == pl) ||
						(grid[i][j] == grid[i - 1][j - 1] && grid[i - 1][j - 1] == grid[i - 2][j - 2] && grid[i - 2][j - 2] == grid[i - 3][j - 3] && grid[i - 3][j - 3] == grid[i - 4][j - 4] && i >= 4 && j >= 4 && grid[i][j] == pl)) {
						return pl;
					}
					else {
						continue;
					}
				}
			}
		}
	}
	int count = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j] != 0) {
				count++;
			}
		}
	}
	if (count == 84) {
		return 0;
	}
	return -1;
}

void f10x10::GameOverHandle(int over)
{
	char* message;
	switch (over)
	{
	case 0:
		message = "Ничья! Желаете сыграть еще раз?";
		break;
	case 1:
		message = "Крестики победили! Желаете сыграть еще раз?";
		break;
	case 2:
		message = "Нолики победили! Желаете сыграть еще раз?";
		break;
	default:
		return;
	}
	if (MessageBox(0, message, "Игра окончена", MB_YESNO) == IDYES) {
		Reset();
	}
	else {
		game->Exit();
	}
}

void f10x10::pickBestMove(int f10x10[10][10], int i, int j, int *mi, int *mj, int count)
{
	if (count == 1) {
		if (f10x10[i - 1][j] == 0 && i != 0) {
			*mi = i - 1;
			*mj = j;
		}
		else if (f10x10[i][j - 1] == 0 && j != 0) {
			*mi = i;
			*mj = j - 1;
		}
		else if (f10x10[i][j + 1] == 0 && j != 9) {
			*mi = i;
			*mj = j + 1;
		}
		else if (f10x10[i + 1][j] == 0 && i != 9) {
			*mi = i + 1;
			*mj = j;
		}
		else if (f10x10[i - 1][j - 1] == 0 && i != 0 && j != 0) {
			*mi = i - 1;
			*mj = j - 1;
		}
		else if (f10x10[i - 1][j + 1] == 0 && i != 0 && j != 9) {
			*mi = i - 1;
			*mj = j + 1;
		}
		else if (f10x10[i + 1][j - 1] == 0 && i != 9 && j != 0) {
			*mi = i + 1;
			*mj = j - 1;
		}
		else if (f10x10[i + 1][j + 1] == 0 && i != 9 && j != 9) {
			*mi = i + 1;
			*mj = j + 1;
		}
	}
	if (count > 1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if ((f10x10[i][j + 1] == pl && f10x10[i][j + 1] == f10x10[i][j + 2] && f10x10[i][j + 2] == f10x10[i][j + 3] && f10x10[i][j + 3] == f10x10[i][j + 4] && f10x10[i][j] == 0) ||
					(f10x10[i][j - 1] == pl && f10x10[i][j - 1] == f10x10[i][j - 2] && f10x10[i][j - 2] == f10x10[i][j - 3] && f10x10[i][j - 3] == f10x10[i][j - 4] && f10x10[i][j] == 0) ||
					(f10x10[i + 1][j] == pl && f10x10[i + 1][j] == f10x10[i + 2][j] && f10x10[i + 2][j] == f10x10[i + 3][j] && f10x10[i + 3][j] == f10x10[i + 4][j] && f10x10[i][j] == 0) ||
					(f10x10[i - 1][j] == pl && f10x10[i - 1][j] == f10x10[i - 2][j] && f10x10[i - 2][j] == f10x10[i - 3][j] && f10x10[i - 3][j] == f10x10[i - 4][j] && f10x10[i][j] == 0) ||
					(f10x10[i + 1][j + 1] == pl && f10x10[i + 1][j + 1] == f10x10[i + 2][j + 2] && f10x10[i + 2][j + 2] == f10x10[i + 3][j + 3] && f10x10[i + 3][j + 3] == f10x10[i + 4][j + 4] && f10x10[i][j] == 0) ||
					(f10x10[i - 1][j + 1] == pl && f10x10[i - 1][j + 1] == f10x10[i - 2][j + 2] && f10x10[i - 2][j + 2] == f10x10[i - 3][j + 3] && f10x10[i - 3][j + 3] == f10x10[i - 4][j + 4] && f10x10[i][j] == 0) ||
					(f10x10[i + 1][j - 1] == pl && f10x10[i + 1][j - 1] == f10x10[i + 2][j - 2] && f10x10[i + 2][j - 2] == f10x10[i + 3][j - 3] && f10x10[i + 3][j - 3] == f10x10[i + 4][j - 4] && f10x10[i][j] == 0) ||
					(f10x10[i - 1][j - 1] == pl && f10x10[i - 1][j - 1] == f10x10[i - 2][j - 2] && f10x10[i - 2][j - 2] == f10x10[i - 3][j - 3] && f10x10[i - 3][j - 3] == f10x10[i - 4][j - 4] && f10x10[i][j] == 0)) {
					*mi = i;
					*mj = j;
					break;
				}
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i][j + 1] && f10x10[i][j + 1] == f10x10[i][j + 2] && f10x10[i][j + 2] == f10x10[i][j + 3] && (f10x10[i][j + 4] == 0 || f10x10[i][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j + 4] == 0 && j != 9) {
			*mi = i;
			*mj = j + 4;
		}
		else if (f10x10[i][j - 1] == 0 && j != 0) {
			*mi = i;
			*mj = j - 1;
		}
		else {
			if (f10x10[i][j + 5] == 0 && j != 9) {
				*mi = i;
				*mj = j + 5;
			}
			else if (f10x10[i][j - 2] == 0 && j != 0) {
				*mi = i;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i][j - 1] && f10x10[i][j - 1] == f10x10[i][j - 2] && f10x10[i][j - 2] == f10x10[i][j - 3] && (f10x10[i][j - 4] == 0 || f10x10[i][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j - 4] == 0 && j != 0) {
			*mi = i;
			*mj = j - 4;
		}
		else if (f10x10[i][j + 1] == 0 && j != 9) {
			*mi = i;
			*mj = j + 1;
		}
		else {
			if (f10x10[i][j - 5] == 0 && j != 0) {
				*mi = i;
				*mj = j - 5;
			}
			else if (f10x10[i][j + 2] == 0 && j != 9) {
				*mi = i;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j] && f10x10[i + 1][j] == f10x10[i + 2][j] && f10x10[i + 2][j] == f10x10[i + 3][j] && (f10x10[i + 4][j] == 0 || f10x10[i - 1][j] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 4][j] == 0) {
			*mi = i + 4;
			*mj = j;
		}
		else if (f10x10[i - 1][j] == 0) {
			*mi = i - 1;
			*mj = j;
		}
		else {
			if (f10x10[i + 5][j] == 0) {
				*mi = i + 5;
				*mj = j;
			}
			else if (f10x10[i - 2][j] == 0) {
				*mi = i - 2;
				*mj = j;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j] && f10x10[i - 1][j] == f10x10[i - 2][j] && f10x10[i - 2][j] == f10x10[i - 3][j] && (f10x10[i - 4][j] == 0 || f10x10[i + 1][j] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 4][j] == 0) {
			*mi = i - 4;
			*mj = j;
		}
		else if (f10x10[i + 1][j] == 0) {
			*mi = i + 1;
			*mj = j;
		}
		else {
			if (f10x10[i - 5][j] == 0) {
				*mi = i - 5;
				*mj = j;
			}
			else if (f10x10[i + 2][j] == 0) {
				*mi = i + 2;
				*mj = j;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j + 1] && f10x10[i + 1][j + 1] == f10x10[i + 2][j + 2] && f10x10[i + 2][j + 2] == f10x10[i + 3][j + 3] && (f10x10[i + 4][j + 4] == 0 || f10x10[i - 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 4][j + 4] == 0 && j != 9) {
			*mi = i + 4;
			*mj = j + 4;
		}
		else if (f10x10[i - 1][j - 1] == 0 && j != 0) {
			*mi = i - 1;
			*mj = j - 1;
		}
		else {
			if (f10x10[i + 5][j + 5] == 0 && j != 9) {
				*mi = i + 5;
				*mj = j + 5;
			}
			else if (f10x10[i - 2][j - 2] == 0 && j != 0) {
				*mi = i - 2;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j - 1] && f10x10[i - 1][j - 1] == f10x10[i - 2][j - 2] && f10x10[i - 2][j - 2] == f10x10[i - 3][j - 3] && (f10x10[i - 4][j - 4] == 0 || f10x10[i + 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 4][j - 4] == 0 && j != 0) {
			*mi = i - 4;
			*mj = j - 4;
		}
		else if (f10x10[i + 1][j + 1] == 0 && j != 9) {
			*mi = i + 1;
			*mj = j + 1;
		}
		else {
			if (f10x10[i - 5][j - 5] == 0 && j != 0) {
				*mi = i - 5;
				*mj = j - 5;
			}
			else if (f10x10[i + 2][j + 2] == 0 && j != 9) {
				*mi = i + 2;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j + 1] && f10x10[i - 1][j + 1] == f10x10[i - 2][j + 2] && f10x10[i - 2][j + 2] == f10x10[i - 3][j + 3] && (f10x10[i - 4][j + 4] == 0 || f10x10[i + 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 4][j + 4] == 0 && j != 9) {
			*mi = i - 4;
			*mj = j + 4;
		}
		else if (f10x10[i + 1][j - 1] == 0 && j != 0) {
			*mi = i + 1;
			*mj = j - 1;
		}
		else {
			if (f10x10[i - 5][j + 5] == 0 && j != 9) {
				*mi = i - 5;
				*mj = j + 5;
			}
			else if (f10x10[i + 2][j - 2] == 0 && j != 0) {
				*mi = i + 2;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j - 1] && f10x10[i + 1][j - 1] == f10x10[i + 2][j - 2] && f10x10[i + 2][j - 2] == f10x10[i + 3][j - 3] && (f10x10[i + 4][j - 4] == 0 || f10x10[i - 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 4][j - 4] == 0 && j != 0) {
			*mi = i + 4;
			*mj = j - 4;
		}
		else if (f10x10[i - 1][j + 1] == 0 && j != 9) {
			*mi = i - 1;
			*mj = j + 1;
		}
		else {
			if (f10x10[i + 5][j - 5] == 0 && j != 0) {
				*mi = i + 5;
				*mj = j - 5;
			}
			else if (f10x10[i - 2][j + 2] == 0 && j != 9) {
				*mi = i - 2;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i][j - 1] && f10x10[i][j - 1] == f10x10[i][j - 2] && (f10x10[i][j - 3] == 0 || f10x10[i][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j - 3] == 0 && j != 0) {
			*mi = i;
			*mj = j - 3;
		}
		else if (f10x10[i][j + 1] == 0 && j != 9) {
			*mi = i;
			*mj = j + 1;
		}
		else {
			if (f10x10[i][j - 4] == 0 && j != 0) {
				*mi = i;
				*mj = j - 4;
			}
			else if (f10x10[i][j + 2] == 0 && j != 9) {
				*mi = i;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i][j + 1] && f10x10[i][j + 1] == f10x10[i][j + 2] && (f10x10[i][j + 3] == 0 || f10x10[i][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j + 3] == 0 && j != 9) {
			*mi = i;
			*mj = j + 3;
		}
		else if (f10x10[i][j - 1] == 0 && j != 0) {
			*mi = i;
			*mj = j - 1;
		}
		else {
			if (f10x10[i][j + 4] == 0 && j != 9) {
				*mi = i;
				*mj = j + 4;
			}
			else if (f10x10[i][j - 2] == 0 && j != 0) {
				*mi = i;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j] && f10x10[i + 1][j] == f10x10[i + 2][j] && (f10x10[i + 3][j] == 0 || f10x10[i - 1][j] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 3][j] == 0) {
			*mi = i + 3;
			*mj = j;
		}
		else if (f10x10[i - 1][j] == 0) {
			*mi = i - 1;
			*mj = j;
		}
		else {
			if (f10x10[i + 4][j] == 0) {
				*mi = i + 4;
				*mj = j;
			}
			else if (f10x10[i - 2][j] == 0) {
				*mi = i - 2;
				*mj = j;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j] && f10x10[i - 1][j] == f10x10[i - 2][j] && (f10x10[i - 3][j] == 0 || f10x10[i + 1][j] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 3][j] == 0) {
			*mi = i - 3;
			*mj = j;
		}
		else if (f10x10[i + 1][j] == 0) {
			*mi = i + 1;
			*mj = j;
		}
		else {
			if (f10x10[i - 4][j] == 0) {
				*mi = i - 4;
				*mj = j;
			}
			else if (f10x10[i + 2][j] == 0) {
				*mi = i + 2;
				*mj = j;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j + 1] && f10x10[i + 1][j + 1] == f10x10[i + 2][j + 2] && (f10x10[i + 3][j + 3] == 0 || f10x10[i - 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 3][j + 3] == 0 && j != 9) {
			*mi = i + 3;
			*mj = j + 3;
		}
		else if (f10x10[i - 1][j - 1] == 0 && j != 0) {
			*mi = i - 1;
			*mj = j - 1;
		}
		else {
			if (f10x10[i + 4][j + 4] == 0 && j != 9) {
				*mi = i + 4;
				*mj = j + 4;
			}
			else if (f10x10[i - 2][j - 2] == 0 && j != 0) {
				*mi = i - 2;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j - 1] && f10x10[i - 1][j - 1] == f10x10[i - 2][j - 2] && (f10x10[i - 3][j - 3] == 0 || f10x10[i + 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 3][j - 3] == 0 && j != 0) {
			*mi = i - 3;
			*mj = j - 3;
		}
		else if (f10x10[i + 1][j + 1] == 0 && j != 9) {
			*mi = i + 1;
			*mj = j + 1;
		}
		else {
			if (f10x10[i - 4][j - 4] == 0 && j != 0) {
				*mi = i - 4;
				*mj = j - 4;
			}
			else if (f10x10[i + 2][j + 2] == 0 && j != 9) {
				*mi = i + 2;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j + 1] && f10x10[i - 1][j + 1] == f10x10[i - 2][j + 2] && (f10x10[i - 3][j + 3] == 0 || f10x10[i + 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 3][j + 3] == 0 && j != 9) {
			*mi = i - 3;
			*mj = j + 3;
		}
		else if (f10x10[i + 1][j - 1] == 0 && j != 0) {
			*mi = i + 1;
			*mj = j - 1;
		}
		else {
			if (f10x10[i - 4][j + 4] == 0 && j != 9) {
				*mi = i - 4;
				*mj = j + 4;
			}
			else if (f10x10[i + 2][j - 2] == 0 && j != 0) {
				*mi = i + 2;
				*mj = j - 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j - 1] && f10x10[i + 1][j - 1] == f10x10[i + 2][j - 2] && (f10x10[i + 3][j - 3] == 0 || f10x10[i - 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 3][j - 3] == 0 && j != 0) {
			*mi = i + 3;
			*mj = j - 3;
		}
		else if (f10x10[i - 1][j + 1] == 0 && j != 9) {
			*mi = i - 1;
			*mj = j + 1;
		}
		else {
			if (f10x10[i + 4][j - 4] == 0 && j != 0) {
				*mi = i + 4;
				*mj = j - 4;
			}
			else if (f10x10[i - 2][j + 2] == 0 && j != 9) {
				*mi = i - 2;
				*mj = j + 2;
			}
		}
	}
	else if (f10x10[i][j] == f10x10[i][j - 1] && (f10x10[i][j - 2] == 0 || f10x10[i][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j - 2] == 0 && j != 0) {
			*mi = i;
			*mj = j - 2;
		}
		else if (f10x10[i][j + 1] == 0 && j != 9) {
			*mi = i;
			*mj = j + 1;
		}
	}
	else if (f10x10[i][j] == f10x10[i][j + 1] && (f10x10[i][j + 2] == 0|| f10x10[i][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i][j - 1] == 0 && j != 0) {
			*mi = i;
			*mj = j - 1;
		}
		else if (f10x10[i][j + 2] == 0 && j != 9) {
			*mi = i;
			*mj = j + 2;
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j + 1] && (f10x10[i + 2][j + 2] == 0 || f10x10[i - 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 2][j + 2] == 0 && j != 9) {
			*mi = i + 2;
			*mj = j + 2;
		}
		else if (f10x10[i - 1][j - 1] == 0 && j != 0) {
			*mi = i - 1;
			*mj = j - 1;
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j - 1] && (f10x10[i - 2][j - 2] == 0 || f10x10[i + 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 1][j + 1] == 0 && j != 9) {
			*mi = i + 1;
			*mj = j + 1;
		}
		else if (f10x10[i - 2][j - 2] == 0 && j != 0) {
			*mi = i - 2;
			*mj = j - 2;
		}
	}
	else if (f10x10[i][j] == f10x10[i - 1][j + 1] && (f10x10[i - 2][j + 2] == 0 || f10x10[i + 1][j - 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i - 2][j + 2] == 0 && j != 9) {
			*mi = i - 2;
			*mj = j + 2;
		}
		else if (f10x10[i + 1][j - 1] == 0 && j != 0) {
			*mi = i + 1;
			*mj = j - 1;
		}
	}
	else if (f10x10[i][j] == f10x10[i + 1][j - 1] && (f10x10[i + 2][j - 2] == 0 || f10x10[i - 1][j + 1] == 0) && f10x10[i][j] == 1) {
		if (f10x10[i + 2][j - 2] == 0 && j != 0) {
			*mi = i + 2;
			*mj = j - 2;
		}
		else if (f10x10[i - 1][j + 1] == 0 && j != 9) {
			*mi = i - 1;
			*mj = j + 1;
		}
	}
	else if (f10x10[i - 1][j] == 0) {
		*mi = i - 1;
		*mj = j;
	}
	else if (f10x10[i][j - 1] == 0) {
		*mi = i;
		*mj = j - 1;
	}
	else if (f10x10[i][j + 1] == 0) {
		*mi = i;
		*mj = j + 1;
	}
	else if (f10x10[i + 1][j] == 0) {
		*mi = i + 1;
		*mj = j;
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (f10x10[i][j] == 0) {
					*mi = i;
					*mj = j;
				}
			}
		}
	}
}

void f10x10::Start()
{
	StartSettings();
	LoadingImage();
	Reset();
}

void f10x10::Update()
{
	// Если нажат красный крестик в окне
	int count = 0;
	char* message = "Вернутся назад?";
	if (input->IsExit()) {
		if (MessageBox(0, message, "Назад.", MB_YESNO) == IDYES) {
			game->Exit();
		}
		else {
			Reset();
		}
	}
	// Если нажата левая кнопка мыши
	// P.S. 1 - ЛКМ, 2 - СКМ, 3 - ПКМ
	if (input->IsMouseButtonDown(1))
	{
		// Берем координаты нажатой клетки
		int x = input->GetButtonDownCoords().x / (GRID_SIZE / 10),
			y = input->GetButtonDownCoords().y / (GRID_SIZE / 10);

		// Если мы нажали на пустую клетку
		if (grid[x][y] == 0)
		{
			// Устанавливаем крестик или нолик в клетку
			grid[x][y] = pl;
			count++;
			if (GameOver() == -1) {
				int r, c;
				pickBestMove(grid, x, y, &r, &c, count);
				grid[r][c] = pc;
				count++;
			}
			// Рисуем задник
			graphics->DrawImage(back, 0, 0);
			// Рисуем крестики и нолики
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (grid[i][j] != 0) {
						graphics->DrawImage(player[grid[i][j] - 1], i * (GRID_SIZE / 10), j * (GRID_SIZE / 10));
					}
				}
			}
			// Выводим на экран
			graphics->Flip();
			// Обрабатываем конец игры
			GameOverHandle(GameOver());
		}
	}
}
