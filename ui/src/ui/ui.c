#if defined(EEZ_FOR_LVGL)
#include <eez/core/vars.h>
#endif

#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"

// ASSETS DEFINITION
const uint8_t assets[2580] = {
    0x7E, 0x65, 0x65, 0x7A, 0x03, 0x00, 0x06, 0x00, 0x94, 0x21, 0x00, 0x00, 0x6E, 0x24, 0x00, 0x00,
    0x00, 0x24, 0x00, 0x01, 0x00, 0x17, 0x20, 0x0C, 0x00, 0x53, 0xE0, 0x01, 0x40, 0x01, 0x01, 0x28,
    0x00, 0x13, 0x02, 0x1C, 0x00, 0xD7, 0x05, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x0D, 0x00,
    0x00, 0x00, 0x08, 0x2D, 0x00, 0x11, 0x1C, 0x06, 0x00, 0x20, 0xFF, 0xFF, 0x13, 0x00, 0xF3, 0x02,
    0x44, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00,
    0xD4, 0x40, 0x00, 0x00, 0x08, 0x00, 0x57, 0x22, 0x00, 0x00, 0x00, 0xD0, 0x64, 0x00, 0x6E, 0x09,
    0x00, 0x00, 0x00, 0xF4, 0x1F, 0x88, 0x00, 0x66, 0x0F, 0x00, 0x00, 0x00, 0x30, 0x01, 0x10, 0x00,
    0x6E, 0x04, 0x00, 0x00, 0x00, 0xD8, 0x1F, 0x28, 0x00, 0x10, 0x17, 0x70, 0x00, 0x0B, 0x28, 0x00,
    0x1F, 0xB4, 0x50, 0x00, 0x04, 0x1B, 0x78, 0x28, 0x00, 0x2E, 0x90, 0x1F, 0x28, 0x00, 0x10, 0x0E,
    0xB8, 0x00, 0x07, 0x28, 0x00, 0x6E, 0x03, 0x00, 0x00, 0x00, 0x6C, 0x1F, 0x28, 0x00, 0xF2, 0x2F,
    0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0xFF, 0xFF, 0x08, 0x42, 0x94, 0x01, 0x00, 0x00,
    0xB0, 0x01, 0x00, 0x00, 0xCC, 0x01, 0x00, 0x00, 0xE8, 0x01, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00,
    0x20, 0x02, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00, 0x74, 0x02, 0x00, 0x00,
    0x90, 0x02, 0x00, 0x00, 0xAC, 0x02, 0x00, 0x00, 0xC8, 0x02, 0x00, 0x00, 0xE4, 0x02, 0x59, 0x00,
    0xF2, 0x2F, 0x1C, 0x03, 0x00, 0x00, 0x38, 0x03, 0x00, 0x00, 0x54, 0x03, 0x00, 0x00, 0x70, 0x03,
    0x00, 0x00, 0x8C, 0x03, 0x00, 0x00, 0xA8, 0x03, 0x00, 0x00, 0xC4, 0x03, 0x00, 0x00, 0xE0, 0x03,
    0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x34, 0x04, 0x00, 0x00, 0x50, 0x04,
    0x00, 0x00, 0x74, 0x04, 0x00, 0x00, 0x98, 0x04, 0x00, 0x00, 0xBC, 0x04, 0x00, 0x00, 0xE0, 0x04,
    0x8D, 0x01, 0xFA, 0xFF, 0x0C, 0x20, 0x05, 0x00, 0x00, 0x44, 0x05, 0x00, 0x00, 0x68, 0x05, 0x00,
    0x00, 0x88, 0x05, 0x00, 0x00, 0xA4, 0x05, 0x00, 0x00, 0xC0, 0x05, 0x00, 0x00, 0xDC, 0x05, 0x00,
    0x00, 0xF8, 0x05, 0x00, 0x00, 0x14, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x4C, 0x06, 0x00,
    0x00, 0x68, 0x06, 0x00, 0x00, 0x84, 0x06, 0x00, 0x00, 0xA0, 0x06, 0x00, 0x00, 0xBC, 0x06, 0x00,
    0x00, 0xE0, 0x06, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x28, 0x07, 0x00, 0x00, 0x4C, 0x07, 0x00,
    0x00, 0x68, 0x07, 0x00, 0x00, 0x84, 0x07, 0x00, 0x00, 0xA0, 0x07, 0x00, 0x00, 0xBC, 0x07, 0x00,
    0x00, 0xD8, 0x07, 0x00, 0x00, 0xF4, 0x07, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x2C, 0x08, 0x00,
    0x00, 0x48, 0x08, 0x00, 0x00, 0x64, 0x08, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x9C, 0x08, 0x00,
    0x00, 0xB8, 0x08, 0x00, 0x00, 0xD4, 0x08, 0x00, 0x00, 0xF0, 0x08, 0x00, 0x00, 0x0C, 0x09, 0x00,
    0x00, 0x28, 0x09, 0x00, 0x00, 0x44, 0x09, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x84, 0x09, 0x00,
    0x00, 0xA8, 0x09, 0x00, 0x00, 0xCC, 0x09, 0x00, 0x00, 0xF0, 0x09, 0x00, 0x00, 0x0C, 0x0A, 0x00,
    0x00, 0x28, 0x0A, 0x00, 0x00, 0x44, 0x0A, 0x00, 0x00, 0x60, 0x0A, 0x00, 0x00, 0x7C, 0x0A, 0x00,
    0x00, 0x98, 0x0A, 0x00, 0x00, 0xB4, 0x0A, 0x00, 0x00, 0xD0, 0x0A, 0x00, 0x00, 0xEC, 0x0A, 0x00,
    0x00, 0x08, 0x0B, 0x00, 0x00, 0x24, 0x0B, 0x00, 0x00, 0x48, 0x0B, 0x00, 0x00, 0x6C, 0x0B, 0x00,
    0x00, 0x90, 0x0B, 0x00, 0x00, 0xB4, 0x0B, 0x00, 0x00, 0xD0, 0x0B, 0x00, 0x00, 0xEC, 0x0B, 0x00,
    0x00, 0x08, 0x0C, 0x00, 0x00, 0x24, 0x0C, 0x00, 0x00, 0x40, 0x0C, 0x00, 0x00, 0x5C, 0x0C, 0x00,
    0x00, 0x78, 0x0C, 0x00, 0x00, 0x94, 0x0C, 0x00, 0x00, 0xB0, 0x0C, 0x00, 0x00, 0xCC, 0x0C, 0x00,
    0x00, 0xE8, 0x0C, 0x00, 0x00, 0x0C, 0x0D, 0x00, 0x00, 0x30, 0x0D, 0x00, 0x00, 0x20, 0x4E, 0xC4,
    0x01, 0x26, 0x44, 0x0D, 0x10, 0x00, 0x5B, 0xFF, 0xFF, 0x00, 0x00, 0x21, 0x20, 0x00, 0x1B, 0x30,
    0x20, 0x00, 0x1B, 0x22, 0x20, 0x00, 0x1B, 0x1C, 0x20, 0x00, 0x0C, 0x60, 0x00, 0x22, 0x08, 0x0D,
    0xE4, 0x02, 0x2E, 0x0C, 0x0D, 0x40, 0x00, 0x00, 0xAB, 0x01, 0x2E, 0xFC, 0x0C, 0x60, 0x00, 0x08,
    0x20, 0x00, 0x2F, 0xEC, 0x0C, 0x60, 0x00, 0x0B, 0x50, 0xDC, 0x0C, 0x00, 0x00, 0x01, 0x94, 0x03,
    0x1F, 0x0C, 0x40, 0x00, 0x03, 0x1B, 0xCC, 0x40, 0x00, 0x1B, 0x23, 0x40, 0x00, 0x1B, 0xBC, 0x20,
    0x00, 0x1B, 0x24, 0x20, 0x00, 0x1F, 0xA8, 0x80, 0x00, 0x0C, 0x13, 0x94, 0x80, 0x00, 0x1F, 0x98,
    0x80, 0x00, 0x04, 0x1F, 0x84, 0x40, 0x00, 0x0C, 0x13, 0x74, 0x40, 0x00, 0x1F, 0x78, 0x40, 0x00,
    0x04, 0x1F, 0x64, 0x40, 0x00, 0x0C, 0x13, 0x54, 0x40, 0x00, 0x1F, 0x58, 0x40, 0x00, 0x04, 0x1F,
    0x44, 0x40, 0x00, 0x0C, 0x13, 0x34, 0x40, 0x00, 0x1F, 0x38, 0x40, 0x00, 0x04, 0x1F, 0x24, 0x20,
    0x01, 0x0C, 0x1F, 0x14, 0x60, 0x00, 0x0C, 0x2F, 0x00, 0x0C, 0x40, 0x02, 0x0B, 0x2F, 0xEC, 0x0B,
    0x40, 0x00, 0x0B, 0x2F, 0xD8, 0x0B, 0x40, 0x00, 0x0B, 0x1F, 0xC4, 0x40, 0x00, 0x0C, 0x1F, 0xB0,
    0x40, 0x00, 0x0C, 0x1B, 0x9C, 0x20, 0x00, 0x22, 0x06, 0x04, 0x10, 0x01, 0x17, 0x90, 0x18, 0x00,
    0x10, 0x01, 0xC8, 0x01, 0x12, 0x0B, 0x20, 0x00, 0x00, 0x34, 0x00, 0x26, 0x7C, 0x0B, 0x28, 0x00,
    0x1B, 0x7C, 0x28, 0x00, 0x17, 0x70, 0x28, 0x00, 0x17, 0x68, 0x28, 0x00, 0x1B, 0x68, 0x28, 0x00,
    0x13, 0x5C, 0x28, 0x00, 0x10, 0x01, 0xC4, 0x01, 0x07, 0x28, 0x00, 0x1B, 0x4C, 0x28, 0x00, 0x13,
    0x40, 0x28, 0x00, 0x10, 0x04, 0xA4, 0x01, 0x52, 0x0B, 0x00, 0x00, 0xF5, 0x03, 0x18, 0x00, 0x1B,
    0x3C, 0x28, 0x00, 0x23, 0x30, 0x0B, 0xC0, 0x00, 0x16, 0x00, 0x24, 0x00, 0x1B, 0x20, 0x24, 0x00,
    0x13, 0x14, 0x24, 0x00, 0x26, 0x07, 0x00, 0x70, 0x00, 0x1B, 0x04, 0x24, 0x00, 0x26, 0xF8, 0x0A,
    0x98, 0x00, 0x26, 0xF0, 0x0A, 0x28, 0x00, 0x2A, 0xE8, 0x0A, 0x28, 0x00, 0x17, 0xDC, 0x28, 0x00,
    0x26, 0xD4, 0x0A, 0x74, 0x00, 0x1B, 0xCC, 0x28, 0x00, 0x13, 0xC0, 0x28, 0x00, 0x3E, 0x08, 0x00,
    0x00, 0x5C, 0x03, 0x1F, 0x0A, 0x7C, 0x04, 0x0B, 0x2F, 0x94, 0x0A, 0xDC, 0x01, 0x0B, 0x23, 0x80,
    0x0A, 0x9C, 0x01, 0x1F, 0x0A, 0xBC, 0x02, 0x03, 0x1F, 0x70, 0x40, 0x00, 0x0C, 0x13, 0x60, 0x40,
    0x00, 0x1F, 0x64, 0x40, 0x00, 0x04, 0x1F, 0x50, 0x40, 0x00, 0x0C, 0x13, 0x40, 0x40, 0x00, 0x1F,
    0x44, 0x40, 0x00, 0x04, 0x1F, 0x30, 0x40, 0x00, 0x0C, 0x13, 0x20, 0x40, 0x00, 0x1F, 0x24, 0x40,
    0x00, 0x04, 0x1B, 0x10, 0x40, 0x00, 0x1C, 0x25, 0x5C, 0x03, 0x1F, 0x0A, 0xBC, 0x02, 0x03, 0x2A,
    0xF4, 0x09, 0x84, 0x01, 0x26, 0xE8, 0x09, 0x44, 0x02, 0x26, 0xE0, 0x09, 0x28, 0x00, 0x1B, 0xE4,
    0x28, 0x00, 0x26, 0xD8, 0x09, 0xD4, 0x01, 0x17, 0xD0, 0x28, 0x00, 0x1B, 0xC8, 0x28, 0x00, 0x17,
    0xBC, 0x28, 0x00, 0x17, 0xB4, 0x28, 0x00, 0x1B, 0xAC, 0x28, 0x00, 0x17, 0xA0, 0x28, 0x00, 0x2E,
    0x98, 0x09, 0x00, 0x02, 0x2F, 0x88, 0x09, 0x00, 0x02, 0x0B, 0x2F, 0x74, 0x09, 0xC0, 0x01, 0x0C,
    0x13, 0x09, 0xC0, 0x01, 0x1F, 0x09, 0xC0, 0x01, 0x04, 0x1F, 0x09, 0xC0, 0x01, 0x0C, 0x13, 0x09,
    0xC0, 0x01, 0x1F, 0x09, 0xC0, 0x01, 0x04, 0x1F, 0x09, 0xC0, 0x01, 0x0C, 0x13, 0x09, 0xC0, 0x01,
    0x1F, 0x09, 0xC0, 0x01, 0x04, 0x1F, 0x09, 0x1C, 0x05, 0x0C, 0x13, 0x09, 0x84, 0x03, 0x0F, 0x40,
    0x00, 0x04, 0x2F, 0xF0, 0x08, 0x7C, 0x05, 0x0B, 0x2F, 0xE0, 0x08, 0xDC, 0x04, 0x0B, 0x1B, 0xCC,
    0x20, 0x00, 0x1B, 0x26, 0x20, 0x00, 0x1F, 0xB8, 0x60, 0x00, 0x0C, 0x1F, 0xA4, 0x60, 0x00, 0x0C,
    0x1B, 0x90, 0x20, 0x00, 0x1B, 0x27, 0x20, 0x00, 0x1F, 0x7C, 0x60, 0x00, 0x0C, 0x1F, 0x68, 0x60,
    0x00, 0x0C, 0x1F, 0x54, 0xC0, 0x00, 0x0C, 0x2F, 0x40, 0x08, 0x00, 0x03, 0x03, 0x2A, 0x34, 0x08,
    0x88, 0x02, 0x26, 0x28, 0x08, 0x00, 0x03, 0x26, 0x20, 0x08, 0x28, 0x00, 0x1B, 0x24, 0x28, 0x00,
    0x26, 0x18, 0x08, 0xB0, 0x02, 0x17, 0x10, 0x28, 0x00, 0x1B, 0x08, 0x28, 0x00, 0x26, 0xFC, 0x07,
    0x28, 0x00, 0x26, 0xF4, 0x07, 0x28, 0x00, 0x2A, 0xEC, 0x07, 0x28, 0x00, 0x17, 0xE0, 0x28, 0x00,
    0x10, 0xD8, 0x50, 0x0A, 0x0B, 0xC0, 0x00, 0x2F, 0xC8, 0x07, 0x00, 0x03, 0x0B, 0x2F, 0xB4, 0x07,
    0x40, 0x01, 0x0B, 0x2F, 0xA0, 0x07, 0x60, 0x02, 0x0B, 0x23, 0x8C, 0x07, 0xCC, 0x06, 0x1F, 0x07,
    0x60, 0x02, 0x03, 0x1F, 0x7C, 0x40, 0x00, 0x0C, 0x23, 0x6C, 0x07, 0xD4, 0x06, 0x0F, 0x40, 0x00,
    0x04, 0x1F, 0x5C, 0x40, 0x00, 0x0C, 0x13, 0x4C, 0x40, 0x00, 0x1F, 0x50, 0x40, 0x00, 0x04, 0x1F,
    0x3C, 0x40, 0x00, 0x0C, 0x23, 0x2C, 0x07, 0xDC, 0x06, 0x0F, 0x40, 0x00, 0x04, 0x2F, 0x1C, 0x07,
    0x00, 0x02, 0x03, 0x1B, 0x14, 0x88, 0x01, 0x17, 0x08, 0x88, 0x01, 0x17, 0x00, 0xB0, 0x01, 0x2A,
    0xF8, 0x06, 0x28, 0x00, 0x26, 0xEC, 0x06, 0x28, 0x02, 0x27, 0xE4, 0x06, 0xFC, 0x06, 0x1B, 0x06,
    0xFC, 0x06, 0x17, 0x06, 0xFC, 0x06, 0x07, 0x28, 0x00, 0x2B, 0xCC, 0x06, 0xFC, 0x06, 0x07, 0x28,
    0x00, 0x2E, 0xB8, 0x06, 0xE0, 0x00, 0x2F, 0xA8, 0x06, 0xE0, 0x01, 0x0B, 0x2F, 0x94, 0x06, 0x1C,
    0x0B, 0x0B, 0x2F, 0x80, 0x06, 0x40, 0x01, 0x0B, 0x1F, 0x70, 0x40, 0x00, 0x0C, 0x2F, 0x5C, 0x06,
    0xC0, 0x01, 0x0C, 0x13, 0x06, 0xC0, 0x01, 0x1F, 0x06, 0xC0, 0x01, 0x04, 0x1F, 0x06, 0xC0, 0x01,
    0x0C, 0x0F, 0x80, 0x00, 0x0C, 0x2F, 0x18, 0x06, 0x3C, 0x0C, 0x0C, 0x03, 0x80, 0x00, 0x1F, 0x0C,
    0x80, 0x00, 0x04, 0x2F, 0xF8, 0x05, 0x00, 0x02, 0x03, 0x2A, 0xF0, 0x05, 0x88, 0x01, 0x26, 0xE4,
    0x05, 0x88, 0x01, 0x26, 0xDC, 0x05, 0x28, 0x00, 0x1B, 0xD4, 0x28, 0x00, 0x17, 0xC8, 0x28, 0x00,
    0x17, 0xC0, 0x28, 0x00, 0x1B, 0xB8, 0x28, 0x00, 0x17, 0xAC, 0x28, 0x00, 0x2F, 0xA4, 0x05, 0x04,
    0x00, 0x23, 0x00, 0x44, 0x00, 0x1F, 0xB4, 0x04, 0x00, 0x1C, 0x1F, 0xBC, 0x04, 0x00, 0x24, 0x1F,
    0xC4, 0x04, 0x00, 0x0C, 0x1F, 0xCC, 0x04, 0x00, 0x0C, 0x1F, 0xD4, 0x04, 0x00, 0x0C, 0x1F, 0xDC,
    0x04, 0x00, 0x50, 0x10, 0x00, 0x44, 0x05, 0x96, 0x05, 0x00, 0x00, 0xE0, 0x05, 0x00, 0x00, 0xF4,
    0x05, 0x1C, 0x02, 0x10, 0x18, 0x58, 0x03, 0x92, 0x06, 0x00, 0x00, 0x34, 0x06, 0x00, 0x00, 0x48,
    0x06, 0x00, 0x0B, 0x62, 0x58, 0x06, 0x00, 0x00, 0x60, 0x06, 0x94, 0x11, 0xF2, 0x03, 0x6C, 0x06,
    0x00, 0x00, 0x74, 0x06, 0x00, 0x00, 0x88, 0x06, 0x00, 0x00, 0x9C, 0x06, 0x00, 0x00, 0xB0, 0x06,
    0x00, 0x0B, 0x22, 0xC0, 0x06, 0x94, 0x0A, 0x23, 0xC4, 0x06, 0x8C, 0x05, 0x40, 0x06, 0x00, 0x00,
    0xD0, 0xF8, 0x0F, 0x03, 0xE0, 0x03, 0x22, 0xE4, 0x06, 0xB8, 0x0E, 0x22, 0xF0, 0x06, 0x28, 0x04,
    0x0F, 0x04, 0x00, 0x11, 0x2F, 0x00, 0x07, 0x04, 0x00, 0x0B, 0x1F, 0x08, 0x04, 0x00, 0x0C, 0x1F,
    0x10, 0x04, 0x00, 0x0C, 0x1F, 0x18, 0x04, 0x00, 0x08, 0x13, 0x00, 0xF8, 0x04, 0x22, 0x1C, 0x07,
    0x30, 0x05, 0x62, 0x44, 0x07, 0x00, 0x00, 0x58, 0x07, 0xC4, 0x00, 0x22, 0x68, 0x07, 0xC4, 0x05,
    0x01, 0xB0, 0x0C, 0x03, 0xCC, 0x10, 0x13, 0x03, 0x18, 0x06, 0x5F, 0x98, 0x07, 0x00, 0x00, 0xA8,
    0x04, 0x00, 0x14, 0x1F, 0xB0, 0x04, 0x00, 0x0C, 0x1F, 0xB8, 0x04, 0x00, 0x0C, 0x1F, 0xC0, 0x04,
    0x00, 0x0C, 0x1F, 0xC8, 0x04, 0x00, 0x68, 0x10, 0x01, 0x0C, 0x02, 0x52, 0x07, 0x00, 0x00, 0xCC,
    0x07, 0xB8, 0x07, 0x26, 0xF4, 0x07, 0xF8, 0x07, 0x22, 0x18, 0x08, 0x38, 0x08, 0x22, 0x02, 0x00,
    0xF0, 0x11, 0x26, 0x34, 0x08, 0x80, 0x08, 0x00, 0xFC, 0x11, 0x1F, 0x58, 0x04, 0x00, 0x20, 0x1F,
    0x60, 0x04, 0x00, 0x0C, 0x1F, 0x68, 0x04, 0x00, 0x0C, 0x1F, 0x70, 0x04, 0x00, 0x0C, 0x1B, 0x78,
    0x04, 0x00, 0x10, 0x02, 0x50, 0x0B, 0x12, 0x08, 0x94, 0x09, 0x01, 0x7C, 0x0B, 0x12, 0x08, 0xC0,
    0x09, 0x13, 0xA4, 0xB0, 0x12, 0x23, 0xCC, 0x08, 0x20, 0x05, 0x43, 0x08, 0x00, 0x00, 0xE4, 0xF8,
    0x00, 0x00, 0x80, 0x0A, 0x6F, 0xF8, 0x08, 0x00, 0x00, 0x08, 0x09, 0x04, 0x00, 0x3F, 0x1F, 0x10,
    0x04, 0x00, 0x28, 0x1B, 0x18, 0x04, 0x00, 0x01, 0xFC, 0x02, 0x53, 0x09, 0x00, 0x00, 0x1C, 0x09,
    0xF0, 0x09, 0x12, 0x09, 0xBC, 0x0B, 0x10, 0x02, 0xA4, 0x06, 0x03, 0x7C, 0x13, 0x2F, 0x00, 0xE0,
    0x04, 0x00, 0x1B, 0x04, 0xD8, 0x0B, 0x04, 0xF4, 0x05, 0x14, 0x1C, 0xCC, 0x0B, 0x07, 0x24, 0x00,
    0x10, 0x02, 0x06, 0x00, 0x07, 0x10, 0x00, 0x1B, 0x03, 0x10, 0x00, 0x01, 0x3C, 0x08, 0x1E, 0x08,
    0x38, 0x00, 0x00, 0xA7, 0x14, 0x0F, 0x84, 0x00, 0x15, 0x2E, 0xAC, 0x08, 0x40, 0x00, 0x1E, 0x05,
    0x68, 0x00, 0x01, 0xD0, 0x01, 0x0C, 0x28, 0x00, 0x1E, 0x06, 0x28, 0x00, 0x01, 0xA8, 0x14, 0x0C,
    0x28, 0x00, 0x1E, 0x07, 0x28, 0x00, 0x06, 0x5C, 0x0B, 0x07, 0x18, 0x00, 0x1F, 0x08, 0xB8, 0x00,
    0x14, 0x0F, 0x6C, 0x01, 0x21, 0x13, 0xD4, 0x84, 0x03, 0x13, 0x02, 0xFC, 0x16, 0x01, 0x9C, 0x05,
    0x01, 0xB8, 0x09, 0x00, 0x6A, 0x07, 0x02, 0x18, 0x00, 0x13, 0x08, 0x04, 0x00, 0x1B, 0xB0, 0x18,
    0x00, 0x13, 0x07, 0x34, 0x00, 0x17, 0x9C, 0x18, 0x00, 0x04, 0xF8, 0x0A, 0x1B, 0x01, 0x3C, 0x00,
    0x1B, 0x80, 0x3C, 0x00, 0x04, 0x6C, 0x00, 0x1F, 0x6C, 0x54, 0x00, 0x04, 0x17, 0x58, 0x18, 0x00,
    0x08, 0x04, 0x08, 0x04, 0x84, 0x08, 0x00, 0x83, 0x0F, 0x1B, 0x32, 0x04, 0x17, 0x04, 0x74, 0x00,
    0x13, 0x06, 0x44, 0x00, 0x1B, 0x18, 0x5C, 0x00, 0x13, 0x0D, 0x18, 0x00, 0x1B, 0x04, 0x18, 0x00,
    0x13, 0x0A, 0x18, 0x00, 0x2A, 0xF0, 0x06, 0x18, 0x00, 0x13, 0x0C, 0x18, 0x00, 0x2F, 0xDC, 0x06,
    0x8C, 0x00, 0x07, 0x0F, 0x0C, 0x00, 0x05, 0x1F, 0x02, 0xA4, 0x00, 0x08, 0x04, 0x68, 0x09, 0x0F,
    0x20, 0x00, 0x06, 0x0F, 0xBC, 0x01, 0x14, 0x2F, 0x48, 0x06, 0xA4, 0x02, 0x13, 0x2F, 0x24, 0x06,
    0xA4, 0x02, 0x13, 0x2F, 0x00, 0x06, 0xA4, 0x02, 0x13, 0x2F, 0xDC, 0x05, 0xA4, 0x02, 0x10, 0x0B,
    0x94, 0x01, 0x13, 0x2B, 0x4C, 0x01, 0x2A, 0xA4, 0x05, 0x64, 0x01, 0x13, 0x2C, 0x18, 0x00, 0x1B,
    0x90, 0x18, 0x00, 0x13, 0x29, 0x18, 0x00, 0x1B, 0x7C, 0x18, 0x00, 0x13, 0x2A, 0x18, 0x00, 0x2F,
    0x68, 0x05, 0x94, 0x01, 0x07, 0x1F, 0x01, 0x7C, 0x01, 0x29, 0x0E, 0x60, 0x02, 0x0F, 0x90, 0x01,
    0x16, 0x2F, 0xD8, 0x04, 0x90, 0x01, 0x13, 0x2F, 0xB4, 0x04, 0x90, 0x01, 0x13, 0x2F, 0x90, 0x04,
    0x90, 0x01, 0x13, 0x2F, 0x6C, 0x04, 0x34, 0x04, 0x57, 0x0F, 0x04, 0x00, 0x06, 0x0B, 0xF0, 0x01,
    0x13, 0x33, 0xA8, 0x01, 0x2A, 0xD4, 0x03, 0xC0, 0x01, 0x13, 0x32, 0x18, 0x00, 0x1B, 0xC0, 0x18,
    0x00, 0x13, 0x30, 0x18, 0x00, 0x1B, 0xAC, 0x18, 0x00, 0x13, 0x31, 0x18, 0x00, 0x17, 0x98, 0x18,
    0x00, 0x0F, 0x6C, 0x03, 0x1D, 0x1F, 0x01, 0xF0, 0x01, 0x10, 0x10, 0x09, 0x8C, 0x0A, 0x0F, 0xF0,
    0x01, 0x18, 0x0C, 0x84, 0x01, 0x2F, 0xFC, 0x02, 0xFC, 0x01, 0x13, 0x2F, 0xD8, 0x02, 0xFC, 0x01,
    0x13, 0x2F, 0xB4, 0x02, 0xFC, 0x01, 0x13, 0x2F, 0x90, 0x02, 0xFC, 0x01, 0x04, 0x0F, 0x04, 0x01,
    0x18, 0x00, 0x43, 0x00, 0x13, 0x25, 0x04, 0x01, 0x2A, 0x44, 0x02, 0x80, 0x01, 0x13, 0x26, 0x18,
    0x00, 0x1B, 0x30, 0x18, 0x00, 0x13, 0x24, 0x18, 0x00, 0x1B, 0x1C, 0x18, 0x00, 0x14, 0x23, 0xDC,
    0x05, 0x07, 0x18, 0x00, 0x0F, 0x80, 0x03, 0x1D, 0x1F, 0x02, 0x80, 0x03, 0x20, 0x1F, 0x05, 0xF0,
    0x02, 0x08, 0x1F, 0x0B, 0x34, 0x03, 0x01, 0x1F, 0x01, 0x60, 0x01, 0x0F, 0x08, 0x04, 0x00, 0x2E,
    0x0C, 0x00, 0x44, 0x00, 0x2F, 0x2C, 0x01, 0x7C, 0x01, 0x23, 0x01, 0xC0, 0x12, 0x0F, 0xD0, 0x06,
    0x18, 0x04, 0x30, 0x07, 0x26, 0xC4, 0x00, 0x54, 0x01, 0x1F, 0xBC, 0x04, 0x00, 0x0B, 0x00, 0x30,
    0x00, 0x22, 0xE0, 0x0A, 0x77, 0x16, 0x27, 0xE0, 0xB0, 0x10, 0x00, 0x04, 0x14, 0x00, 0x17, 0x0A,
    0x04, 0x00, 0x10, 0x94, 0xF4, 0x10, 0x07, 0x04, 0x00, 0x0C, 0x20, 0x00, 0x10, 0x84, 0xEC, 0x17,
    0x07, 0x04, 0x00, 0x0C, 0x20, 0x00, 0x10, 0x74, 0xE4, 0x0A, 0x07, 0x04, 0x00, 0x0C, 0x20, 0x00,
    0x10, 0x64, 0x00, 0x09, 0x03, 0x04, 0x00, 0x00, 0x1C, 0x00, 0xF1, 0x16, 0x19, 0x00, 0x00, 0x00,
    0x1A, 0x00, 0x01, 0x00, 0x21, 0x00, 0x02, 0x00, 0x1F, 0x00, 0x03, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x1C, 0x00, 0x05, 0x00, 0x1B, 0x00, 0x06, 0x00, 0x1D, 0x00, 0x07, 0x00, 0x1E, 0x00, 0x08, 0x00,
    0x0B, 0xB0, 0x07, 0xF3, 0x0C, 0x01, 0x00, 0x0C, 0x00, 0x02, 0x00, 0x0E, 0x00, 0x03, 0x00, 0x14,
    0x00, 0x00, 0x00, 0x13, 0x00, 0x01, 0x00, 0x15, 0x00, 0x02, 0x00, 0x16, 0x00, 0x03, 0x00, 0x0E,
    0x20, 0x00, 0x91, 0x0B, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x03, 0x00, 0x0B, 0xB0, 0x07, 0x70, 0x01,
    0x00, 0x0D, 0x00, 0x02, 0x00, 0x54, 0xA4, 0x16, 0x00, 0xE4, 0x01, 0x00, 0xE0, 0x1B, 0x03, 0xB4,
    0x00, 0x10, 0x90, 0xA8, 0x08, 0x00, 0xFC, 0x11, 0x00, 0x5C, 0x03, 0x00, 0x80, 0x04, 0x00, 0x38,
    0x12, 0x00, 0x90, 0x03, 0x00, 0xA8, 0x10, 0x00, 0x94, 0x02, 0x61, 0x03, 0x01, 0x03, 0x03, 0x03,
    0x03, 0x60, 0x20, 0x1A, 0x03, 0x01, 0x00, 0x0E, 0x96, 0x20, 0x0B, 0xF4, 0x07, 0x04, 0xA8, 0x1F,
    0x13, 0x00, 0x60, 0x00, 0x08, 0x10, 0x00, 0x1B, 0x9C, 0x10, 0x00, 0x1B, 0x90, 0x10, 0x00, 0x1B,
    0x84, 0x10, 0x00, 0x1B, 0x78, 0x10, 0x00, 0x1B, 0x6C, 0x10, 0x00, 0x17, 0x60, 0x24, 0x03, 0x0C,
    0x34, 0x03, 0x0F, 0x90, 0x00, 0x01, 0x1B, 0x34, 0x10, 0x00, 0x13, 0x28, 0x08, 0x00, 0xF0, 0x15,
    0xEF, 0x81, 0x8B, 0x00, 0xEF, 0x81, 0x8C, 0x00, 0xEF, 0x80, 0x91, 0x00, 0xEF, 0x81, 0xAE, 0x00,
    0xEF, 0x8A, 0x87, 0x00, 0xEF, 0x80, 0x95, 0x00, 0xEF, 0x80, 0x93, 0x00, 0xEF, 0x82, 0x93, 0x00,
    0xEF, 0x80, 0x8B, 0x00
};

native_var_t native_vars[] = {
    { NATIVE_VAR_TYPE_NONE, 0, 0 },
};


ActionExecFunc actions[] = {
    action_chart_current_pause,
    action_chart_current_resume,
    action_btn_power,
};


#if defined(EEZ_FOR_LVGL)

void ui_init() {
    eez_flow_init(assets, sizeof(assets), (lv_obj_t **)&objects, sizeof(objects), images, sizeof(images), actions);
}

void ui_tick() {
    eez_flow_tick();
    tick_screen(g_currentScreen);
}

#else

static int16_t currentScreen = -1;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

static const void *getLvglImageByName(const char *name) {
    for (size_t imageIndex = 0; imageIndex < sizeof(images) / sizeof(ext_img_desc_t); imageIndex++) {
        if (strcmp(images[imageIndex].name, name) == 0) {
            return images[imageIndex].img_dsc;
        }
    }
    return 0;
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);
}

void ui_tick() {
    tick_screen(currentScreen);
}

#endif
