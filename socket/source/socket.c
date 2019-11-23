#include "../include/socket.h"

extern struct user_input parsed_user_commands;

void setup_server()
{
  char server_message[256] = "Congrats! You have reached the server.";
  struct sockaddr_in server;

  int server_socket = socket (AF_INET, SOCK_STREAM, 0);

  server.sin_family      = AF_INET;
  server.sin_port        = htons (9002);
  server.sin_addr.s_addr = INADDR_ANY;

  bind (server_socket, (struct sockaddr*)&server, sizeof (server));

  listen (server_socket, 4);

  int client_socket = accept (server_socket, NULL, NULL);

  send (client_socket, server_message, sizeof (server_message), 0);

  close (server_socket);
}


void setup_client()
{
  int client_socket;
  struct sockaddr_in client;

  client_socket = socket (AF_INET, SOCK_STREAM, 0);

  client.sin_family      = AF_INET;
  client.sin_port        = htons (9002);
  client.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect (client_socket, (struct sockaddr*)&client, sizeof (client));

  if (-1 == connection_status)
  {
    printf ("Error in making connection with a server.");
  }
  else
  {
    /* OKAY. */
  }

  char server_response[256];
  recv (client_socket, &server_response, sizeof (server_response), 0);

  printf ("Server sent %s.\n", server_response);

  close (client_socket);

}
