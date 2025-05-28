#ifndef _MBI_DRIVER_H
#define _MBI_DRIVER_H
#include <stdint.h>

int32_t mbi_init(void);
int32_t mbi_data_latch(uint16_t *buf, uint32_t len);
int32_t mbi_vsync(void);
int32_t mbi_gclk(int32_t num);

#endif // _MBI_DRIVER_H
