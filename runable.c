#include "socket/include/socket.h"
#include "parser/include/compiler.h"
#include "draw-func/include/draw.h"

int main(void)
{

  instantialise_scene();

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
