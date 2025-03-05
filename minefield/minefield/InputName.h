#pragma once

#include "Scene.h"

class InputName : public Scene
{
public:
	InputName(SDL_Renderer* renderer, int width, int height, bool f = true);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
	string GetName() { return m_name; }

private:
	string m_name;
	bool m_f;
};
