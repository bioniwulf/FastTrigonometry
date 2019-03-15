#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <math.h>

/// Быстрая тригонометрия не требующая никаких зависимостей
#include "fasttrigonometry.h"

#define TestsSize 1000

#define EQUALRANGE_SIN 0.02
#define EQUALRANGE_RAD 0.02

#define ABS(x) ((x) >= 0 ? (x): (-x))

float aEqual (float x, float y, float range) {
    float error = x - y;
    return ABS(error) < range ? 1: 0;
}

float getRand(float max) {
    return (float)rand()/(float)(RAND_MAX / (2 * max)) - max;
}

int main()
{
    printf("Fast Trigonometric\n");
    srand (time(NULL));

    printf("Sin Angle Tests...\n");
    assert(aEqual(sin(0), fastSin(0), EQUALRANGE_SIN));
    assert(aEqual(sin(MathPI), fastSin(MathPI), EQUALRANGE_SIN));
    assert(aEqual(sin(-MathPI), fastSin(-MathPI), EQUALRANGE_SIN));
    assert(aEqual(sin(-2 * MathPI), fastSin(-2 * MathPI), EQUALRANGE_SIN));
    assert(aEqual(sin(-MathPI / 4), fastSin(-MathPI / 4), EQUALRANGE_SIN));
    assert(aEqual(sin(-6.27), fastSin(-6.27), EQUALRANGE_SIN));

    for(int i = 0; i < TestsSize; i++) {
        float value = getRand(2 * MathPI);
        assert(aEqual(sin(value), fastSin(value), EQUALRANGE_SIN));
    }
    printf("Passed!\n");

    printf("Cos Angle Tests...\n");
    for(int i = 0; i < TestsSize; i++) {
        float value = getRand(2 * MathPI);
        assert(aEqual(cos(value), fastCos(value), EQUALRANGE_SIN));
    }
    printf("Passed!\n");

    printf("Atan Angle Tests...\n");
    printf("Value: %f, %f \n", atan2(67.357, -26.444), fastAtan2(67.357, -26.444));
    for(int i = 0; i < TestsSize; i++) {
        float value_x = getRand(100);
        float value_y = getRand(100);
//        printf("Value: %f, %f \n", value_x, value_y);
        assert(aEqual(atan2(value_y, value_x), fastAtan2(value_y, value_x), EQUALRANGE_RAD));
    }
    printf("Passed!\n");

    printf("Full Tests...\n");
    for(int i = 0; i < TestsSize; i++) {
        float value = getRand(MathPI);
//        printf("Value: %f, %f \n", value, fastAtan2(fastSin(value), fastCos(value)));
        assert(aEqual(value, fastAtan2(fastSin(value), fastCos(value)), 0.03));
    }
    printf("Passed!\n");
    return 0;
}
