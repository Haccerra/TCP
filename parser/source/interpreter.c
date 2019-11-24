#include "../include/interpreter.h"

command command_interpreter(string client_cmd)
{
  uint8 cmd_length = strlen (client_cmd);

  if (ALLOWED_LENGTH < cmd_length)
  {
    /* Error. */
    return UNKNOWN_COMMAND;
  }
  else
  {
    /* Parse the value. */
    if (BASIC_MOVEMENT == cmd_length)
    {
      switch (client_cmd[0x00u])
      {
        /* UPWARD MOVEMENT. */
        case 'W':
        case '8':
        {
          return UP_COMMAND;
        } break;
        /* DOWNWARD MOVEMENT. */
        case 'S':
        case '2':
        {
          return DOWN_COMMAND;
        } break;
        /* LEFT MOVEMENT. */
        case 'A':
        case '4':
        {
          return LEFT_COMMAND;
        } break;
        /* RIGHT MOVEMENT. */
        case 'D':
        case '6':
        {
          return RIGHT_COMMAND;
        } break;
        /* CENTRE THE SQUARE. */
        case 'C':
        case '5':
        {
          return CENTRE_COMMAND;
        } break;
        /* EXIT PROGRAMME. */
        case 'Q':
        case '0':
        {
          return EXIT_COMMAND;
        } break;
        /* SPECIAL COMMANDS. */
        case '1':
        case '3':
        case '7':
        case '9':
        {
          goto label_advanced_movement;
        } break;
        /* INVALID INPUT. */
        default:
        {
          /* Unknown command. */
          return UNKNOWN_COMMAND;
        } break;
      }
    }
    else if (ADVANCED_MOVEMENT == cmd_length)
    {
      label_advanced_movement:
      /* UPWARD LEFT MOVEMENT. */
      if (
           (RET_OK == strcmp ("WA", client_cmd)) ||
           (RET_OK == strcmp ("AW", client_cmd)) ||
           (RET_OK == strcmp ("7",  client_cmd))
         )
      {
        return UP_LEFT_COMMAND;
      }
      else
      {
        /* Do nothing. */
      }
      /* UPWARD RIGHT MOVEMENT. */
      if (
           (RET_OK == strcmp ("WD", client_cmd)) ||
           (RET_OK == strcmp ("DW", client_cmd)) ||
           (RET_OK == strcmp ("9",  client_cmd))
         )
      {
        return UP_RIGHT_COMMAND;
      }
      else
      {
        /* Do nothing. */
      }
      /* DOWNWARD LEFT MOVEMENT. */
      if (
           (RET_OK == strcmp ("SA", client_cmd)) ||
           (RET_OK == strcmp ("AS", client_cmd)) ||
           (RET_OK == strcmp ("1",  client_cmd))
         )
      {
        return DOWN_LEFT_COMMAND;
      }
      else
      {
        /* Do nothing. */
      }
      /* DOWNWARD RIGHT MOVEMENT. */
      if (
           (RET_OK == strcmp ("SD", client_cmd)) ||
           (RET_OK == strcmp ("DS", client_cmd)) ||
           (RET_OK == strcmp ("3",  client_cmd))
         )
      {
        return DOWN_RIGHT_COMMAND;
      }
      else
      {
        /* Do nothing. */
      }
    }
    else
    {
      /* Unreachable. */
    }
  }
}
