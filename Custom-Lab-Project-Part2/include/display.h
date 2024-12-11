#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "helper.h"
#include "spiAVR.h"

//functions to write onto 128x128 LCD display

void data_command(bool set) {
  PORTB = SetBit(PORTB, 1, set); //1 means data, 0 means command
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

void HardwareReset() {
  //set reset pin to low
  PORTB = SetBit(PORTB, 0, 0);
  _delay_ms(200);
  //set reset pin to high
  PORTB = SetBit(PORTB, 0, 1);
  _delay_ms(200);
}

void ST7735_init() {
  HardwareReset();
  command(0x01); //SWERESET
  _delay_ms(150); 
  command(0x11); //SLPOUT
  _delay_ms(200);
  // command(0x0C); //RDD COLMOD
  command(0x3A); //COLMOD
  // data(0x06); //18 bit color mode
  data(0x03); //12 bit color mode 
  _delay_ms(10);
  command(0x29); //DISPON
  _delay_ms(200);
}

void setColor(int color) {
  data_command(true);
  setSS(false);
  SPI_SEND((color & 0xF00)>>8);
  SPI_SEND((color & 0x0F0)>>4);
  SPI_SEND(color & 0x00F);
  setSS(true);
}

void makeEntity(int startX, int finalX, int startY, int finalY, int color) { 
    //startX <= finalX
    //startY <= finalY

    command(0x2A); //CASET, sets column address
    data(0x00); //starting X bits 15-8
    data(startX); //starting X bits 7-0
    data(0x00); //ending X bits 15-8
    data(finalX); //ending X bits 7-0

    command(0x2B); //RASET, sets row address
    data(0x00); //starting Y bits 15-8
    data(startY); //starting Y bits 7-0
    data(0x00); //ending Y bits 15-8
    data(finalY); //ending Y bits 7-0

    command(0x2C); //RAMWR, memory write

    for(int i = 0; i <= 250; i++) { //i and j were 0
      for(int j = 0; j <= 250; j++) {
        setColor(color);
      }
    }
}

void referenceSpawn() { 
    makeEntity(2, 10, 1, 9, 0xF00); //pixel at top left corner     F00 is green
    makeEntity(121,129, 1,9, 0x0F0); //pixel at top right corner     0F0 is blue
    makeEntity(2, 10, 120, 128, 0x00F); //pixel at bottom left corner    00F is red
    makeEntity(121,129, 120, 128, 0xFFF); //pixel at bottom right corner   FFF is white
}

void deleteEntity(int startX_old, int finalX_old, int startY_old, int finalY_old) { //blacks out old positions
    command(0x2A); //CASET, sets column address
    data(0x00); //starting X bits 15-8
    data(startX_old); //starting X bits 7-0

    data(0x00); //ending X bits 15-8
    data(finalX_old); //ending X bits 7-0

    command(0x2B); //RASET, sets row address
    data(0x00); //starting Y bits 15-8
    data(startY_old); //starting Y bits 7-0

    data(0x00); //ending Y bits 15-8
    data(finalY_old); //ending Y bits 7-0

    command(0x2C); //RAMWR, memory write

    data_command(true);
    setSS(false);

    for(int i = 0; i <= (128); i++) { //i and j were 0
      for(int j = 0; j <= (128); j++) {
        SPI_SEND(0x00);
      }
    }

    setSS(true);
}

#endif /* _ST7735AVR_H_ */