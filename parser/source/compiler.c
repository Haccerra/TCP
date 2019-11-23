#include "../include/compiler.h"

struct user_input parsed_user_commands =
{
  .socket = __UNDEFN__,
  .type   = CONNECTION_DOMAIN,
  .IP     = "",
  .PORT   = CONNECTION_PORT_STD,
};

static void    error_message_output_client_application(void);
static void    error_message_output_server_application(void);
static boolean evaluate_format_of_user_input_commands(string, string);
static uint8   search_for_equation_sign_position(string argument);
static boolean search_for_minusminus_sign_existance(string argument);
static boolean check_default_values(string, string);

static boolean verify_correct_number_format_for_port_argument(string);
static id verify_correct_message_format_for_use_id_argument_and_return_valid_number(string);
static boolean is_digit(char string2number);

static string  skimfromcmd(string);
static uint32  num2pow(uint32, uint32);
static uint32  convert_s2ui8(string);

void __compiler_parser(int argc, stream argv)
{
  if (
       (__MAX__NUMBER__OF__ARGUMENTS__FOR__CLIENT__APPLICATION__ == argc) ||
       (__MAX__NUMBER__OF__ARGUMENTS__FOR__SERVER__APPLICATION__ == argc)
     )
  {
    if (RET_OK == strcmp ("--connect_as=server", argv[_CON_TYPE_]))
    {
      if (__MAX__NUMBER__OF__ARGUMENTS__FOR__SERVER__APPLICATION__ == argc)
      {
        boolean ret_val[2];
        ret_val[0] = evaluate_format_of_user_input_commands("IP", argv[_IP_]);
        ret_val[1] = evaluate_format_of_user_input_commands("PORT", argv[_PORT_]);

        if (
             (FALSE != (ret_val[0] & ret_val[1]))
           )
        {
          /* All is okay. */
        }
        else
        {
          /* Not everything is okay. Abort! */
          exit (0);
        }

        /* Check for default values on PORT. */
        boolean port_default_value = check_default_values("default", argv[_PORT_]);

        if (FALSE != port_default_value)
        {

        }
        else
        {
          /* Not a default value. User specified. */

          /* Verify if a number is specified. */
          boolean isOK = verify_correct_number_format_for_port_argument(argv[_PORT_]);

          if (FALSE != isOK)
          {
            string port_arg_val = skimfromcmd(argv[_PORT_]);
            parsed_user_commands.PORT   = (int)convert_s2ui8(port_arg_val);
          }
          else
          {
            /* PORT not specified in digit number nor is it default. Error. */
            fprintf (stderr, "ERR::PORT argument not properly specified. It must be a number.\n");
            exit (0);
          }
        }

        parsed_user_commands.socket = __SERVER__;
        parsed_user_commands.IP     = skimfromcmd(argv[_IP_]);
        parsed_user_commands._max_num_of_clients = __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__;
      }
      else
      {
        /* Inappropriate number of arguments for server application. */
        fprintf (stderr, "ERR::Invalid number of arguments passed!\n");
        error_message_output_server_application();

        return;
      }
    }
    else if (RET_OK == strcmp ("--connect_as=client", argv[_CON_TYPE_]))
    {
      if (__MAX__NUMBER__OF__ARGUMENTS__FOR__CLIENT__APPLICATION__ == argc)
      {
        boolean ret_val[3];
        ret_val[0] = evaluate_format_of_user_input_commands("IP",         argv[_IP_]);
        ret_val[1] = evaluate_format_of_user_input_commands("PORT",     argv[_PORT_]);
        ret_val[2] = evaluate_format_of_user_input_commands("USE_ID", argv[_USE_ID_]);

        if (
             (FALSE != ((ret_val[0] & ret_val[1]) & ret_val[2]))
           )
        {
          /* All is okay. */
        }
        else
        {
          /* Not everything is okay. Abort! */
          exit (0);
        }

        /* Check for default values on PORT and USE_ID. */
        boolean port_default_value   = check_default_values("default",     argv[_PORT_]);
        boolean use_id_default_value = check_default_values("automatic", argv[_USE_ID_]);

        if (FALSE != port_default_value)
        {

        }
        else
        {
          /* Not a default value. User specified. */

          /* Verify if a number is specified. */
          boolean isOK = verify_correct_number_format_for_port_argument(argv[_PORT_]);

          if (FALSE != isOK)
          {
            string port_arg_val = skimfromcmd(argv[_PORT_]);
            parsed_user_commands.PORT   = (int)convert_s2ui8(port_arg_val);
          }
          else
          {
            /* PORT not specified in digit number, nor is it a default value. Error. */
            fprintf (stderr, "ERR::PORT argument not properly specified. It must be a number.\n");
            exit (0);
          }
        }

        if (FALSE != use_id_default_value)
        {
          parsed_user_commands._connect_with_id = LET_SERVER_DECIDED_ON_CLIENT_ID;
        }
        else
        {
          /* User defined value. */
          id connect_with_id = verify_correct_message_format_for_use_id_argument_and_return_valid_number(argv[_USE_ID_]);

          if (ERROR != connect_with_id)
          {
            parsed_user_commands._connect_with_id = connect_with_id;
          }
          else
          {
            /* Error occured. Abort. */
            exit (0);
          }
        }

        parsed_user_commands.socket = __CLIENT__;
        parsed_user_commands.IP     = skimfromcmd(argv[_IP_]);
      }
      else
      {
        /* Inappropriate number of arguments for client application. */
        fprintf (stderr, "ERR::Invalid number of arguments passed!\n");
        error_message_output_client_application();

        return;
      }
    }
  }
  else
  {
    /* Inappropriate length of arguments passed to programme call. */
    fprintf (stderr, "ERR::Invalid number of arguments passed!\n");
    error_message_output_server_application();
    error_message_output_client_application();

    return;
  }
}

static void error_message_output_client_application()
{
  fprintf (stderr, "INFO::For client application please use following:\n");
  fprintf (stderr, "\t--connect_as=client\n");
  fprintf (stderr, "\t--IP=\"server IP address to connect to\"\n");
  fprintf (stderr, "\t--PORT=default or --PORT=\"port number of server application to connect to\"\n");
  fprintf (stderr, "\t--USE_ID=x where x is 1, 2, 3 or 4. Otherwise, use --USE_ID=automatic for server choice.\n\n");
}

static void error_message_output_server_application()
{
  fprintf (stderr, "INFO::For server application please use following:\n");
  fprintf (stderr, "\t--connect_as=server\n");
  fprintf (stderr, "\t--IP=\"server IP address\"\n");
  fprintf (stderr, "\t--PORT=default or --PORT=\"port number for server application to use\"\n\n");
}

static boolean evaluate_format_of_user_input_commands(string cmd_type, string user_val)
{
  if (NULL != user_val)
  {
    uint8 equal_sign_position = search_for_equation_sign_position(user_val);
    if (ERROR != equal_sign_position)
    {
      boolean minusminus_found = search_for_minusminus_sign_existance(user_val);
      if (FALSE != minusminus_found)
      {
        string extract_command = (string)calloc ((equal_sign_position-DECLARE_COMMAND_LENGTH), sizeof (char));
        if (NULL != extract_command)
        {
          for (uint8 i = 0x00u; equal_sign_position > i; i++)
          {
            extract_command[i] = user_val[i+DECLARE_COMMAND_LENGTH];
          }
          extract_command[equal_sign_position-DECLARE_COMMAND_LENGTH] = '\0';    /* Place string delimiter. */

          if (RET_OK == strcmp (cmd_type, extract_command))
          {
            return TRUE;
          }
          else
          {
            return FALSE;
          }
        }
        else
        {
          /* Starting command argument not found. */
          fprintf (stderr, "ERROR::Starting command argument -- not found.\n");
          return FALSE;
        }
      }
      else
      {
        /* Allocation failed. */
        fprintf (stderr, "ERROR::Not enough space for programme to operate. Execution stoped.\n");
        return FALSE;
      }
    }
    else
    {
      /* Wrong syntax. */
      fprintf (stderr, "ERROR::Wrong syntax. Missing '=' in %s command.\n", cmd_type);
      return FALSE;
    }
  }
  else
  {
    /* Inappropriate call of the function. */
    fprintf (stderr, "FATAL::Programming error. NULL passed as %s command.\n", cmd_type);
    return FALSE;
  }
}

static uint8 search_for_equation_sign_position(string argument)
{
  boolean is_there_equation_sign = FALSE;
  uint8 i = 0x00u;

  for ( ; strlen (argument) > i; i++)
  {
    if ('=' == argument[i])
    {
      is_there_equation_sign = TRUE;
      break;
    }
    else
    {
      /* Do nothing. */
    }
  }

  if (FALSE != is_there_equation_sign)
  {
    return i; /* position of the '=' argument. */
  }
  else
  {
    return ERROR;
  }

  return ERROR; /* Unreachable. */
}

static boolean search_for_minusminus_sign_existance(string argument)
{
  boolean was_minus_found = TRUE;   /* Assume that command is valid before checking. */
  for (uint8 i = 0x00u; DECLARE_COMMAND_LENGTH > i; i++)
  {
    if ('-' == argument[i])
    {
      continue;
    }
    else
    {
      /* Error. Sign not found. */
      was_minus_found = FALSE;
      break;
    }
  }

  return was_minus_found;
}

static boolean check_default_values(string default_val, string arg)
{
  uint8 argument_length     = strlen (arg);
  uint8 equal_sign_position = search_for_equation_sign_position(arg);

  /* Already handled whether = exists in command. */
  string argument_extract = (string)calloc ((argument_length-equal_sign_position), sizeof (char));
  for (uint8 i = equal_sign_position+1; argument_length > i; i++)
  {
    argument_extract[i-equal_sign_position-1] = arg[i];
  }
  argument_extract[argument_length-equal_sign_position] = '\0';

  if (RET_OK == strcmp(default_val, argument_extract))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }

  return FALSE; /* Unreachable. */
}


static boolean verify_correct_number_format_for_port_argument(string port_arg)
{
  uint8 equal_sign_position   = search_for_equation_sign_position(port_arg);
  uint8 length_of_an_argument = strlen (port_arg);

  /* Assume that --PORT= is already in correct format as it was processed before call of this function. */
  for (uint8 i = equal_sign_position+1; length_of_an_argument > i; i++)
  {
    boolean result = is_digit(port_arg[i]);

    if (FALSE != result)
    {
      continue;
    }
    else
    {
      /* Not a digit. */
      return FALSE;
    }
  }

  return TRUE;
}

static id verify_correct_message_format_for_use_id_argument_and_return_valid_number(string use_id_arg)
{
  uint8 equal_sign_position   = search_for_equation_sign_position(use_id_arg);
  uint8 length_of_an_argument = strlen (use_id_arg);

  if (DECLARE_COMMAND_LENGTH+equal_sign_position == length_of_an_argument)
  {
    /* Okay. Only one digit used as an argument. */
    switch (use_id_arg[length_of_an_argument-1])
    {
      case '1':
      {
        return CONNECT_WITH_ID_1;
      } break;
      case '2':
      {
        return CONNECT_WITH_ID_2;
      } break;
      case '3':
      {
        return CONNECT_WITH_ID_3;
      } break;
      case '4':
      {
        return CONNECT_WITH_ID_4;
      } break;
      default:
      {
        goto label_invalid_argument;
      } break;
    }
  }
  else
  {
    label_invalid_argument:
    /* Argument for USE_ID can only be a number "1, 2, 3 or 4." if not a default value. */
    fprintf (stderr, "ERR::USE_ID argument not correct. Must be a number between 1-4 or use automatic keyword.\n");
    return ERROR;
  }

  return ERROR; /* Not reachable. */
}

static boolean is_digit(char string2number)
{
  if (
       ('0' <= string2number) &&
       ('9' >= string2number)
     )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }

  return FALSE; /* Unreachable. */
}

static string  skimfromcmd(string user_cmd)
{
  uint8 equal_sign_position   = search_for_equation_sign_position(user_cmd);
  uint8 length_of_an_argument = strlen (user_cmd);

  string skimval = (string)calloc (length_of_an_argument-equal_sign_position, sizeof (char));
  for (uint8 i = equal_sign_position+1; length_of_an_argument > i; i++)
  {
    skimval[i-equal_sign_position-1] = user_cmd[i];
  }
  skimval[length_of_an_argument-equal_sign_position] = '\0';

  return skimval;
}

static uint32  num2pow(uint32 num_1, uint32 num_2)
{
  uint32 result = num_1;
  for (uint32 i = 0x00u; num_2 > i; i++)
  {
    result *= num_1;
  }

  return result;
}

static uint32   convert_s2ui8(string string2number)
{
  uint8* number = (uint8*)calloc(strlen(string2number), sizeof (uint8));
  if (NULL != number)
  {
    for (uint8 i = 0x00u; strlen (string2number) > i; i++)
    {
      switch (string2number[i])
      {
        case '0':
        {
          number[i] = 0;
        } break;
        case '1':
        {
          number[i] = 1;
        } break;
        case '2':
        {
          number[i] = 2;
        } break;
        case '3':
        {
          number[i] = 3;
        } break;
        case '4':
        {
          number[i] = 4;
        } break;
        case '5':
        {
          number[i] = 5;
        } break;
        case '6':
        {
          number[i] = 6;
        } break;
        case '7':
        {
          number[i] = 7;
        } break;
        case '8':
        {
          number[i] = 8;
        } break;
        case '9':
        {
          number[i] = 9;
        } break;
        default:
        {
          /* Impossible case. */
        } break;
      }
    }
  }
  else
  {
    /* Error. Not enough space. */
    fprintf (stderr, "ERR::Not enough space. Allocation failed.\n");
    exit (0);
  }

  uint8  numbersnumber = strlen (string2number)-2;
  uint32 multiplicator = num2pow(10, numbersnumber);

  uint32 converted_number = number[strlen (string2number)-1];
  for (uint8 i = 0x00u; strlen (string2number)-1 > i; i++)
  {
    converted_number += number[i]*multiplicator;
    multiplicator = num2pow(10, --numbersnumber);
  }

  return converted_number;
}
