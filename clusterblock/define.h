#ifndef DEFINE_H__
#define DEFINE_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#ifdef _WIN32
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/glew.h>
#endif

#define SHADER_PATH "../mcclone/media/shaders/"
#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16
#define FALLSPEED 1
#define JUMP_HEIGHT 1
#define WALK_SPEED 8
#define MAX_SELECTION_DISTANCE 5

typedef uint8_t BlockType;
enum BLOCK_TYPE {BTYPE_AIR, BTYPE_DIRT, BTYPE_GRASS, BTYPE_PLANK, BTYPE_COBBLE, BTYPE_LAST};


#define TEXTURE_PATH        "../mcclone/media/textures/"
#define VIEW_DISTANCE       128
#define DEFAULT_PORT        7777

#endif // DEFINE_H__
