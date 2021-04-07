

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
AnalogIn Ain(A0);
//DigitalOut led(LED1);
uLCD_4DGL uLCD(D1, D0, D2);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue queue_push(32 * EVENTS_EVENT_SIZE);
EventQueue queue_sample(32 * EVENTS_EVENT_SIZE);
Thread thread;
Thread t;
Thread thread_for_sample;


int x=1;
int x_confirmed=1;
float ADCdata[3000];

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

/*void sample_waveform(){
    int r=0;
    int k=0;
    for(r=0; r<120; r=r+1){
        ADCdata[r]=3.3*Ain.read();
        printf("ADC: %f\r\n", 3.3*Ain.read());
        //r=r+1;
        ThisThread::sleep_for(1ms);
    }
    ThisThread::sleep_for(5s);
    for(k=0;k<2400;k=k+1){
        //printf("%d: %f\r\n", k,ADCdata[k]); 
        printf("%f\r\n", ADCdata[k]); 
    }
    
}*/

void generate_waveform(){
    uLCD.locate(1,3);
    uLCD.printf("Confirmed!\n");

    //queue_sample.call(sample_waveform);
    //int r=0;

    /*for (float i = 0.0f; i < 1.0f; i += 0.0125f) {  
            aout = i * 0.91f;                             
            if(x_confirmed==4){                                     
                ThisThread::sleep_for(1ms);             
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(50ms);
                wait_us(500);
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(14ms);
                wait_us(250);
            }else if(x_confirmed==1){
                //ThisThread::sleep_for(5ms);
                wait_us(125);
            }           
            //ADCdata[r]=3.3*Ain.read();
            //r=r+1;              
            
    }
    if(x_confirmed==4){                                     
        ThisThread::sleep_for(80ms);             
    }else if(x_confirmed==3){
        ThisThread::sleep_for(160ms);
    }else if(x_confirmed==2){
        ThisThread::sleep_for(200ms);
    }else if(x_confirmed==1){
        ThisThread::sleep_for(220ms);
    }


    for (float i = 1.0f; i > 0.0f; i -= 0.0125f) {  
            aout = i * 0.91f;                             
            if(x_confirmed==4){                                     
                ThisThread::sleep_for(1ms);             
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(50ms);
                wait_us(500);
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(14ms);
                wait_us(250);
            }else if(x_confirmed==1){
                //ThisThread::sleep_for(5ms);
                wait_us(125);
            }                                      
            
    }*/
int r=0;
    for (float i = 0.0f; i < 1.0f; ) {  
            aout = i * 0.91f;                             
            if(x_confirmed==4){                                     
                i += 0.00125f;             
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(50ms);
                i += 0.0025f;
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(14ms);
                i += 0.005f;
            }else if(x_confirmed==1){
                //ThisThread::sleep_for(5ms);
                i += 0.01f;
            }           
            ADCdata[r]=3.3*Ain.read();
            r=r+1;    
            wait_us(100);         
            
    }
    int j;
    if(x_confirmed==4){
        for(j=0;j<800;j=j+1){
            ADCdata[r]=3.3*Ain.read();
            r=r+1;
            wait_us(100);
        }                                     
        //ThisThread::sleep_for(80ms);             
    }else if(x_confirmed==3){
        for(j=0;j<1600;j=j+1){
            ADCdata[r]=3.3*Ain.read();
            r=r+1;
            wait_us(100);
        }
        //ThisThread::sleep_for(160ms);
    }else if(x_confirmed==2){
        for(j=0;j<2000;j=j+1){
            ADCdata[r]=3.3*Ain.read();
            r=r+1;
            wait_us(100);
        }
        //ThisThread::sleep_for(200ms);
    }else if(x_confirmed==1){
        for(j=0;j<2200;j=j+1){
            ADCdata[r]=3.3*Ain.read();
            r=r+1;
            wait_us(100);
        }
        //ThisThread::sleep_for(220ms);
    }


    for (float i = 1.0f; i > 0.0f; ) {  
            aout = i * 0.91f;                             
            if(x_confirmed==4){                                     
                i -= 0.00125f;             
            }else if(x_confirmed==3){
                //ThisThread::sleep_for(50ms);
                i -= 0.0025f;
            }else if(x_confirmed==2){
                //ThisThread::sleep_for(14ms);
                i -= 0.005f;
            }else if(x_confirmed==1){
                //ThisThread::sleep_for(5ms);
                i -= 0.01f;
            }           
            ADCdata[r]=3.3*Ain.read();
            r=r+1;    
            wait_us(100);         
            
    }
    for(int k=0;k<2400;k=k+10){
        //printf("%d: %f\r\n", k,ADCdata[k]); 
        printf("%f\r\n", ADCdata[k]); 
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
    thread_for_sample.start(callback(&queue_sample, &EventQueue::dispatch_forever));
    pusheenbutton_up.rise(&flip_up);
    pusheenbutton_down.rise(&flip_down);
    //pusheenbutton_confirm.rise(&flip_confirm);
    pusheenbutton_confirm.rise(&flip_confirm);
    while (1){
        ThisThread::sleep_for(1s);
    }
}