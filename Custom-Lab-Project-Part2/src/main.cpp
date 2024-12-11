#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "serialATmega.h"
#include "spiAVR.h"
#include "display.h"
#include "alphabet.h"
#include "snes.h"
#include "sprites.h"

#define NUM_TASKS 3 //TODO: Change to the number of tasks being used

//Task struct for concurrent synchSMs implmentations
typedef struct _task {
	signed char state; 		       // Task's current state
	unsigned long period; 		   // Task period
	unsigned long elapsedTime; 	 // Time elapsed since last task tick
	int (*TickFct)(int); 		     // Task tick function
} task;


//TODO: Define Periods for each task
// e.g. const unsined long TASK1_PERIOD = <PERIOD>

const unsigned long GCD_PERIOD = 1; //TODO:Set the GCD Period

task tasks[NUM_TASKS]; // declared task array with 5 tasks

enum mainScreen {SCREEN_INIT, WAIT, UPDATE};
int TickFct_screen(int);
unsigned long SCREEN_PERIOD = 200;
bool runGame = false;

enum moveObj {OBJ_INIT, SPAWN, MOVE, COOLDOWN}; //updates position of non player controlled objects
int TickFct_move(int);
unsigned long OBJ_PERIOD = 200;

enum playerControl {PLAYER_INIT}; 
int TickFct_playerControl(int);
unsigned long PLAYER_PERIOD = 200;

void TimerISR() {
	for ( unsigned int i = 0; i < NUM_TASKS; i++ ) {              // Iterate through each task in the task array
		if ( tasks[i].elapsedTime == tasks[i].period ) {            // Check if the task is ready to tick
			tasks[i].state = tasks[i].TickFct(tasks[i].state);        // Tick and set the next state for this task
			tasks[i].elapsedTime = 0;                                 // Reset the elapsed time for the next tick
		}
		tasks[i].elapsedTime += GCD_PERIOD;                         // Increment the elapsed time by GCD_PERIOD
	} 
}

//TODO: Create your tick functions for each task

int main(void) {
    //TODO: initialize all your inputs and ouputs
    //DDR 1= output, 0 on port and vice versa for input
    //A0-2 are inputs, rest are outputs
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    ADC_init();   // initializes ADC
    //serial_init(9600);
    SPI_INIT();
    ST7735_init();
    SNES_pinSet();
    //serial_println("starting");

    //TODO: Initialize tasks here
    // e.g. 
    // tasks[0].period = ;
    // tasks[0].state = ;
    // tasks[0].elapsedTime = ;
    // tasks[0].TickFct = ;

    tasks[0].period = SCREEN_PERIOD;
    tasks[0].state = SCREEN_INIT;
    tasks[0].elapsedTime = tasks[0].period;
    tasks[0].TickFct = &TickFct_screen;

    tasks[1].period = OBJ_PERIOD;
    tasks[1].state = OBJ_INIT;
    tasks[1].elapsedTime = tasks[1].period;
    tasks[1].TickFct = &TickFct_move;

    tasks[2].period = PLAYER_PERIOD;
    tasks[2].state = PLAYER_INIT;
    tasks[2].elapsedTime = tasks[2].period;
    tasks[2].TickFct = &TickFct_playerControl;

    TimerSet(GCD_PERIOD);
    TimerOn();

    while(1) {}

    return 0;
}

int TickFct_screen(int state) {
  //state transitions
  switch (state) { 
  //X, starts from 1, ends at 19
  case SCREEN_INIT:
    //128x128
    makeEntity(0, 0xFF, 0, 0xFF, 0x00); //black screen 
    referenceSpawn();
    printStr("PRESS ANY", 2, 20, 0xF00);
    printStr("BUTTON TO START", 2, 35, 0xF00);
    state = WAIT; //adjust later based on SNES input
    break;

  case WAIT:
    state = (SNES_IDLE() != 255) ? UPDATE: WAIT; 
    if(state == UPDATE) {
      makeEntity(0, 0xFF, 0, 0xFF, 0x00); //clear screen before starting
    }
    break;

  case UPDATE:
  state = UPDATE; 
  break;

  default: 
  break;
  }

  //state actions
  switch (state) {
  case WAIT:
  serial_println(SNES_IDLE()); 
  break;

  case UPDATE: 
    //128 x 128
    runGame = true;
    // serial_println(SNES_IDLE());
    break;

  default: 
  break;
  }

  return state;
}

int atk[2]; //Possibly implement into vector
int wait; //Keep count to wait

int TickFct_move(int state) {
  //state transitions
  switch (state) {
  case OBJ_INIT:
  state = (runGame) ? SPAWN: OBJ_INIT; 
  break;

  case SPAWN: 
  state = (runGame) ? MOVE: OBJ_INIT; 
  break;

  case MOVE: 
  state = MOVE; 
  break;

  default: 
  break;
  }

  //state actions
  switch (state) {
  case SPAWN: //spawn entity going from right to left seems to work fine, but left to right is still work in progress
    commonEnemy(60, 60); //60, 60 will serve as center for this object and determine where projectiles spawn
    commonAtk(55,60);
    atk[0] = 60;
    atk[1] = 55;
    wait = 6;
    break;

  case MOVE: //handle projectile
    // atk[0] = commonAtkUpdate(atk[0], 60);
    atk[1] = commonAtkUpdateAlt(atk[1], 60);
    serial_println(SNES_IDLE());
    break;

  default: 
  break;
  }

  return state;
}


int TickFct_playerControl(int state) {
  //state transitions
  switch (state) {
  case PLAYER_INIT: //wait for SNES input
  break; 

  default:
  break;
  }

  //state actions
  switch (state) {
  case PLAYER_INIT: 
  break;

  default: 
  break;
  }
  
  return state;
}