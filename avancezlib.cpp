#include "avancezlib.h"

// Creates the main window. Returns true on success.
bool AvancezLib::init(int width, int height)
{
	SDL_Log("Initializing the system...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	m_window = SDL_CreateWindow("LUNAR LANDER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	//Create renderer for window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	TTF_Init();
	m_font = TTF_OpenFont("data/space_invaders.ttf", 12); //this opens a font style and sets a size
	if (m_font == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// initialize the keys
	m_key.fire = false;	m_key.left = false;	m_key.right = false;

	//Initialize renderer color
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);

	//Clear screen
	SDL_RenderClear(m_renderer);

	SDL_Log("System up and running...\n");
	return true;
}


// Destroys the avancez library instance
void AvancezLib::destroy()
{
	SDL_Log("Shutting down the system\n");

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	TTF_CloseFont(m_font);

	TTF_Quit();
	SDL_Quit();
}


bool AvancezLib::update()
{
	SDL_Event event;


	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return false;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_q:
				return false;
			case SDLK_SPACE:
				m_key.fire = true;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				m_key.left = true;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				m_key.right = true;
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				m_key.fire = false;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				m_key.left = false;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				m_key.right = false;
				break;
			}
		}

	}

	//Update screen
	SDL_RenderPresent(m_renderer);

	//Clear screen
	SDL_RenderClear(m_renderer);

	return true;
}


Sprite * AvancezLib::createSprite(const char * path)
{
	SDL_Surface* surf = SDL_LoadBMP(path);
	if (surf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture * texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);

	Sprite * sprite = new Sprite(m_renderer, texture);

	return sprite;
}

void AvancezLib::drawText(int x, int y, const char * msg)
{
	//SDL_Color black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Color text_color = { 255, 255, 255 };

	SDL_Surface* surf = TTF_RenderText_Solid(m_font, msg, text_color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(m_renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { x, y, w, h };

	SDL_RenderCopy(m_renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

float AvancezLib::getElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

void AvancezLib::getKeyStatus(KeyStatus & keys)
{
	keys.fire = m_key.fire;
	keys.left = m_key.left;
	keys.right = m_key.right;
}


Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture)
{
	m_renderer = renderer;
	m_texture = texture;
}


void Sprite::draw(int x, int y, float angle)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;

	SDL_QueryTexture(m_texture, NULL, NULL, &(rect.w), &(rect.h));
	SDL_Point center;
	center.x = (int)(rect.w / 2.f);
	center.y = (int)(rect.h / 2.f);

	//Render texture to screen
//	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_RenderCopyEx(m_renderer,
		m_texture,
		NULL,
		&rect,
		angle,
		&center,
		SDL_FLIP_NONE);
}


void Sprite::destroy()
{
	SDL_DestroyTexture(m_texture);
}

