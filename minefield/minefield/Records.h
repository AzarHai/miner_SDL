#pragma once

#include "Scene.h"
#include "Scores.h"

class Records : public Scene
{
public:
	Records(SDL_Renderer* renderer, int width, int height);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
	void DrawTable(vector<Score> scores);

private:
	bool m_isReading;
};
