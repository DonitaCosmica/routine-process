#ifndef COORDINATES_H
#define COORDINATES_H

#include <avr/eeprom.h>
#include <stdint.h>

typedef struct  
{
  volatile uint16_t x;
  volatile uint16_t y;

} coordinate_t;

extern coordinate_t EEMEM storedCoordinate;

#endif // !COORDINATES_H
