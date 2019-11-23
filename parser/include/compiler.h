#if !defined(__COMPILER__)
#define __COMPILER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../platform/platform.h"
#include "../../socket/include/socket.h"

#define __MAX__NUMBER__OF__ARGUMENTS__FOR__CLIENT__APPLICATION__    0x05u
#define __MAX__NUMBER__OF__ARGUMENTS__FOR__SERVER__APPLICATION__    0x04u

#define _CON_TYPE_  0x01u
#define _IP_        0x02u
#define _PORT_      0x03u
#define _USE_ID_    0x04u

#define __UNDEFN__  0x00u
#define __SERVER__  0x01u
#define __CLIENT__  0x02u

void __compiler_parser(int argc, stream argv) __attribute__ ((constructor));






#endif /* __COMPILER__ */
