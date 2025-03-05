#pragma once

#include "Scene.h"

class Info : public Scene
{
public:
	Info(SDL_Renderer* renderer, int width, int height);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
};
