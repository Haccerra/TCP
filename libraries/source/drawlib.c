#include "../include/drawlib.h"

#define MAX_PKT_SIZE 640*480*4

extern unsigned int image_matrix[__SCREEN__BOUNDS__Y__][__SCREEN__BOUNDS__X__];

/* #define __HOME__ */

#if !defined(__HOME__)
void update_graphics()
{
  int fd;
  int *p;
  fd = open("/dev/vga_dma", O_RDWR|O_NDELAY);
  if (fd < 0)
  {
    printf("Cannot open /dev/vga for write\n");
    exit (ERROR);
  }
  p=(int*)mmap(0, MAX_PKT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  memcpy(p, image_matrix, MAX_PKT_SIZE);
  munmap(p, MAX_PKT_SIZE);
  close(fd);
  if (fd < 0)
  {
    printf("Cannot close /dev/vga for write\n");
    exit (ERROR);
  }
}
#else
void update_graphics()
{

}
#endif
