#include <iostream>

#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Info.h"
#include "Game.h"
#include "Records.h"
#include "Screensaver.h"
#include "InputName.h"

using namespace std;

Window* wnd;

int WIDTH = 800, HEIGHT = 600;

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Ru");

	wnd = new Window("Minefield", WIDTH, HEIGHT);

	Scene* scene = new Screensaver(wnd->GetRenderer(), WIDTH, HEIGHT);
	scene->Render();
	SDL_Delay(3000);
	bool isInputName = true;
	string name;
	scene = new InputName(wnd->GetRenderer(), WIDTH, HEIGHT, false);

	Uint32 frameStart;
	int frameTime;

	while (wnd->IsOpened())
	{
		frameStart = SDL_GetTicks();

		switch (scene->HandleEvents())
		{
		case -1:
			wnd->SetOpened(false);
			break;
		case 1:
			scene = new Game(wnd->GetRenderer(), WIDTH, HEIGHT);
			static_cast<Game*>(scene)->SetName(name);
			isInputName = false;
			break;
		case 2:
			scene = new InputName(wnd->GetRenderer(), WIDTH, HEIGHT);
			isInputName = true;
			break;
		case 3:
			scene = new Records(wnd->GetRenderer(), WIDTH, HEIGHT);
			isInputName = false;
			break;
		case 4:
			scene = new Info(wnd->GetRenderer(), WIDTH, HEIGHT);
			isInputName = false;
			break;
		case 5:
			if (isInputName && static_cast<InputName*>(scene)->GetName() != "") 
				name = static_cast<InputName*>(scene)->GetName();
			isInputName = false;
			scene = new Menu(wnd->GetRenderer(), WIDTH, HEIGHT);
			break;
		}

		scene->Update();
		scene->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	delete wnd;

	return 0;
}