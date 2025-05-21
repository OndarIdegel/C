/*
 * Задание 4: Поменять в целом положительном числе (типа int) значение третьего
 * байта на введенное пользователем число (изначальное число также
 * вводится с клавиатуры).
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int original_num;
    int new_byte;
    int result;
    
    printf("Введите целое положительное число: ");
    scanf("%d", &original_num);
    
    if (original_num < 0) {
        printf("Ошибка: введено отрицательное число.\n");
        return 1;
    }
    
    printf("Введите значение для третьего байта (0-255): ");
    scanf("%d", &new_byte);
    
    if (new_byte < 0 || new_byte > 255) {
        printf("Ошибка: значение байта должно быть в диапазоне от 0 до 255.\n");
        return 1;
    }
    
    // Очищаем третий байт (биты 16-23) и устанавливаем новое значение
    result = (original_num & ~(0xFF << 16)) | (new_byte << 16);
    
    printf("Исходное число: %d (0x%X)\n", original_num, original_num);
    printf("Новое значение третьего байта: %d (0x%X)\n", new_byte, new_byte);
    printf("Результат: %d (0x%X)\n", result, result);
    
    return 0;
}
