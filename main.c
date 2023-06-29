#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "stepper.h"
#include "coordinates.h"

// PORTB
#define LED_STOP 0
#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 2
#define BUTTON_PIN_3 3

// PORTD
#define LED_HOME 2
#define LED_START 3

#define MOTOR1_STEP 4
#define MOTOR1_DIR 5

#define MOTOR2_STEP 6
#define MOTOR2_DIR 7

// Variables
#define LIMIT 3
#define LINE 500
#define DELAY_MS 3000

coordinate_t EEMEM storedCoordinate;

void setup(void);
void start(void);
void reset(void);
void loop(void);

int main(int argc, char **argv)
{
  setup();

  coordinate_t coordinate;

  eeprom_read_block((void*)&coordinate, (const void*)&storedCoordinate, sizeof(coordinate_t));

  if(coordinate.x > 0 || coordinate.y > 0)
  {
    PORTD |= ((1 << LED_HOME) | (1 << MOTOR1_DIR));
    PORTD &= ~(1 << MOTOR2_DIR);

    home(coordinate.x, MOTOR1_STEP);
    home(coordinate.y, MOTOR2_STEP);

    PORTD &= ~(1 << LED_HOME);
  }

  coordinate.x = 0;
  coordinate.y = 0;

  eeprom_update_block((const void*)&coordinate, (void*)&storedCoordinate, sizeof(coordinate_t)); 

  while(true)
  {
    loop();
  }

  return 0;
}

void setup(void)
{
  DDRD |= (1 << LED_HOME) | (1 << LED_START) | (1 << MOTOR1_STEP) | (1 << MOTOR1_DIR) | (1 << MOTOR2_STEP) | (1 << MOTOR2_DIR);
  DDRB |= (1 << LED_STOP);

  DDRB &= ~((1 << BUTTON_PIN_1) | (1 << BUTTON_PIN_2) | (1 << BUTTON_PIN_3));

  PORTD &= ~((1 << LED_HOME) | (1 << LED_START) | (1 << MOTOR1_STEP) | (1 << MOTOR2_STEP)); 
  PORTB &= ~(1 << LED_STOP);

  PORTB |= (1 << BUTTON_PIN_1) | (1 << BUTTON_PIN_2) | (1 << BUTTON_PIN_3); 
}

void start(void)
{
  PORTD &= ~(1 << MOTOR1_DIR);
  PORTD |= (1 << MOTOR2_DIR);

  step((LINE / 2), MOTOR1_STEP, MOTOR1_DIR);
  step((LINE * 2.5), MOTOR2_STEP, MOTOR2_DIR);
}

void reset(void)
{
  PORTD |= (1 << LED_HOME);

  coordinate_t coordinate;

  eeprom_read_block((void*)&coordinate, (const void*)&storedCoordinate, sizeof(coordinate_t));
    
  home(coordinate.x, MOTOR1_STEP);
  home(coordinate.y, MOTOR2_STEP);

  PORTD &= ~(1 << LED_HOME);
    
  coordinate.x = 0;
  coordinate.y = 0;

  eeprom_update_block((const void*)&coordinate, (void*)&storedCoordinate, sizeof(coordinate_t));
}

void loop(void)
{
  PORTB |= (1 << LED_STOP); 
  
  if(!(PINB & (1 << BUTTON_PIN_1)))
  {
    start();

    PORTB &= ~(1 << LED_STOP);
    PORTD |= (1 << LED_START);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD &= ~(1 << MOTOR2_DIR);

    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    PORTD |= (1 << MOTOR1_DIR);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    PORTD &= ~(1 << MOTOR1_DIR);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD &= ~(1 << LED_START);
    _delay_ms(DELAY_MS);

    PORTD |= ((1 << LED_HOME) | (1 << MOTOR1_DIR)); 

    reset(); 
  }
  else if(!(PINB & (1 << BUTTON_PIN_2)))
  {
    start();

    PORTB &= ~(1 << LED_STOP);
    PORTD |= (1 << LED_START);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD &= ~(1 << MOTOR2_DIR);

    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    PORTD |= (1 << MOTOR1_DIR);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD &= ~(1 << MOTOR1_DIR);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    PORTD |= (1 << MOTOR1_DIR);

    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD &= ~(1 << LED_START);
    _delay_ms(DELAY_MS);

    reset(); 
  }
  else if(!(PINB & (1 << BUTTON_PIN_3)))
  {
    start();

    PORTB &= ~(1 << LED_STOP);
    PORTD |= (1 << LED_START);
    PORTD &= ~(1 << MOTOR2_DIR);

    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    step((LINE * 2), MOTOR1_STEP, MOTOR1_DIR);
    PORTD |= ((1 << MOTOR1_DIR) | (1 << MOTOR2_DIR));

    step(LINE, MOTOR2_STEP, MOTOR2_DIR);
    PORTD &= ~(1 << MOTOR2_DIR);

    step((LINE * 2), MOTOR2_STEP, MOTOR2_DIR);
    PORTD &= ~(1 << LED_START);
    _delay_ms(DELAY_MS);

    PORTD |= (1 << LED_HOME);

    reset(); 
  }
}
