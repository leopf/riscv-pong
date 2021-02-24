#include "display.h"
#include "interrupts.h"

#define CPU_CLOCK 2000000

int minMax(int min, int value, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

void wait_one_sec() {
    for (int i = 0; i < 5000000; i++) {}
}
