#ifndef _MBI_5252_H
#define _MBI_5252_H
#include <stdint.h>

int32_t mbi5252_init(uint32_t chips, uint32_t scan_lines, uint32_t channels);

int32_t mbi5252_send_frame(uint16_t framebuf[16][16][48], uint32_t len);

#endif // _MBI_5252_H
