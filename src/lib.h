#include "display.h"
#include "interrupts.h"

int minMax(int min, int value, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
