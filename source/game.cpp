#include "game.hpp"

namespace betacore
{
Game::Game()
{
	if (init())
	{
		printf("Error loading init\n");
		return;
	}
	SDL_Event event;

	while (this->KEEP_ALIVE)
	{
		//Handle Events
		this->events(event);
		this->paint();
	}
	close();
}
Game::~Game() {}

int Game::init()
{
	int result = 0;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Problem loading SLD Error: %s\n", SDL_GetError());
	}
	else
	{
		//OPEN GL VERSION 2.X
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		//OPEN GL VERSION ^.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		int videoFlags = SDL_WINDOW_OPENGL;
		videoFlags |= SDL_WINDOW_SHOWN;
		videoFlags |= SDL_WINDOW_RESIZABLE;

		this->WINDOW = SDL_CreateWindow(
				this->TITLE,
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				this->SCREEN_WIDTH,
				this->SCREEN_HEIGHT,
				videoFlags);
		if (WINDOW == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			result = -1;
		}
		else
		{
			glContext = SDL_GL_CreateContext(WINDOW);

			if (glContext == NULL)
			{
				printf("Unable to crate Open GL Context: %s\n", SDL_GetError());
				result = -2;
			}
			else
			{
				//Try Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Vsync error:%s\n", SDL_GetError());
				}

				if (initGL())
				{
					printf("Problem working with OpenGL");
				}
			}
		}
	}

	return result;
}

int Game::initGL()
{
	int result = 0;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // This Will Clear The Background Color To Black
	glClearDepth(1.0);										// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
	glMatrixMode(GL_PROJECTION);
	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLoadIdentity();
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		printf("OpenGL Error %s\n", gluErrorString(error));
		result = -1;
		return result;
	}

	glMatrixMode(GL_MODELVIEW);

	// Set up the view port
	glViewport(0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
			45.0f,
			(GLfloat)this->SCREEN_WIDTH / (GLfloat)this->SCREEN_HEIGHT,
			0.1f,
			100.0f);
	glMatrixMode(GL_MODELVIEW);

	return result;
}

void Game::close()
{
	SDL_DestroyWindow(this->WINDOW);
	WINDOW = NULL;
	SDL_Quit();
}

void Game::grid()
{
	glPushMatrix();
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,gray);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glLineWidth(2.5);
	glColor3f(1.0, 1.0, 1.0);

	/*grid*/
	float GRIDE_SIZE = 100;
	//X
	glBegin(GL_LINES);
	glVertex2f(-GRIDE_SIZE, 0);
	glVertex2f(GRIDE_SIZE, 0);
	glEnd();
	//Y
	glBegin(GL_LINES);
	glVertex2f(0, -GRIDE_SIZE);
	glVertex2f(0, GRIDE_SIZE);
	glEnd();
	//Z
	glBegin(GL_LINES);
	glVertex3f(0, 0, -GRIDE_SIZE);
	glVertex3f(0, 0, GRIDE_SIZE);
	glEnd();

	//X ticks
	float TICK_SIZE = .5;
	for (float f = -GRIDE_SIZE; f <= GRIDE_SIZE; f += 1)
	{
		//X
		glBegin(GL_LINES);
		glVertex3f(f, -TICK_SIZE, 0);
		glVertex3f(f, TICK_SIZE, 0);
		glEnd();
		//Y
		glBegin(GL_LINES);
		glVertex2f(-TICK_SIZE, f);
		glVertex2f(TICK_SIZE, f);
		glEnd();
		//Z
		glBegin(GL_LINES);
		glVertex3f(0, -TICK_SIZE, f);
		glVertex3f(0, TICK_SIZE, f);
		glEnd();
	}
	glPopMatrix();
}
void Game::triangle()
{
	glBegin(GL_POLYGON);						// start drawing a polygon
	glColor3f(1.0f, 0.0f, 0.0f);		// Set The Color To Red
	glVertex3f(0.0f, 1.0f, 0.0f);		// Top
	glVertex3f(1.0f, -1.0f, 0.0f);	// Bottom Right
	glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	glEnd();												// we're done with the polygon (smooth color interpolation)
}
void Game::square()
{
	glBegin(GL_QUADS);							// start drawing a polygon (4 sided)
	glVertex3f(-1.0f, 1.0f, 0.0f);	// Top Left
	glVertex3f(1.0f, 1.0f, 0.0f);		// Top Right
	glVertex3f(1.0f, -1.0f, 0.0f);	// Bottom Right
	glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	glEnd();												// done with the polygon
}

void Game::box()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0f, 1.0f, 0.0f);	// Top Left
	glVertex3f(1.0f, 1.0f, 0.0f);		// Top Right
	glVertex3f(1.0f, -1.0f, 0.0f);	// Bottom Right
	glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	glEnd();
}
void Game::rectangle(){
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2.5f, 1.0f, 0.0f);	// Top Left
	glVertex3f(2.5f, 1.0f, 0.0f);		// Top Right
	glVertex3f(2.5f, -1.0f, 0.0f);	// Bottom Right
	glVertex3f(-2.5f, -1.0f, 0.0f); // Bottom Left
	glEnd();
}

void Game::circle()
{
	// glBegin(GL_LINE_LOOP);
	//    for(int i =0; i <= 300; i++){
	//        double angle = 2 * PI * i / 300;
	//        double x = cos(angle);
	//        double y = sin(angle);
	//        glVertex2d(x,y);
	//    }
	// glEnd();
	// this code (mostly) copied from question:
	double radius = 1;
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius * sin(angle1));
		angle1 += angle;
	}
	glEnd();
}
void Game::pentagon()
{
	float angleIncrement = 360.0f / 5.0f;
	angleIncrement *= PI / 180.0f;
	glBegin(GL_TRIANGLE_FAN);
	float angle = 0.0f;
	double radius = 1;
	for (int k = 0; k < 100; ++k)
	{
		glVertex3f(radius * cos(angle), radius * sin(angle), 0.0f);
		angle += angleIncrement;
	}
	glEnd();
}
void Game::user_screen()
{
	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, -6.0f);
	this->box();

	//this->box();
	//glTranslatef(-1.5f, 0.0f, -6.0f); // Move Left 1.5 Units And Into The Screen 6.0
	glTranslatef(-1.5f, -1.0f, -6.0f);
	// draw a triangle (in smooth coloring mode)
	switch (USER_CURRENT)
	{
	case TRIANGLE:
		glColor3f(1.0f, 0.0f, 0.0f);
		this->triangle();
		break;
	case CIRCLE:
		glColor3f(0.0f, 1.0f, 0.0f);
		this->circle();
		break;
	case SQUARE:
		glColor3f(0.0f, 0.0f, 1.0f);
		this->square();
		break;
	case PENTAGON:
		glRotatef(-54.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		this->pentagon();
		break;
	}

	// glTranslatef(3.0f, 0.0f, 0.0f); // Move Right 3 Units
	// // draw a square (quadrilateral)

	// glColor3f(0.5f, 0.5f, 1.0f); // set color to a blue shade.

	glPopMatrix();
}
void Game::guest_screen(){
	glPushMatrix();
	glTranslatef(1.5f, -1.0f, -6.0f);
	this->box();
	glPopMatrix();
}
void Game::top_screen(){
	glPushMatrix();
	glTranslatef(-0.0f, 1.25f, -6.0f);
	this->rectangle();
	glPopMatrix();
	
}
void Game::paint()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (this->SHOW_GRID)
	{
		this->grid();
	}
	this->top_screen();
	this->user_screen();
	this->guest_screen();

	SDL_GL_SwapWindow(this->WINDOW);
}
void Game::resize(int width, int height)
{
	glViewport(0, 0, width, height); // Reset The USER_CURRENT Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * key down
 * SDL_Keycode key_code
 */
void Game::key_down(SDL_Keycode key_code)
{
	switch (key_code)
	{
	case SDLK_ESCAPE:
	case SDLK_q:
		printf("Escape\n");
		this->KEEP_ALIVE = false;
		break;

	case SDLK_UP:
		printf("UP Key Pressed\n");
		this->on_key_up_arrow();
		break;

	case SDLK_DOWN:
		printf("Down Key Pressed\n");
		this->on_key_down_arrow();
		break;

	case SDLK_LEFT:
		printf("Left Key Pressed\n");
		this->on_key_left_arrow();
		break;

	case SDLK_RIGHT:
		printf("Right Key Pressed\n");
		this->on_key_right_arrow();
		break;
	case SDLK_g:
		this->SHOW_GRID = !SHOW_GRID;
		break;
	case SDLK_SPACE:
		printf("Space Key Pressed\n");
		break;

	default:
		//Do nothing
		break;
	}
}
void Game::events(SDL_Event &event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		//https://wiki.libsdl.org/SDL_EventType
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				//resize();
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				this->resize(event.window.data1, event.window.data2);
				break;
			}
			break;
			//user-requested quit
		case SDL_QUIT:
			this->KEEP_ALIVE = false;
			break;

		//Mouse events
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			break;
			//Keyboard Events
		case SDL_KEYDOWN:
			this->key_down(event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			//Todo Key up commands
			break;

		} //end switch(event.type)

	} //end-while
}

void Game::on_key_up_arrow()
{
	// Toggle triangle
	this->USER_CURRENT = TRIANGLE;
}
void Game::on_key_down_arrow()
{
	this->USER_CURRENT = SQUARE;
}
void Game::on_key_left_arrow()
{
	this->USER_CURRENT = PENTAGON;
}
void Game::on_key_right_arrow()
{
	this->USER_CURRENT = CIRCLE;
}
void Game::on_key_space()
{
}
void Game::on_key_enter()
{
}
} // namespace betacore

int main(int argc, char *argv[])
{
	betacore::Game game;
	return 0;
}