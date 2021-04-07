#include "mbed.h"
#include "uLCD_4DGL.h"
#include "mbed_events.h"
#include<iostream>
using namespace std::chrono;
using namespace std;

const double Amp = 56173;//65535;

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogIn Ain(A5);
//PwmOut Aout(D6);

DigitalIn goUp(A2);
DigitalIn goDn(A1);
DigitalIn Selet(A0);

AnalogOut aout(PA_4);

void print(int state);

EventQueue SampleQueue;
EventQueue eventQueue;

void gene(int state) {

    float periodArray[4] = {1.0, 1.0/2, 1.0/4, 1.0/8};
    int SectionLong[4] = {80, 40 ,20, 10};
    uint16_t Digit_signal = 0;

    while(1) {
        for(int i = 0; i < SectionLong[state]; i++) {
            Digit_signal = (uint16_t)(Amp * i/SectionLong[state]);   
            aout.write_u16(Digit_signal);
            ThisThread::sleep_for(1ms);
        }
        for(int i = 0; i < 240 - 2 * SectionLong[state]; i++) {
            Digit_signal = (uint16_t)(Amp);   
            aout.write_u16(Digit_signal);
            ThisThread::sleep_for(1ms);
        }
        for(int i = SectionLong[state]; i > 0; i--) {
            Digit_signal = (uint16_t)(Amp * i/SectionLong[state]);   
            aout.write_u16(Digit_signal);
            ThisThread::sleep_for(1ms);
        }
    }
}

int sample_fre = 500;
float ADCdata[500];

void sampling() {
    while(1) {

        for (int i = 0; i < sample_fre; i++){
            //Aout = Ain;
            ADCdata[i] = Ain;
            ThisThread::sleep_for(1000ms/sample_fre);
        }
        for (int i = 0; i < sample_fre; i++){
            cout << ADCdata[i] << " \r\n ";
            //printf("%f\r\n", ADCdata[i]);
        }
        ThisThread::sleep_for(5000ms);
    }
}



int main() 
{
    int state = 0;
    

    while(1) {
        if(Selet) {
            ThisThread::sleep_for(1ms);
            print(state);
            break;
        } else if(goUp) {
            if (state < 3) state++;  else state = state;
            print(state);
            ThisThread::sleep_for(1ms);
        } else if (goDn) {
            if (state > 0) state--;  else state = state;
            print(state);
            ThisThread::sleep_for(1ms);
        }
    }


    eventQueue.call(&gene, state);
    Thread eventThread(osPriorityNormal);
    eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

    SampleQueue.call(&sampling);
    Thread SamplingThread(osPriorityNormal);
    SamplingThread.start(callback(&SampleQueue, &EventQueue::dispatch_forever));

    while(1) {
        ThisThread::sleep_for(1ms);
    }
}

void print(int state) {
    uLCD.cls();
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n1, 1/2, 1/4, 1/8\n");
    uLCD.text_width(3);
    uLCD.locate(2, 5);

    switch (state)
    {
        case 0:
            uLCD.printf("\n1\n");
            break;
        case 1:
            uLCD.printf("\n1/2\n");
            break;
        case 2:
            uLCD.printf("\n1/4\n");
            break;
        case 3:
            uLCD.printf("\n1/8\n");
            break;
        default:
            uLCD.printf("\nerror\n");
    }
}
