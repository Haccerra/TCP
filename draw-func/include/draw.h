#if !defined(__DRAW__)
#define __DRAW__

#include "../../platform/platform.h"
#include "../../socket/include/socket.h"
#include "../../parser/include/interpreter.h"

#define __SCREEN__BOUNDS__X__ 640
#define __SCREEN__BOUNDS__Y__ 480

#define BLACK_COLOUR 0x0000u
#define RED_COLOUR   0xF800u
#define BLUE_COLOUR  0x001Fu

#define UP          +0x0A
#define DOWN        -0x0A
#define LEFT        -0x0A
#define RIGHT       +0x0A
#define NONE        +0x00

struct rectangle
{
  boolean is_alive;
  uint16 x_beg;
  uint16 x_end;
  uint16 y_beg;
  uint16 y_end;
};

extern unsigned int image_matrix[__SCREEN__BOUNDS__Y__][__SCREEN__BOUNDS__X__];
extern struct rectangle moving_rectangles[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__];

void update_rectangle(command, uint8);
boolean instantialise_scene(void);

#endif /* __DRAW__ */
