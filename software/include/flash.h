#ifndef __FLASH_H
#define __FLASH_H

#include <stdint.h>
#include <stddef.h>

void flash_init(void);
bool flash_read(uint32_t addr, void *data, size_t len);
bool flash_write(uint32_t addr, void *data, size_t len);

#endif
