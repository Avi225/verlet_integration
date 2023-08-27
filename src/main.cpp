#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "aMath.hpp"
#include "aWindow.hpp"
#include "aUtility.hpp"
#include "aClothSimulation.hpp"
#include "aUserInterface.hpp"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	IMG_Init(IMG_INIT_PNG);

	TTF_Init();

	aWindow window("cloth", 1280, 720);

	aClothSimulation simulation(&window);
	aUserInterface interface(&window);

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utility::hireTimeInSeconds();

	Uint32 fpsStart, fpsFrame;
	float fps;

	interface.createHeader(aHeader(vector2f(20, 20), std::string("settings")));

	interface.createHeader(aHeader(vector2f(40, 40), std::string("editor")));
	interface.createSwitchB(aSwitchB(simulation.getEditorShowPoints(), vector2f(60, 60), std::string("show points")));
	interface.createSwitchB(aSwitchB(simulation.getEditorShowSticks(), vector2f(60, 80), std::string("show sticks")));

	interface.createHeader(aHeader(vector2f(40, 100), std::string("simulation")));
	interface.createSwitchB(aSwitchB(simulation.getSimulationShowPoints(), vector2f(60, 120), std::string("show points")));
	interface.createSwitchB(aSwitchB(simulation.getSimulationShowSticks(), vector2f(60, 140), std::string("show sticks")));
	interface.createSliderF(aSliderF(&simulation.getGravityPointer()->x, vector2f(60, 170), 200, std::string("gravity x"), -5, 5));
	interface.createSliderF(aSliderF(&simulation.getGravityPointer()->y, vector2f(60, 210), 200, std::string("gravity y"), -5, 5));
	interface.createSwitchB(aSwitchB(simulation.getShowStretchPointer(), vector2f(60, 250), std::string("show stretch")));
	interface.createSwitchB(aSwitchB(simulation.getShowCompressionPointer(), vector2f(60, 270), std::string("show compression")));

	interface.createHeader(aHeader(vector2f(20, 310), std::string("controls")));
	interface.createText(aText(vector2f(40, 330), std::string("spacebar - start/stop simulation")));
	interface.createText(aText(vector2f(40, 350), std::string("p - create point")));
	interface.createText(aText(vector2f(40, 370), std::string("l - lock point")));
	interface.createText(aText(vector2f(40, 390), std::string("d - delete point")));
	interface.createText(aText(vector2f(40, 410), std::string("s - create stick")));
	interface.createText(aText(vector2f(40, 430), std::string("f - delete stick")));
	interface.createText(aText(vector2f(40, 450), std::string("g - generate grid")));
	interface.createText(aText(vector2f(40, 470), std::string("a - huj")));

	interface.createSliderF(aSliderF(&fps, vector2f(40, 500), 0, std::string("fps"), 0, 100));

	bool running = true;

	while (running)
	{
		fpsStart = SDL_GetTicks();
		int startTicks = SDL_GetTicks();
		float newTime = utility::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator > + timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (interface.checkSelectedSlider() != NULL)
					{
						interface.checkSelectedSlider()->setSelected(true);
						std::cout << interface.checkSelectedSlider()->getName().c_str() << std::endl;
					}
					if (interface.checkPressedSwitch() != NULL)
					{
						interface.checkPressedSwitch()->switchValue();
					}
					break;
				case SDL_MOUSEBUTTONUP:
					interface.unselectAllSliders();
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_p:
						simulation.mouseSpawnPoint();
						break;
					case SDLK_l:
						simulation.switchLockPoint(simulation.checkClosestPoint());
						break;
					case SDLK_s:
						if (event.key.repeat == 0)
						{
							simulation.setStickMaker(simulation.checkClosestPoint());
						}
						break;
					case SDLK_SPACE:
						simulation.switchIsSimulating();
						break;
					case SDLK_d:
						if (simulation.checkClosestPoint() != NULL)
							simulation.deletePoint(simulation.checkClosestPoint());
						break;
					case SDLK_f:
						simulation.mouseDeleteStick();
						break;
					case SDLK_g:
						simulation.generateGrid();
						break;
					}
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_s:
						if (event.key.repeat == 0 && event.key.state == SDL_RELEASED)
						{
							simulation.spawnStick(simulation.checkClosestPoint());
						}
						break;
					}
				}
			}
			accumulator = timeStep;
		}

		window.clear();
		simulation.updateSimulation();
		interface.updateUserInterface();
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		fpsFrame = SDL_GetTicks() - fpsStart;
		fps = (fpsFrame > 0) ? 1000.0f / fpsFrame : 0.0f;

	}

	TTF_Quit();
	window.cleanUp();
	SDL_Quit();
	return 0;
}
