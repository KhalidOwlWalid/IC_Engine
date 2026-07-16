#pragma once

#include <math.h>

namespace ice::math {

inline float deg2rad(float deg) {
    return deg * (M_PI / 180);
}

inline float rad2deg(float rad) {
    return rad * (180 / M_PI);
}

}
