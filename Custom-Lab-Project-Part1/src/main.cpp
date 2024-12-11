#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "serialATmega.h"
#include "spiAVR.h"

#define NUM_TASKS 2 //TODO: Change to the number of tasks being used

void HardwareReset() {
  //set reset pin to low
  PORTB = SetBit(PORTB, 0, 0);
  _delay_ms(200);

  //set reset pin to high
  PORTB = SetBit(PORTB, 0, 1);
  _delay_ms(200);
}

void data_command(bool set) {
  PORTB = SetBit(PORTB, 1, set); //1 when data, 0 when commands
}

void setSS(bool set) {
  PORTB = SetBit(PORTB, 2, set); //set to 0 before using SPI_SEND()
}

void command(int cmd) {
  data_command(false);
  setSS(false);
  SPI_SEND(cmd);
  setSS(true);
}

void data(int val) {
  data_command(true);
  setSS(false);
  SPI_SEND(val);
  setSS(true);
}

void ST7735_init() {
  HardwareReset();
  command(0x01); //SWERESET
  _delay_ms(150); 

  command(0x11); //SLPOUT
  _delay_ms(200);

  command(0x0C); //COLMOD
  data(0x06);    //18 bit color mode
  _delay_ms(10);
  
  command(0x29); //DISPON
  _delay_ms(200);
}

//Task struct for concurrent synchSMs implmentations
typedef struct _task {
	signed char state; 		       // Task's current state
	unsigned long period; 		   // Task period
	unsigned long elapsedTime; 	 // Time elapsed since last task tick
	int (*TickFct)(int); 		     // Task tick function
} task;


//TODO: Define Periods for each task
// e.g. const unsined long TASK1_PERIOD = <PERIOD>

const unsigned long GCD_PERIOD = 100; //TODO: Set the GCD Period

task tasks[NUM_TASKS]; //declared task array with 5 tasks

enum mainScreen {SCREEN_INIT, UPDATE};
int TickFct_screen(int);
unsigned long SCREEN_PERIOD = 200;

int objTracker[1][4]; //keeps track of objects in the field

enum moveObj {OBJ_INIT, SPAWN, MOVE};
int TickFct_move(int);
unsigned long OBJ_PERIOD = 200;


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
    HardwareReset();
    ST7735_init();
    // serial_println("starting");

    //TODO: Initialize tasks here
    //  e.g.
    //  tasks[0].period = ;
    //  tasks[0].state = ;
    //  tasks[0].elapsedTime = ;
    //  tasks[0].TickFct = ;

    tasks[0].state = SCREEN_INIT;
    tasks[0].period = SCREEN_PERIOD;
    tasks[0].elapsedTime = tasks[0].period;
    tasks[0].TickFct = &TickFct_screen;

    tasks[1].state = OBJ_INIT;
    tasks[1].period = OBJ_PERIOD;
    tasks[1].elapsedTime = tasks[1].period;
    tasks[1].TickFct = &TickFct_move;

    TimerSet(GCD_PERIOD);
    TimerOn();

    while (1) {}

    return 0;
}


void makeEntity(int startX, int finalX, int startY, int finalY, int color) {
    command(0x2A);
    //SPI_SEND(0x2A)
    //CASET, sets column address
    data(0x00); //starting X bits 15-8
    data(startX); //starting X bits 7-0

    data(0x00); //ending X bits 15-8
    data(finalX); //ending X bits 7-0

    //SPI_SEND(0x2B)
    //RASET, sets row address
    command(0x2B);
    data(0x00); //starting Y bits 15-8
    data(startY); //starting Y bits 7-0

    data(0x00); //ending Y bits 15-8
    data(finalY); //ending Y bits 7-0

    command(0x2C);
    //SPI_SEND(0x2C) 
    //RAMWR, memory write

    data_command(true);
    setSS(false);

    for (int i = 0; i <= (finalX); i++) {
      for (int j = 0; j <= (finalY); j++) {
        SPI_SEND(color);
      }
    }
    // SPI_SEND(color);

    setSS(true);
}

int TickFct_screen(int state) {
  //state transitions
  switch (state) {
  case SCREEN_INIT: 
  makeEntity(0x00, 0xFF, 0x00, 0xFF, 0x00); //black out screen
  state = UPDATE; 
  break;

  case UPDATE: 
  state = UPDATE; 
  break;

  default: 
  break;
  }

  //state actions
  switch (state) {
  case UPDATE: //128 x 128
  // ST7735_init();
  for (int i = 0; i < 1; i++) {
  makeEntity(0x00, 0xFF, 0x00, 0xFF, 0x00);
  makeEntity(objTracker[i][0], objTracker[i][1], objTracker[i][2], objTracker[i][3], 0xC0);
  }
  break;

  default: 
  break;
  }

  return state;
}

int TickFct_move(int state) {
  //state transitions
  switch (state) {
  case OBJ_INIT: 
  state = SPAWN; 
  break;

  case SPAWN: 
  state = MOVE; 
  makeEntity(62, 66, 62, 66, 0xC0); //spawn 4x4 object
  objTracker[0][0] = 62;
  objTracker[0][1] = 66;
  objTracker[0][2] = 62;
  objTracker[0][3] = 66;
  break;

  case MOVE: 
  break;

  default: 
  break;
  }

  //state actions
  switch (state) {
  case SPAWN: 
  makeEntity(62, 66, 62, 66, 0xC0); //spawn 4x4 object
  objTracker[0][0] = 62;
  objTracker[0][1] = 66;
  objTracker[0][2] = 62;
  objTracker[0][3] = 66;
  break;

  case MOVE: //move object diagonally until SNES controller is implemented
    for(int i = 0; i < 1; i++) {
      for(int j = 0; j < 4; j++) {
        objTracker[i][j]+=1;
        if(objTracker[i][j] > 128) {
          objTracker[i][j] = 0;
        }
      }
    }
    break;

  default: 
  break;
  }

  return state;
}