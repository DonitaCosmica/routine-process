#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>

void step(uint16_t, uint8_t, uint8_t);
void home(uint16_t, uint8_t);

#endif // !STEPPER_H
