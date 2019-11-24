#include "../include/draw.h"

unsigned int image_matrix[__SCREEN__BOUNDS__Y__][__SCREEN__BOUNDS__X__];
struct rectangle rect[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__];

static void set_background_colour(void);
static void draw_horizontal_line(int, int, int);
static void draw_vertical_line(int, int, int);
static void draw_rectangle(int, int, int, int, boolean);
static void refresh_rectangle(int, int, uint8);
static void draw_rectangle_at_centre(uint8 id);

static void set_background_colour(void)
{
  for (int i = 0x00; i < __SCREEN__BOUNDS__Y__; i++)
  {
    for (int j = 0x00; j < __SCREEN__BOUNDS__X__; j++)
    {
      image_matrix[i][j] = BLACK_COLOUR;
    }
  }
}

static void draw_horizontal_line(int x_beg, int x_end, int y)
{

  for (int x = x_beg; x <= x_end; x++)
  {
    image_matrix[y][x] = BLUE_COLOUR;
  }
}

static void draw_vertical_line(int y_beg, int y_end, int x)
{
  for (int y = y_beg; y <= y_end; y++)
  {
    image_matrix[y][x] = BLUE_COLOUR;
  }
}

static void draw_rectangle(int x_beg, int x_end, int y_beg, int y_end, boolean remove)
{
  for (int x = x_beg; x <= x_end; x++)
  {
    for (int y = y_beg; y <= y_end; y++)
    {
      image_matrix[y][x] = (FALSE != remove) ? BLACK_COLOUR : RED_COLOUR;
    }
  }
}

static void refresh_rectangle(int x_move, int y_move, uint8 id)
{
  draw_rectangle(rect[id].x_beg, rect[id].x_end, rect[id].y_beg, rect[id].y_end, TRUE);
  draw_rectangle(rect[id].x_beg+x_move, rect[id].x_end+x_move, rect[id].y_beg+y_move, rect[id].y_end+y_move, FALSE);
}

void update_rectangle(command update, uint8 id)
{

  if (FALSE != rect[id].is_alive)
  {
    switch (update)
    {
      case UP_COMMAND:
      {
        refresh_rectangle(NONE, UP, id);
      } break;
      case DOWN_COMMAND:
      {
        refresh_rectangle(NONE, DOWN, id);
      } break;
      case LEFT_COMMAND:
      {
        refresh_rectangle(LEFT, NONE, id);
      } break;
      case RIGHT_COMMAND:
      {
        refresh_rectangle(RIGHT, NONE, id);
      } break;
      case UP_LEFT_COMMAND:
      {
        refresh_rectangle(UP, LEFT, id);
      } break;
      case UP_RIGHT_COMMAND:
      {
        refresh_rectangle(UP, RIGHT, id);
      } break;
      case DOWN_LEFT_COMMAND:
      {
        refresh_rectangle(DOWN, LEFT, id);
      } break;
      case DOWN_RIGHT_COMMAND:
      {
        refresh_rectangle(DOWN, RIGHT, id);
      } break;
      case CENTRE_COMMAND:
      {
        refresh_rectangle(NONE, NONE, id);
        draw_rectangle_at_centre(id);
      } break;
      default:
      {
        /* Do nothing. */
      }
    }
  }
  else
  {
    /* Ignore. */
  }
}

boolean instantialise_scene(void)
{
  rect[0].is_alive = FALSE;
  rect[1].is_alive = FALSE;
  rect[2].is_alive = FALSE;
  rect[3].is_alive = FALSE;

  set_background_colour();
  draw_horizontal_line(0x0000u, (int)__SCREEN__BOUNDS__X__ ,(int)(__SCREEN__BOUNDS__Y__/2));
  draw_vertical_line(0x0000u,   (int)__SCREEN__BOUNDS__Y__ ,(int)(__SCREEN__BOUNDS__X__/2));
}

static void draw_rectangle_at_centre(uint8 id)
{
  if ((0 <= id) && (3>= id))
  {
    if (0 == id)
    {
      rect[id].x_beg = 0;
      rect[id].x_end = 0;
      rect[id].y_beg = 0;
      rect[id].y_end = 0;
    }
    else if (1 == id)
    {
      rect[id].x_beg = 0;
      rect[id].x_end = 0;
      rect[id].y_beg = 0;
      rect[id].y_end = 0;
    }
    else if (2 == id)
    {
      rect[id].x_beg = 0;
      rect[id].x_end = 0;
      rect[id].y_beg = 0;
      rect[id].y_end = 0;
    }
    else if (3 == id)
    {
      rect[id].x_beg = 0;
      rect[id].x_end = 0;
      rect[id].y_beg = 0;
      rect[id].y_end = 0;
    }
    else
    {
      /* Unreachable. */
    }
  }
  else
  {
    /* Wrong ID. */
  }
}
