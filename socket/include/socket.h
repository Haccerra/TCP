#if !defined(__SOCKET__)
#define __SOCKET__

#include "../../platform/platform.h"
#include "../../parser/include/compiler.h"
#include "../../parser/include/interpreter.h"
#include "../../draw-func/include/draw.h"
#include "../../libraries/include/drawlib.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define __MAX__NUMBER__OF__CLIENTS__AVAILABLE__TO__CONNECT__ 0x04u

#define __BUFFER__SIZE__ 256

#define CONNECTION_DOMAIN   AF_INET         /* IPv4 */
#define CONNECTION_TYPE     SOCK_STREAM     /* TCP */
#define CONNECTION_PROTOCOL 0x00u
#define CONNECTION_PORT_STD 9001

#define LET_SERVER_DECIDED_ON_CLIENT_ID 0x00u
#define CONNECT_WITH_ID_1               0x01u
#define CONNECT_WITH_ID_2               0x02u
#define CONNECT_WITH_ID_3               0x03u
#define CONNECT_WITH_ID_4               0x04u

#define DO_NOT_USE_ANY_FLAGS            0x00u
#define CLIENT_INACTIVE                 0x00u

#define PROTOCOL_0                      0x00u

struct user_input
{
  socket_type socket;                 /* Server or client. */
  uint8       type;                   /* IPv4 or IPv6. */
  string      IP;                     /* IP of server. IP to connect to (for clients). */
  int         PORT;                   /* PORT of server. PORT to connect to (for clients). */
  union
  {
    uint8 _connect_with_id;           /* Connect to a server with ID (1 - 4). */
    uint8 _max_num_of_clients;        /* Maximum numbers of clients for server application */
  };
};

extern struct user_input parsed_user_commands;

void setup_server(void);
void setup_client(void);

#endif /* __SOCKET__ */
