#include <Arduino.h>
#include <Joystick.h>
#include <FUTABA_SBUS.h>
// #include <Streaming.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_MULTI_AXIS,
  2, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  true, true,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

FUTABA_SBUS sBus;

void setup() {

  //Set pinout
  pinMode(8, OUTPUT);
  // Configure JoyStick
  Joystick.setXAxisRange(174,1808);
  Joystick.setYAxisRange(174,1808);
  Joystick.setRxAxisRange(174,1808);
  Joystick.setRyAxisRange(174,1808);
  Joystick.setRudderRange(174,1808);
  Joystick.setThrottleRange(174,1808);
  
  // Begin!!!
  Joystick.begin();
  sBus.begin();
}

int i = 0;

void loop() {
  sBus.FeedLine();
  if (sBus.toChannels == 1){
    sBus.UpdateChannels();
    sBus.toChannels = 0; 

    // Update channels
    Joystick.setXAxis(sBus.channels[3]);
    Joystick.setYAxis(sBus.channels[2]);
    Joystick.setRxAxis(sBus.channels[0]);
    Joystick.setRyAxis(sBus.channels[1]);
    Joystick.setRudder(sBus.channels[5]);
    Joystick.setThrottle(sBus.channels[6]);
    Joystick.setButton(0,sBus.channels[4]);
    Joystick.setButton(1,sBus.channels[7]);

    if (sBus.channels[4] > 500 || sBus.channels[7] > 500){
      digitalWrite(8, HIGH);
    }
    else{
      digitalWrite(8, LOW);
    }
  }
} 