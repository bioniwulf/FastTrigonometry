#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <math.h>

/// Быстрая тригонометрия не требующая никаких зависимостей
#include "fasttrigonometry.h"

#define TestsSize 1000

#define ABS(x) (x >= 0 ? x: (-x))
#define EQUALRANGE 0.01
#define AEQUAL(x, y) ((ABS(x) - ABS(y) < EQUALRANGE) ? 1 : 0)

float getRand(float max) {
    return (float)rand()/(float)(RAND_MAX / (2 * max)) - max;
}

int main()
{
    printf("Fast Trigonometric\n");

    printf("Sin Angle Tests...\n");
    assert(AEQUAL(sin(0), fastSin(0)));
    assert(AEQUAL(sin(MathPI), fastSin(MathPI)));
    assert(AEQUAL(sin(-MathPI), fastSin(-MathPI)));
    assert(AEQUAL(sin(2 * MathPI), fastSin(2 * MathPI)));
    assert(AEQUAL(sin(-MathPI / 4), fastSin(-MathPI / 4)));

    for(int i = 0; i < TestsSize; i++) {
        float value = getRand(2 * MathPI);
        assert(AEQUAL(sin(value), fastSin(value)));
    }
    printf("Passed!\n");

    printf("Cos Angle Tests...\n");
    for(int i = 0; i < TestsSize; i++) {
        float value = getRand(2 * MathPI);
        assert(AEQUAL(cos(value), fastCos(value)));
    }
    printf("Passed!\n");

    printf("Atan Angle Tests...\n");
    for(int i = 0; i < TestsSize; i++) {
        float value_x = getRand(100);
        float value_y = getRand(100);
        assert(AEQUAL(atan2(value_y, value_x), fastAtan2(value_y, value_x)));
    }
    printf("Passed!\n");
    return 0;
}
