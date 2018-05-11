#pragma once
#include "Project.h"


class f3x3 : public Screen
{
private:
	const int GRID_SIZE = 384;
	Input* input;
	Graphics* graphics;
	Image* back;
	Image *player[2];
	int pl;
	int pc;
	int grid[3][3];
	void StartSettings();
	void LoadingImage();
	void Reset();
	int GameOver();
	void GameOverHandle(int over);
	void pickBestMove(int f3x3[3][3], int pl, int pc, int *r, int *c);
	int negamax(int f3x3[3][3], int pl, int pc);
public:
	void Start();
	void Update();
public:
	f3x3();
	virtual ~f3x3();
};

