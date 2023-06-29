#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#include "coordinates.h"

#define DELAY_MS 10

void setBit(volatile uint8_t *reg, uint8_t bit)
{
  *reg |= (1 << bit);
}

void clearBit(volatile uint8_t *reg, uint8_t bit)
{
  *reg &= ~(1 << bit);
}

bool isBitSet(uint8_t byte, uint8_t bit)
{
  return (byte & (1 << bit)) != 0;
}

void step(uint16_t steps, uint8_t bit, uint8_t dir)
{
  coordinate_t coordinate;

  eeprom_read_block((void*)&coordinate, (const void*)&storedCoordinate, sizeof(coordinate_t));

  for(uint16_t i = 0; i < steps; i++)
  {
    setBit(&PORTD, bit);
    _delay_ms(DELAY_MS);
    clearBit(&PORTD, bit);
    _delay_ms(DELAY_MS); 

    if(isBitSet(PIND, dir))
    { 
      coordinate.x -= (bit == 4);
      coordinate.y += (bit == 6);
    }
    else
    {
      coordinate.x += (bit == 4);
      coordinate.y -= (bit == 6);
    }

    eeprom_update_block((const void*)&coordinate, (void*)&storedCoordinate, sizeof(coordinate_t));
  } 
}

void home(uint16_t steps, uint8_t bit)
{
  for(uint16_t i = steps; i > 0; i--)
  {
    setBit(&PORTD, bit);
    _delay_ms(DELAY_MS);
    clearBit(&PORTD, bit);
    _delay_ms(DELAY_MS);
  }
}
