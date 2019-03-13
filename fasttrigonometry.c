#include "fasttrigonometry.h"

typedef unsigned short  uint16_t;
typedef signed short    int16_t;

#define MathPI4	0.785398163F

#define ABS(x) (x >= 0 ? x: (-x))
#define SIGN(x) (x>= 0 ? 1 : (-1))

/// Размер массива значений синусов
#define TrigoQuarterSize 41

/// Значения синуса в диапазоне [0; pi / 2]
/// приведенная к максимальной ёмкости uint16_t: 2^16
static const uint16_t TrigoQuarter[TrigoQuarterSize] = {
   0, 2573, 5142, 7703, 10252, 12785, 15299, 17789, 20251,
   22683, 25079, 27437, 29752, 32022, 34242, 36409, 38521,
   40572, 42562, 44485, 46340, 48124, 49833, 51466, 53019,
   54490, 55878, 57179, 58392, 59515, 60546, 61484, 62327,
   63075, 63724, 64276, 64728, 65081, 65333, 65484, 65535 };

/// Дискрет значений угла между значениями синуса массива
#define DeltaDegreeRad (MathPI / (2 * (TrigoQuarterSize - 1)))

float fastFmod (float a, float b) {
    return (a - b * (int)(a / b));
}
float normalizeAnglePositive(float angle) {
    return fastFmod(fastFmod(angle, 2.0F * MathPI) + 2.0F * MathPI, 2.0F * MathPI);
}

/// Нормировка угла на [-pi, pi]
float normalizeAngle(float angle) {
    float a = normalizeAnglePositive(angle);
    if (a > MathPI)
      a -= 2.0F * MathPI;
    return a;
}

/// Линейная аппроксимация sin угла
/// по таблице в диапазоне [0; pi / 2]
float linearApprox(float angle_rad) {

    int16_t low_index = 0;
    float temp_angle_rad = 0.0F;

    for(int16_t index = 0; index < TrigoQuarterSize; index++) {
        temp_angle_rad = index * DeltaDegreeRad;
        if(temp_angle_rad >= angle_rad) {
            break;
        }
        low_index++;
    }

    float value;
    if(low_index == TrigoQuarterSize - 1) {
        value = TrigoQuarter[low_index];
    } else {
        value = TrigoQuarter[low_index] + (TrigoQuarter[low_index + 1] - TrigoQuarter[low_index])
            * (temp_angle_rad - angle_rad) / DeltaDegreeRad;
    }

    return value / (1 << 16);
}

/// Функция быстрого синуса
/// Входное значение [Рад] в любом диапазоне
/// На выходе [-1; 1]
float fastSin(float angle_rad) {
    /// Нормализируем угол в диапазон [-pi, pi]
    angle_rad = normalizeAngle(angle_rad);

    /// Берем угол с другой стороны если он больше pi / 2
    if(ABS(angle_rad) > MathPI - ABS(angle_rad)) {
        angle_rad = MathPI - ABS(angle_rad);
    }

    /// Возвращаем линейную аппроксимацию от угла в диапазоне [0; pi / 2]
    return SIGN(angle_rad) * linearApprox(ABS(angle_rad));
}

/// Функция быстрого косинуса
/// Входное значение [Рад] в любом диапазоне
/// На выходе [-1.0; 1.0]
float fastCos(float angle_rad) {
    /// Пользуемся тем что косинус можно
    /// выразить через синус
    return fastSin(angle_rad + MathPI / 2);
}

/// Функция быстрого обратного тангенса
/// Входное значение в любом диапазоне
/// На выходе [-pi; pi]
float fastAtan(float x) {
    return (MathPI4 * x - x * (ABS(x) - 1) *
            (0.2447F + 0.0663F * ABS(x)));
}

/// Функция быстрого обратного тангенса 2
/// Входное значение в любом диапазоне
/// На выходе [-pi; pi]
float fastAtan2(float y, float x) {
    if((x == 0.0F && y == 0.0F) || x == 0.0F) {
        return 0.0;
    }

    if(x >= y) {
        if(x >= -y) {
            return fastAtan(y / x);
        } else {
            return (-MathPI / 2) - fastAtan(x / y);
        }
    } else {
        if(x >= -y) {
            return (MathPI / 2) - fastAtan(x / y);
        } else {
            if(y >= 0.0F) {
                return MathPI + fastAtan(y / x);
            } else {
                return -MathPI + fastAtan(y / x);
            }
        }
    }
}
