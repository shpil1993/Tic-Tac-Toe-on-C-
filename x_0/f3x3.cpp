#include "f3x3.h"



f3x3::f3x3()
{
	this->pl = 1;
	this->pc = 2;
}


f3x3::~f3x3()
{
}

void f3x3::StartSettings()
{
	input = game->GetInput();
	graphics = game->GetGraphics();
	SDL_WM_SetCaption("Field 3x3", 0);
}

void f3x3::LoadingImage()
{
	back = graphics->NewImage("pic/back.bmp");
	player[0] = graphics->NewImage("pic/X.bmp", 255, 255, 255);
	player[1] = graphics->NewImage("pic/O.bmp", 255, 255, 255);
}

void f3x3::Reset()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			grid[i][j] = 0;
		}
	}
	graphics->DrawImage(back, 0, 0);
	graphics->Flip();
}

int f3x3::GameOver()
{
	for (int i = 1; i < 3; i++) {
		if ((grid[0][0] == i && grid[1][0] == i && grid[2][0] == i) ||
			(grid[0][1] == i && grid[1][1] == i && grid[2][1] == i) ||
			(grid[0][2] == i && grid[1][2] == i && grid[2][2] == i) ||
			(grid[0][0] == i && grid[0][1] == i && grid[0][2] == i) ||
			(grid[1][0] == i && grid[1][1] == i && grid[1][2] == i) ||
			(grid[2][0] == i && grid[2][1] == i && grid[2][2] == i) ||
			(grid[0][0] == i && grid[1][1] == i && grid[2][2] == i) ||
			(grid[2][0] == i && grid[1][1] == i && grid[0][2] == i)) {
			return i;
		}
	}
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i][j] != 0) {
				count++;
			}
		}
	}
	if (count == 9) {
		return 0;
	}
	return -1;
}

void f3x3::GameOverHandle(int over)
{
	char* message;
	switch (over)
	{
	case 0:
		message = "�����! ������� ������� ��� ���?";
		break;
	case 1:
		message = "�������� ��������! ������� ������� ��� ���?";
		break;
	case 2:
		message = "������ ��������! ������� ������� ��� ���?";
		break;
	default:
		return;
	}
	if (MessageBox(0, message, "���� ��������", MB_YESNO) == IDYES) {
		Reset();
	}
	else {
		game->Exit();
	}
}

void f3x3::pickBestMove(int f3x3[3][3], int pl, int pc, int *r, int *c)
{
	int score = -9999;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (f3x3[i][j] == 0) {
				f3x3[i][j] = pl;
				int s = -(negamax(f3x3, pc, pl));
				f3x3[i][j] = 0;
				if (s >= score) {
					score = s;
					*r = i;
					*c = j;
				}
			}
		}
	}
}

int f3x3::negamax(int f3x3[3][3], int pl, int pc)
{
	int score = -9999;
	if (GameOver() == pl) {//����������� ���������� � ������ ������ 1 ������
		return 1000;
	}
	else if (GameOver() == pc) {//����������� ���������� � ������ ������ 2 ������
		return -1000;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (f3x3[i][j] == 0) {
				f3x3[i][j] = pl;
				int s = -(negamax(f3x3, pc, pl));//
				f3x3[i][j] = 0;
				if (s >= score) {
					score = s;
				}
			}
		}
	}
	if (score == -9999 || score == 0) {
		return 0;
	}
	else if (score < 0) {
		return score + 1;
	}
	else if (score > 0) {
		return score - 1;
	}
}

void f3x3::Start()
{
	StartSettings();
	LoadingImage();
	Reset();
}

void f3x3::Update()
{
	// ���� ����� ������� ������� � ����
	char* message = "�������� �����?";
	if (input->IsExit()) {
		if (MessageBox(0, message, "�����.", MB_YESNO) == IDYES)
			game->Exit();
		else
			Reset();
	}
	// ���� ������ ����� ������ ����
	// P.S. 1 - ���, 2 - ���, 3 - ���
	if (input->IsMouseButtonDown(1))
	{
		// ����� ���������� ������� ������
		int x = input->GetButtonDownCoords().x / (GRID_SIZE / 3),
			y = input->GetButtonDownCoords().y / (GRID_SIZE / 3);

		// ���� �� ������ �� ������ ������
		if (grid[x][y] == 0)
		{
			// ������������� ������� ��� ����� � ������
			grid[x][y] = pl;
			if (GameOver() == -1) {
				int r, c;
				pickBestMove(grid, pc, pl, &r, &c);
				grid[r][c] = pc;
			}
			// ������ ������
			graphics->DrawImage(back, 0, 0);
			// ������ �������� � ������
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[i][j] != 0) {
						graphics->DrawImage(player[grid[i][j] - 1], i * (GRID_SIZE / 3), j * (GRID_SIZE / 3));
					}
				}
			}
			// ������� �� �����
			graphics->Flip();
			// ������������ ����� ����
			GameOverHandle(GameOver());
			}
		}
	}


