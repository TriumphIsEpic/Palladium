#pragma once

#include "Engine.h"
#include <SDL/SDL.h>

#include <string>


class Display
{
public:
	Display(uint_16 width, uint_16 height, const std::string& title);
	bool isCLosed = false;
	void Clear(float r, float g, float b, float a);
	virtual ~Display();
	void SwapBuffers();
	void Update();
private:
	Display(const Display& other) {}
	Display& operator=(const Display& other) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

