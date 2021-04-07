

#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

//Q1 (Inputs)-----------------------------------------
//DigitalIn pusheenbutton_down(D8);
//DigitalIn pusheenbutton_up(D6);
//DigitalIn pusheenbutton_confirm(D5);
InterruptIn pusheenbutton_down(D8);
InterruptIn pusheenbutton_up(D6);
InterruptIn pusheenbutton_confirm(D5);
//---------------------------------------------
AnalogOut  aout(PA_4);//D7
//AnalogIn Ain(A0);
//DigitalOut led(LED1);
uLCD_4DGL uLCD(D1, D0, D2);

int x=1;
int x_confirmed=1;

void flip_up()
{
   if(x<4){
       x=x+1;
   }
}

void flip_down()
{
   if(x>1){
       x=x-1;
   }
}

void flip_confirm()
{
   x_confirmed = x;
}

int main()
{
    pusheenbutton_up.rise(&flip_up);
    pusheenbutton_down.rise(&flip_down);
    pusheenbutton_confirm.rise(&flip_confirm);
    while (1){
        ThisThread::sleep_for(1s);
    }
}