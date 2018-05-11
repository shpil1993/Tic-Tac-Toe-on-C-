#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Project.h"

class Game;

class Screen
{
protected:
	Game* game;
public:
	void SetController(Game* game);

	virtual void Start();
	virtual void Update();
	virtual void Destroy();
};

#endif

