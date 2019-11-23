#if !defined(__PLATFORM__)
#define __PLATFORM__

#include <stdint.h>

#define boolean     uint8_t
#define uint8       uint8_t
#define uint16      uint16_t
#define uint32      uint32_t
#define string      char*
#define stream      char**
#define socket_type uint8_t
#define id          uint8_t

#define FALSE      0x00u
#define TRUE       0x01u

#define RET_OK     0x00u
#define RET_NOK    0x01u

#define ERROR      0x00u
#define VALID      0x01u

#define DECLARE_COMMAND_LENGTH 0x02u

#endif /* __PLATFORM__ */
