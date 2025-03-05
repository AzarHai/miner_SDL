#pragma once

#include "Scene.h"
#include "Scores.h"
#include <functional>
#include <random>

const int SIZE = 10;
const int FSIZE = 30;
const int MINES = 20;

const int DELAY = 2000;

class Game : public Scene
{
public:
	Game(SDL_Renderer* renderer, int width, int height);
	void Update() override;
	void Render() override;
	int HandleEvents() override;
	void SetupDesk();
	void SetName(string name) { m_name = name; }

private:
	function<void(void)> m_render;
	function<void(void)> m_renderGame;
	function<void(void)> m_renderPause;
	function<void(void)> m_renderWin;
	function<void(void)> m_renderGameOver;
	function<void(void)> m_openDesk;
	function<void(void)> m_closeDesk;
	SDL_Rect m_field[SIZE][SIZE];
	int m_matrix[SIZE][SIZE];
	int m_xpos = 0, m_ypos = 0;
	bool m_inputName;
	bool m_pause;
	bool m_show;
	bool m_gameOver;
	string m_name;

	Uint32 m_startTime;
	int m_time;
	int m_pauseTime;
};
