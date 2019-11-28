#if !defined(__DRAW__)
#define __DRAW__

#include "../../platform/platform.h"
#include "../../parser/include/compiler.h"
#include "../../parser/include/interpreter.h"

#define COORDINATE_0            0u

#define __SQUARE__PIXSIZE__    40u

#define __SCREEN__BOUNDS__X__ 640u
#define __SCREEN__BOUNDS__Y__ 480u

#define BLACK_COLOUR 0x0000u
#define RED_COLOUR   0xF800u
#define BLUE_COLOUR  0x001Fu

#define UP          -0x0A
#define DOWN        +0x0A
#define LEFT        -0x0A
#define RIGHT       +0x0A
#define NONE        +0x00

#define USER_1      0x00u
#define USER_2      0x01u
#define USER_3      0x02u
#define USER_4      0x03u

struct rectangle
{
  boolean is_alive;
  uint16 x_beg;
  uint16 x_end;
  uint16 y_beg;
  uint16 y_end;
};

extern unsigned int image_matrix[__SCREEN__BOUNDS__Y__][__SCREEN__BOUNDS__X__];
extern struct rectangle rect[4];

void update_rectangle(command, uint8);
boolean instantialise_scene(void);

#endif /* __DRAW__ */
