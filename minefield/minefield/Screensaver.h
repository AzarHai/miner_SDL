#pragma once

#include "Scene.h"

class Screensaver : public Scene
{
public:
	Screensaver(SDL_Renderer* renderer, int width, int height);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
};
