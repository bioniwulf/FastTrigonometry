#ifndef FASTTRIGONOMETRY_H
#define FASTTRIGONOMETRY_H

#define MathPI  3.141592653F

/// Функция быстрого синуса
/// Входное значение [Рад] в любом диапазоне
/// На выходе [-1; 1]
float fastSin(float angle_rad);

/// Функция быстрого косинуса
/// Входное значение [Рад] в любом диапазоне
/// На выходе [-1.0; 1.0]
float fastCos(float angle_rad);

/// Функция быстрого обратного тангенса 2
/// Входное значение в любом диапазоне
/// На выходе [-pi; pi]
float fastAtan2(float y, float x);
#endif // FASTTRIGONOMETRY_H
