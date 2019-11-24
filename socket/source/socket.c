#include "../include/socket.h"

extern struct user_input parsed_user_commands;

char command_from_client[__BUFFER__SIZE__];

void setup_server()
{
  struct sockaddr_in server;

  int client_socket[__MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__] =
  {
    CLIENT_INACTIVE,
    CLIENT_INACTIVE,
    CLIENT_INACTIVE,
    CLIENT_INACTIVE
  };

  int server_socket = socket (AF_INET, SOCK_STREAM, PROTOCOL_0);

  int multiple_connections_set_up = setsockopt (server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof (int));
  if ((int)ERROR > multiple_connections_set_up)
  {
    /* (int)ERROR occured. */
    fprintf (stderr, "ERR::Setting up multiple connections for the server not possible.\n");
    exit ((int)ERROR);
  }
  else
  {
    /* All is okay. Continue. */
  }

  server.sin_family      = AF_INET;
  server.sin_port        = htons (parsed_user_commands.PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  int bind_socket = bind (server_socket, (struct sockaddr*)&server, sizeof (server));
  if ((int)ERROR > bind_socket)
  {
    /* (int)ERROR occured. */
    fprintf (stderr, "ERR::Binding server to IP=%s PORT=%d not possible.\n", parsed_user_commands.IP, parsed_user_commands.PORT);
    exit ((int)ERROR);
  }
  else
  {
    /* All is okay. Continue. */
  }

  int listen_socket = listen (server_socket, __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__);
  if ((int)ERROR > listen_socket)
  {
    /* (int)ERROR occured. */
    fprintf (stderr, "ERR::Listening to %d clients not possible.\n", __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__);
    exit ((int)ERROR);
  }
  else
  {
    /* All is okay. Continue. */
  }

  printf ("ECHO::Server is waiting for connections.\n\n");

  fd_set read_file_descriptor_on_change;
  for (;;)
  {
      int sizeofserver = sizeof (server);

      FD_ZERO (&read_file_descriptor_on_change);                      /* Clear the socket from junk. */
      FD_SET  (server_socket, &read_file_descriptor_on_change);       /* Add server socket to file descriptor. */

      int highest_descriptor_value = server_socket;

      for (uint8 i = 0x00u; __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__ > i; i++)
      {
        int client_descriptor = client_socket[i];
        if ((int)ERROR < client_descriptor)
        {
          FD_SET (client_descriptor, &read_file_descriptor_on_change);
        }
        else
        {
          /* Do nothing. */
        }
        /* Reprogramme highest descriptor value. */
        if (highest_descriptor_value < client_descriptor)
        {
          highest_descriptor_value = client_descriptor;
        }
        else
        {
          /* Do nothing. */
        }
      }

      /* INFO::Potentional Dead Loop. Infinite waiting time. */
      int wait4activity = select (highest_descriptor_value+1, &read_file_descriptor_on_change, NULL, NULL, NULL);

      if (
           ((int)ERROR > wait4activity) &&
           (EINTR != errno)
         )
      {
        fprintf (stderr, "ERR::Programme failed in connecting with a client.\n");
      }
      else
      {
        /* All is good, all is bright! */
      }

      /* Check whether server is active and new client is to connect. */
      boolean verify_server_did_not_disconnect = FD_ISSET (server_socket, &read_file_descriptor_on_change);
      int accept_client = 0x00;
      if (FALSE != verify_server_did_not_disconnect)
      {
        /* Great! */
        accept_client = accept (server_socket, (struct sockaddr*)&server, (socklen_t*)&sizeofserver);
        if ((int)ERROR > accept_client)
        {
          /* (int)ERROR occured. */
          fprintf (stderr, "ERR::Client could not be accepted. Server breached. Abort.\n");
          exit ((int)ERROR);
        }
        printf ("ECHO::New connection received from IP=%s, PORT=%d\n", inet_ntoa (server.sin_addr), ntohs (server.sin_port));

        char server_response[__BUFFER__SIZE__] = "You have successfully connected.\nPlease use WASD to move rectangle or Q to abort the connection.\n\n";

        int send_response = send (accept_client, server_response, strlen (server_response), DO_NOT_USE_ANY_FLAGS);
        if (strlen (server_response) != send_response)
        {
          /* ERROR occured. */
          fprintf (stderr, "ERR::Something happened with the data transfer. Abort.\n");
          exit ((int)ERROR);
        }
        else
        {
          /* No problem detected. */
        }

        /* Add a new client to the list of clients. */
        for (uint8 i = 0x00u; __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__ > i; i++)
        {
          if (CLIENT_INACTIVE == client_socket[i])
          {
            client_socket[i] = accept_client;
            break;
          }
        }
      }
      else
      {
        /* We lost connection with the client. */
      }

      /* Old client sends messages. Parse the info. */
      for (uint8 i = 0x00u; __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__ > i; i++)
      {
        int isset = FD_ISSET (client_socket[i], &read_file_descriptor_on_change);
        if (FALSE != isset)
        {
          /* Read the message. */
          int is_connected = read (client_socket[i], &command_from_client, __BUFFER__SIZE__);
          if ((int)ERROR == is_connected)
          {
            /* Client is no longer connected. */
            getpeername (client_socket[i], (struct sockaddr*)&server, (socklen_t*)&sizeofserver);

            printf ("ECHO::Client from IP=%s PORT=%d disconnected.\n", inet_ntoa (server.sin_addr), ntohs (server.sin_port));

            client_socket[i] = CLIENT_INACTIVE;
          }
          else
          {
            /* Message received successfully. Send for interpolation. */
            command_from_client[is_connected] = '\0';   /* is_connected also contains number of characters send by client. */

            command user_cmd = command_interpreter(command_from_client);
            if (UNKNOWN_COMMAND != user_cmd)
            {
              /* All is okay. */
            }
            else
            {
              /* Invalid argument. */
            }
          }
        }
        else
        {
          /* Ignore. Nothing of relevance occured. */
        }
      }
  }
}


void setup_client()
{
  int client_socket;
  struct sockaddr_in client;

  client_socket = socket (AF_INET, SOCK_STREAM, PROTOCOL_0);

  client.sin_family      = AF_INET;
  client.sin_port        = htons (parsed_user_commands.PORT);
  client.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect (client_socket, (struct sockaddr*)&client, sizeof (client));
  if ((int)ERROR > connection_status)
  {
    fprintf (stderr, "ERR::Server not connected. Aborting.\n");
    exit ((int)ERROR);
  }
  else
  {
    /* OKAY. */
  }

  char server_response[__BUFFER__SIZE__];
  int receive_successful = recv (client_socket, &server_response, sizeof (server_response), PROTOCOL_0);

  if ((int)ERROR < receive_successful)
  {
    /* Okay. Print message. */
    server_response[receive_successful] = '\0';       /* Add null-terminating delimiter for string. */
    printf ("%s", server_response);
  }
  else
  {
    /* ERROR. Abort. */
    fprintf (stderr, "ERR::Could not receive valid data from server. Disconnecting...\n");
    exit ((int)ERROR);
  }

  /* Send information. */
  for (;;)
  {
    char client2server[__BUFFER__SIZE__];

    (void)scanf ("%s", client2server);

    int loopback_data = send (client_socket, client2server, strlen (client2server), DO_NOT_USE_ANY_FLAGS);
    if (loopback_data != strlen (client2server))
    {
      /* ERROR occured. */
      fprintf (stderr, "ERR::Transmission data from the server failed. Aborting client connection.\n");
      exit ((int)ERROR);
    }
    else
    {
      /* All is good. */
      command is_command_okay = command_interpreter(client2server);
      if (UNKNOWN_COMMAND == is_command_okay)
      {
        printf ("ECHO::Invalid command!\n");
        printf ("ECHO::Please use following:\n");
        printf ("\t\t::W(8) S(2) A(4) D(6) or;\n");
        printf ("\t\t::1 3 7 9 for diagonal movement of the square or;\n");
        printf ("\t\t::C or 5 to centre the square or;\n");
        printf ("\t\t::Q or 0 to close the connection.\n\n");
      }
      else
      {
        if (
             (RET_OK == strcmp ("Q", client2server)) ||
             (RET_OK == strcmp ("0", client2server))
           )
        {
          /* Stop the programme. */
          close (client_socket);
          exit (VALID);
          break;
        }
        else
        {
          /* Do nothing. */
        }
      }
    }
  }

  close (client_socket);  /* Unreachable. */
}
