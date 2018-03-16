#pragma once

/* Define LOG to log allocation etc. */
#if 0
#define LOG(X) SDL_Log(X)
#else
#define LOG(X)
#endif
/* Window definitions */
#define WINDOW_HEIGHT 540.0f
#define WINDOW_WIDTH 960.0f

/* Camera definitions */
#define CAMERA_HALF_HEIGHT 540
#define CAMERA_HALF_WIDTH 960

/* Math definitions */
#define DEGTORAD M_PI/180.0f