#include "socket/include/socket.h"
//#include "platform/platform.h"
#include "parser/include/compiler.h"

int main(void)
{

  if (__SERVER__ == parsed_user_commands.socket)
  {
    setup_server();
  }
  else if (__CLIENT__ == parsed_user_commands.socket)
  {
    setup_client();
  }
  else
  {
    /* Unreachable. */
  }
  return 0;
}
