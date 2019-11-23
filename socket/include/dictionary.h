#if !defined(__DICTIONARY__)
#define __DICTIONARY__

#include <stdint.h>

#define boolean     uint8_t
#define uint8       uint8_t
#define uint16      uint16_t
#define uint32      uint32_t
#define string      char*
#define stream      char**
#define socket_type uint8_t

#define FALSE   0x00u
#define TRUE    0x01u

#define CLIENT  0x00u
#define SERVER  0x01u
#define INVALID 0x02u

#define _SERVER_ARGS_ 0x04u
#define _CLIENT_ARGS_ 0x04u

#define RET_OK  0x00u
#define RET_NOK 0x01u

#define _MAIN_SUCCESSFULLY_EXECUTED_ 0x00u
#define _MAIN_FAILED_IN_EXECUTION_   0x01u

#define _TYPE_ 0x01u
#define _IP_   0x02u
#define _PORT_ 0x03u

#define LISTEN_FAILED 0x00
#define ACCEPT_FAILED 0x00

#define _CMD_MAX_SIZE_ 10
#define _MAX_NUMBER_OF_CLIENTS_ALLOWED_TO_CONNECT_AT_THE_SAME_TIME_ 0x04

#endif /* __DICTIONARY__ */
