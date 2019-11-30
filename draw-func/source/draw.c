#include "../include/draw.h"

unsigned int image_matrix[__SCREEN__BOUNDS__Y__][__SCREEN__BOUNDS__X__];
struct rectangle rect[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__];

static struct rectangle rect_centre[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__] =
{
  /* USER_1 */
  {
    .x_beg = 150,   //(uint16)(1/4)*(__SCREEN__BOUNDS__X__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .x_end = 170,   //(uint16)(1/4)*(__SCREEN__BOUNDS__X__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_beg = 110,   //(uint16)(1/4)*(__SCREEN__BOUNDS__Y__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_end = 130    //(uint16)(1/4)*(__SCREEN__BOUNDS__Y__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__)
  },
  /* USER_2 */
  {
    .x_beg = 470,   //(uint16)(3/4)*(__SCREEN__BOUNDS__X__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .x_end = 490,   //(uint16)(3/4)*(__SCREEN__BOUNDS__X__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_beg = 110,   //(uint16)(1/4)*(__SCREEN__BOUNDS__Y__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_end = 130    //(uint16)(1/4)*(__SCREEN__BOUNDS__Y__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__)
  },
  /* USER_3 */
  {
    .x_beg = 150,   //(uint16)(1/4)*(__SCREEN__BOUNDS__X__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .x_end = 170,   //(uint16)(1/4)*(__SCREEN__BOUNDS__X__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_beg = 350,   //(uint16)(3/4)*(__SCREEN__BOUNDS__Y__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_end = 370    //(uint16)(3/4)*(__SCREEN__BOUNDS__Y__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__)
  },
  /* USER_4 */
  {
    .x_beg = 470,   //(uint16)(3/4)*(__SCREEN__BOUNDS__X__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .x_end = 490,   //(uint16)(3/4)*(__SCREEN__BOUNDS__X__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_beg = 350,   //(uint16)(3/4)*(__SCREEN__BOUNDS__Y__)-(uint16)(1/2)*(__SQUARE__PIXSIZE__),
    .y_end = 370    //(uint16)(3/4)*(__SCREEN__BOUNDS__Y__)+(uint16)(1/2)*(__SQUARE__PIXSIZE__)
  }
};

static void set_background_colour(void);
static void draw_horizontal_line(int, int, int);
static void draw_vertical_line(int, int, int);
static void draw_rectangle(int, int, int, int, boolean);
static boolean is_new_position_out_of_bounds(int, int, uint8);
static void refresh_rectangle(int, int, uint8);
static void draw_rectangle_at_centre(uint8 id);
static void destroy_rectangle(uint8 id);

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

static boolean is_new_position_out_of_bounds(int x_move, int y_move, uint8 id)
{
  if (FALSE != rect[id].is_alive)
  {
    switch (id)
    {
      case USER_1:
      {
        uint16 new_x_loc_valid = (((rect[id].x_beg + x_move) > COORDINATE_0) && ((rect[id].x_end + x_move) < 320)) ? (TRUE) : (FALSE);
        uint16 new_y_loc_valid = (((rect[id].y_beg + y_move) > COORDINATE_0) && ((rect[id].y_end + y_move) < 240)) ? (TRUE) : (FALSE);

        return (new_x_loc_valid & new_y_loc_valid);
      }
      case USER_2:
      {
        uint16 new_x_loc_valid = (((rect[id].x_beg + x_move) > 320) && ((rect[id].x_end + x_move) < 640)) ? (TRUE) : (FALSE);
        uint16 new_y_loc_valid = (((rect[id].y_beg + y_move) >= COORDINATE_0) && ((rect[id].y_end + y_move) < 240)) ? (TRUE) : (FALSE);

        return (new_x_loc_valid & new_y_loc_valid);
      }
      case USER_3:
      {
        uint16 new_x_loc_valid = (((rect[id].x_beg + x_move) > COORDINATE_0) && ((rect[id].x_end + x_move) < 320)) ? (TRUE) : (FALSE);
        uint16 new_y_loc_valid = (((rect[id].y_beg + y_move) > 240) && ((rect[id].y_end + y_move) < 480)) ? (TRUE) : (FALSE);

        return (new_x_loc_valid & new_y_loc_valid);
      }
      case USER_4:
      {
        uint16 new_x_loc_valid = (((rect[id].x_beg + x_move) > 320) && ((rect[id].x_end + x_move) < 640)) ? (TRUE) : (FALSE);
        uint16 new_y_loc_valid = (((rect[id].y_beg + y_move) > 240) && ((rect[id].y_end + y_move) < 480)) ? (TRUE) : (FALSE);

        return (new_x_loc_valid & new_y_loc_valid);
      }
      default:
      {
        /* Wrong ID. */
      }
    }
  }
}

static void refresh_rectangle(int x_move, int y_move, uint8 id)
{
  uint16 is_OK = is_new_position_out_of_bounds(x_move, y_move, id);

  if (FALSE != is_OK)
  {
    draw_rectangle(rect[id].x_beg,        rect[id].x_end,        rect[id].y_beg,        rect[id].y_end,         TRUE);
    draw_rectangle(rect[id].x_beg+x_move, rect[id].x_end+x_move, rect[id].y_beg+y_move, rect[id].y_end+y_move, FALSE);

    rect[id].x_beg += x_move;
    rect[id].x_end += x_move;
    rect[id].y_beg += y_move;
    rect[id].y_end += y_move;
  }
  else
  {
    /* Do not move the rectangle. Boundary reached. */
  }
}

static void draw_rectangle_at_centre(uint8 id)
{
  if ((USER_1 <= id) && (USER_4 >= id))
  {
    if (USER_1 == id)
    {
      rect[id].x_beg = rect_centre[USER_1].x_beg;
      rect[id].x_end = rect_centre[USER_1].x_end;
      rect[id].y_beg = rect_centre[USER_1].y_beg;
      rect[id].y_end = rect_centre[USER_1].y_end;
    }
    else if (USER_2 == id)
    {
      rect[id].x_beg = rect_centre[USER_2].x_beg;
      rect[id].x_end = rect_centre[USER_2].x_end;
      rect[id].y_beg = rect_centre[USER_2].y_beg;
      rect[id].y_end = rect_centre[USER_2].y_end;
    }
    else if (USER_3 == id)
    {
      rect[id].x_beg = rect_centre[USER_3].x_beg;
      rect[id].x_end = rect_centre[USER_3].x_end;
      rect[id].y_beg = rect_centre[USER_3].y_beg;
      rect[id].y_end = rect_centre[USER_3].y_end;
    }
    else if (USER_4 == id)
    {
      rect[id].x_beg = rect_centre[USER_4].x_beg;
      rect[id].x_end = rect_centre[USER_4].x_end;
      rect[id].y_beg = rect_centre[USER_4].y_beg;
      rect[id].y_end = rect_centre[USER_4].y_end;
    }
    else
    {
      /* Unreachable. */
    }
    destroy_rectangle(id);
    draw_rectangle(
      rect[id].x_beg,
      rect[id].x_end,
      rect[id].y_beg,
      rect[id].y_end,
      FALSE
    );
    update_graphics();
  }
  else
  {
    /* Wrong ID. */
    fprintf (stderr, "FATAL::Passed ID(%d) argument is not allowed!\n", id);
    exit (ERROR);
  }
}

static void destroy_rectangle(uint8 id)
{
  if ((USER_1 <= id) && (USER_4 >= id))
  {
    if (USER_1 == id)
    {
      draw_rectangle(
        COORDINATE_0,
        319,                //(uint16)(1/2)*(__SCREEN__BOUNDS__X__)-1,
        COORDINATE_0,
        239,                //(uint16)(1/2)*(__SCREEN__BOUNDS__Y__)-1,
        TRUE
      );
      update_graphics();
    }
    if (USER_2 == id)
    {
      draw_rectangle(
        321,                //(uint16)(1/2)*(__SCREEN__BOUNDS__X__)+1,
        __SCREEN__BOUNDS__X__,
        COORDINATE_0,
        239,                //(uint16)(1/2)*(__SCREEN__BOUNDS__Y__)-1,
        TRUE
      );
      update_graphics();
    }
    if (USER_3 == id)
    {
      draw_rectangle(
        COORDINATE_0,
        319,                //(uint16)(1/2)*(__SCREEN__BOUNDS__X__)-1,
        241,                //(uint16)(1/2)*(__SCREEN__BOUNDS__Y__)+1,
        __SCREEN__BOUNDS__Y__,
        TRUE
      );
      update_graphics();
    }
    if (USER_4 == id)
    {
      draw_rectangle(
        321,                //(uint16)(1/2)*(__SCREEN__BOUNDS__X__)+1,
        __SCREEN__BOUNDS__X__,
        241,                //(uint16)(1/2)*(__SCREEN__BOUNDS__Y__)+1,
        __SCREEN__BOUNDS__Y__,
        TRUE
      );
      update_graphics();
    }
  }
  else
  {
    /* Wrong ID. */
    fprintf (stderr, "FATAL::Passed ID(%d) argument is not allowed!\n", id);
    exit (ERROR);
  }
}

void update_rectangle(command update, uint8 id)
{
  static int last_used_command[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__] = {
    UNKNOWN_COMMAND,
    UNKNOWN_COMMAND,
    UNKNOWN_COMMAND,
    UNKNOWN_COMMAND
  };

  if (FALSE != rect[id].is_alive)
  {
    switch (update)
    {
      case UP_COMMAND:
      {
        up_command_jump:

        refresh_rectangle(NONE, UP, id);
        last_used_command[id] = UP_COMMAND;
      } break;
      case DOWN_COMMAND:
      {
        down_command_jump:

        last_used_command[id] = DOWN_COMMAND;
        refresh_rectangle(NONE, DOWN, id);
      } break;
      case LEFT_COMMAND:
      {
        left_command_jump:

        refresh_rectangle(LEFT, NONE, id);
        last_used_command[id] = LEFT_COMMAND;
      } break;
      case RIGHT_COMMAND:
      {
        right_command_jump:

        refresh_rectangle(RIGHT, NONE, id);
        last_used_command[id] = RIGHT_COMMAND;
      } break;
      case UP_LEFT_COMMAND:
      {
        up_left_command_jump:

        refresh_rectangle(UP, LEFT, id);
        last_used_command[id] = UP_LEFT_COMMAND;
      } break;
      case UP_RIGHT_COMMAND:
      {
        up_right_command_jump:

        refresh_rectangle(-UP, -RIGHT, id);
        last_used_command[id] = UP_RIGHT_COMMAND;
      } break;
      case DOWN_LEFT_COMMAND:
      {
        down_left_command_jump:

        refresh_rectangle(-DOWN, -LEFT, id);
        last_used_command[id] = DOWN_LEFT_COMMAND;
      } break;
      case DOWN_RIGHT_COMMAND:
      {
        down_right_command_jump:

        refresh_rectangle(DOWN, RIGHT, id);
        last_used_command[id] = DOWN_RIGHT_COMMAND;
      } break;
      case CENTRE_COMMAND:
      {
        last_used_command[id] = CENTRE_COMMAND;    /* Special case. Does not have repetition of command. */
        draw_rectangle_at_centre(id);
      } break;
      case DESTROY_ON_DISCONNECTION:
      {
        last_used_command[id] = UNKNOWN_COMMAND;    /* Special case. */
        destroy_rectangle(id);
      } break;
      case REPEAT_COMMAND:
      {
        if (UP_COMMAND == last_used_command[id])
        {
          goto up_command_jump;
        }
        else if (DOWN_COMMAND == last_used_command[id])
        {
          goto down_command_jump;
        }
        else if (LEFT_COMMAND == last_used_command[id])
        {
          goto left_command_jump;
        }
        else if (RIGHT_COMMAND == last_used_command[id])
        {
          goto right_command_jump;
        }
        else if (UP_LEFT_COMMAND == last_used_command[id])
        {
          goto up_left_command_jump;
        }
        else if (UP_RIGHT_COMMAND == last_used_command[id])
        {
          goto up_right_command_jump;
        }
        else if (DOWN_LEFT_COMMAND == last_used_command[id])
        {
          goto down_left_command_jump;
        }
        else if (DOWN_RIGHT_COMMAND == last_used_command[id])
        {
          goto down_right_command_jump;
        }
        else
        {
          /* Ignore. */
        }
      } break;
      default:
      {
        /* Do nothing. */
      } break;
    }
  }
  else
  {
    /* Ignore. */
  }
}

boolean instantialise_scene(void)
{
  rect[USER_1].is_alive = FALSE;
  rect[USER_2].is_alive = FALSE;
  rect[USER_3].is_alive = FALSE;
  rect[USER_4].is_alive = FALSE;

  set_background_colour();
  draw_horizontal_line(COORDINATE_0, __SCREEN__BOUNDS__X__, 240);
  draw_vertical_line(COORDINATE_0,   __SCREEN__BOUNDS__Y__, 320);

  update_graphics();
}
