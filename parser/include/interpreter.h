#if !defined(__INTERPRETER__)
#define __INTERPRETER__

#include <string.h>

#include "../../platform/platform.h"

#define EXIT_COMMAND             0x00
#define UNKNOWN_COMMAND         -0x01
#define UP_COMMAND               0x08
#define DOWN_COMMAND             0x02
#define LEFT_COMMAND             0x04
#define RIGHT_COMMAND            0x06
#define CENTRE_COMMAND           0x05
#define DOWN_LEFT_COMMAND        0x01
#define DOWN_RIGHT_COMMAND       0x03
#define UP_LEFT_COMMAND          0x07
#define UP_RIGHT_COMMAND         0x09
#define DESTROY_ON_DISCONNECTION 0x0A
#define REPEAT_COMMAND           0x0B

#define ALLOWED_LENGTH     0x02u
#define BASIC_MOVEMENT     0x01u
#define ADVANCED_MOVEMENT  0x02u



command command_interpreter(string);



#endif /* __INTERPRETER__ */
