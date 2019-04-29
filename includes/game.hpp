#ifndef __BETACORE_GAME_HPP__
#define __BETACORE_GAME_HPP__

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <Windows.h>
#include <GLU.h>
#include <GL/gl.h>
#elif linux
#include <GL/glu.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#define PI 3.14159265359
#include "common.hpp"
#include "client.hpp"

namespace betacore
{

class Game
{
private:
	SDL_Window *WINDOW = NULL;
	SDL_GLContext glContext;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	int MONITOR_WIDTH = 1920;
	int MONITOR_HEIGHT = 1080;
	const char *TITLE;
	bool KEEP_ALIVE = true;
	bool SHOW_GRID = false;
	SHAPE USER_CURRENT = NONE;
	SHAPE GUST_CURRENT = NONE;
	MODE ME;
	bool KEY_UP_ARROW_ACTIVE = false;
	bool KEY_DOWN_ARROW_ACTIVE = false;
	bool KEY_LEFT_ARROW_ACTIVE = false;
	bool KEY_RIGHT_ARROW_ACTIVE = false;
	bool KEY_SPACE_ACTIVE = false;
	bool KEY_RETURN_ACTIVE = false;
	bool FULL_SCREEN = false;
	Client *client = nullptr;

public:
	Game(MODE mode,
			 int port,
			 std::string url);
	~Game();
	int init();
	int initGL();

	/**
	 * Draws box for use with guest \ current screens 
	 */
	void box();
	/**
	 * Close the application
	 */
	void close();

	/*
	 * Draw a grid on the screen (G key)
	 */
	void grid();

	/*
	 * Paint the gl context
	 */
	void paint();

	/*
	 * SDL Context
	 */
	void events(SDL_Event &event);

	/*
	 * On key down events 
	 */
	void key_down(SDL_Keycode key_code);
	/*
	 * On key up events 
	 */
	void key_up(SDL_Keycode key_code);

	/*
	 * Resize the window to width : height
	 */
	void resize(int width, int height);

	/**
	 * Draw a filled triange
	 */
	void triangle();

	/*
	 * Draw a filled or wireframe triangle
	 */
	void triangle(bool filled);
	/*
	 * Draw a filled or wireframe square
	 */
	void square();
	/*
	 * Draw a filled or wireframe square
	 */
	void square(bool filled);
	/*
	 * Draw a filled or wireframe circle
	 */
	void circle();
	/*
	 * Draw a filled or wireframe circle
	 */
	void circle(bool filled);
	/*
	 * Draw a filled or wireframe pentagon
	 */
	void pentagon();
	/*
	 * Draw a filled or wireframe pentagon
	 */
	void pentagon(bool filled);
	/*
	 * Draw a wireframe rectangle
	 */
	void rectangle();
	/*
	 * Draw a filled or wireframe cross
	 */
	void cross(bool filled);
	/*
	 * Draw the key pad compass
	 */
	void compass();

	/*
	 * Event call for up
	 */
	void on_key_up_arrow();
	/*
	 * Event call for down
	 */
	void on_key_down_arrow();
	/*
	 * Event call for left
	 */
	void on_key_left_arrow();
	/*
	 * Event call for right
	 */
	void on_key_right_arrow();
	/*
	 * Event call for space
	 */
	void on_key_space();
	/*
	 * Event call for enter
	 */
	void on_key_enter();

	void top_screen();
	/*
	 * Draw user screen 
	 */
	void user_screen();
	/*
	 * Draw guest screen 
	 */
	void guest_screen();
	/*
	 * On update from network
	 */
	void update(SHAPE &s, MODE &m);
};
} // namespace betacore
#endif