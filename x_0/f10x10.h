#pragma once
#include "Project.h"


class f10x10 : public Screen
{
private:
	const int GRID_SIZE = 384;
	Input* input;
	Graphics* graphics;
	Image* back;
	Image *player[2];
	int pl;
	int pc;
	int grid[10][10];
	void StartSettings();
	void LoadingImage();
	void Reset();
	int GameOver();
	void GameOverHandle(int over);
	void pickBestMove(int f10x10[10][10], int i, int j, int *mi, int *mj, int count);
public:
	void Start();
	void Update();
	f10x10();
	virtual ~f10x10();
};

