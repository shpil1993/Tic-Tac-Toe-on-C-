#pragma once
#include "Project.h"

class Rules : public Screen
{
	const int GRID_SIZE = 384;
	Input* input;
	Graphics* graphics;
	Image* back;
	int grid[3][3];
	void StartSettings();
	void LoadingImage();
	void Reset();
public:
	void Start();
	void Update();
	Rules();
	virtual ~Rules();
};

