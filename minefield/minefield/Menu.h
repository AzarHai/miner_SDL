#pragma once

#include "Scene.h"

class Menu : public Scene
{
public:
	Menu(SDL_Renderer* renderer, int width, int height);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
};

