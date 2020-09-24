#pragma once

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#define LAYOUT( \
    KA1, KA2 \
) \
{ \
    { KA1, KA2 } \
}
