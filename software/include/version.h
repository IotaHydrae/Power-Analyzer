#ifndef __VERISION_H
#define __VERISION_H

#define SW_VERSION_MAJOR 0
#define SW_VERSION_MINOR 0
#define SW_VERSION_PATCH 1

#define HW_VERSION_MAJOR 0
#define HW_VERSION_MINOR 0
#define HW_VERSION_PATCH 1

#define MAJOR_OFFS(v) (v << 16)
#define MINOR_OFFS(v) (v << 8)
#define PATCH_OFFS(v) (v)

#define SW_VERSION_NUMBER (MAJOR_OFFS(SW_VERSION_MAJOR) | MINOR_OFFS(SW_VERSION_MINOR) | PATCH_OFFS(SW_VERSION_PATCH))
#define HW_VERSION_NUMBER (MAJOR_OFFS(HW_VERSION_MAJOR) | MINOR_OFFS(HW_VERSION_MINOR) | PATCH_OFFS(HW_VERSION_PATCH))

#endif
