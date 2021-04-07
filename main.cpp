

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
EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue queue_push(32 * EVENTS_EVENT_SIZE);
Thread thread;
Thread t;


int x=1;
int x_confirmed=1;

void pusheenbutton_thread()
{
    //while (true)
   //{
    if(x == 1){
        uLCD.locate(1,1);
        uLCD.printf("slew rates: 1/8\n");
    }else if(x == 2){
        uLCD.locate(1,1);
        uLCD.printf("slew rates: 1/4\n");
    }else if(x == 3){
        uLCD.locate(1,1);
        uLCD.printf("slew rates: 1/2\n");
    }else if(x == 4){
        uLCD.locate(1,1);
        uLCD.printf("               \n");
        uLCD.locate(1,1);
        uLCD.printf("slew rates: 1\n");
    }
   //}
}

void flip_up()
{
   if(x<4){
       x=x+1;
   }
   queue_push.call(pusheenbutton_thread);
}

void flip_down()
{
   if(x>1){
       x=x-1;
   }
   queue_push.call(pusheenbutton_thread);
}

void generate_waveform(){
    uLCD.locate(1,3);
    uLCD.printf("Confirmed!\n");

    for (float i = 0.0f; i < 1.0f; i += 0.0125f) {  
            aout = i * 0.91f;                             
            if(x_confirmed==1){                                     
                ThisThread::sleep_for(1ms);             
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(50ms);
                wait_us(500);
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(14ms);
                wait_us(250);
            }else if(x_confirmed==4){
                //ThisThread::sleep_for(5ms);
                wait_us(125);
            }                                      
            
    }
    if(x_confirmed==1){                                     
        ThisThread::sleep_for(80ms);             
    }else if(x_confirmed==2){
        ThisThread::sleep_for(160ms);
    }else if(x_confirmed==3){
        ThisThread::sleep_for(200ms);
    }else if(x_confirmed==4){
        ThisThread::sleep_for(220ms);
    }
    for (float i = 1.0f; i > 0.0f; i -= 0.0125f) {  
            aout = i * 0.91f;                             
            if(x_confirmed==1){                                     
                ThisThread::sleep_for(1ms);             
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(50ms);
                wait_us(500);
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(14ms);
                wait_us(250);
            }else if(x_confirmed==4){
                //ThisThread::sleep_for(5ms);
                wait_us(125);
            }                                      
            
    }
}


void flip_confirm()
{
   x_confirmed = x;
   queue.call(generate_waveform);
}

int main()
{
    //thread.start(pusheenbutton_thread);
    thread.start(callback(&queue_push, &EventQueue::dispatch_forever));
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    pusheenbutton_up.rise(&flip_up);
    pusheenbutton_down.rise(&flip_down);
    //pusheenbutton_confirm.rise(&flip_confirm);
    pusheenbutton_confirm.rise(&flip_confirm);
    while (1){
        ThisThread::sleep_for(1s);
    }
}