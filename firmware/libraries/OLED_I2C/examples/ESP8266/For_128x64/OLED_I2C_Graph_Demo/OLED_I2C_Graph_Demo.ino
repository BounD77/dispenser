// OLED_I2C_Graph_Demo
// Copyright (C)2019 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// **********************************************
// *** This demo is for 128x64 pixel displays ***
// **********************************************
//
// A quick demo of how to use my OLED_I2C library.
//
// Remember to use external pull-up resistors on the data and clock signals 
// if they are required.
//
// You can connect the OLED display to any available pin. The library will
// use the Wire library for display communication.
//

#include <OLED_I2C.h>

OLED  myOLED(D2, D1); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t logo[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

void setup()
{
  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  myOLED.setFont(SmallFont);
  randomSeed(analogRead(7));
}

void loop()
{
  myOLED.clrScr();
  myOLED.drawBitmap(0, 16, logo, 128, 36);
  myOLED.update();

  delay(3000);
  
  myOLED.clrScr();
  myOLED.print("OLED_I2C", CENTER, 0);
  myOLED.print("DEMO", CENTER, 28);
  myOLED.drawRect(50, 26, 78, 36);
  for (int i=0; i<6; i++)
  {
    myOLED.drawLine(79, 26+(i*2), 105-(i*3), 26+(i*2));
    myOLED.drawLine(22+(i*3), 36-(i*2), 50, 36-(i*2));
  }
  myOLED.print("(C)2019 by", CENTER, 48);
  myOLED.print("Henning Karlsen", CENTER, 56);
  myOLED.update();

  delay(5000);
  
  myOLED.clrScr();
  for (int i=0; i<64; i+=4)
  {
    myOLED.drawLine(0, i, 127, 63-i);
    myOLED.update();
  }
  for (int i=127; i>=0; i-=4)
  {
    myOLED.drawLine(i, 0, 127-i, 63);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 63);
  for (int i=0; i<64; i+=4)
  {
    myOLED.drawLine(0, i, i*2, 63);
    myOLED.update();
  }
  for (int i=0; i<64; i+=4)
  {
    myOLED.drawLine(127, 63-i, 127-(i*2), 0);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<10; i++)
  {
    myOLED.drawRoundRect(i*3, i*3, 127-(i*3), 63-(i*3));
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<25; i++)
  {
    myOLED.drawCircle(64, 32, i*3);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 63);
  myOLED.drawLine(0, 31, 127, 31);
  myOLED.drawLine(63, 0, 63, 63);
  for (int c=0; c<2; c++)
  {
    for (int i=0; i<128; i++)
    {
      y=i*0.04974188368183839294232518690191;
      myOLED.invPixel(i, (sin(y)*28)+31);
      myOLED.update();
      delay(10);
    }
  }

  delay(2000);

  for (int pc=0; pc<2; pc++)
  {
    pacy=random(0, 44);
  
    for (int i=-20; i<132; i++)
    {
      myOLED.clrScr();
      for (int p=6; p>((i+20)/20); p--)
        myOLED.drawBitmap(p*20-8, pacy+7, pill, 5, 5);
      switch(((i+20)/3) % 4)
      {
        case 0: bm=pacman1;
                break;
        case 1: bm=pacman2;
                break;
        case 2: bm=pacman3;
                break;
        case 3: bm=pacman2;
                break;
      }
      myOLED.drawBitmap(i, pacy, bm, 20, 20);
      myOLED.update();
      delay(10);
    }
  }

  for (int i=0; i<41; i++)
  {
    myOLED.clrScr();
    myOLED.drawBitmap(22, i-24, The_End, 84, 24);
    myOLED.update();
    delay(50);
  }
  myOLED.print("Runtime (ms):", CENTER, 48);
  myOLED.printNumI(millis(), CENTER, 56);
  myOLED.update();
  for (int i=0; i<5; i++)
  {
    myOLED.invert(true);
    delay(1000);
    myOLED.invert(false);
    delay(1000);
  }
}
