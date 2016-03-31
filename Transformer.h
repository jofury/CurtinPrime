#ifndef Transformer_h
#define Transformer_h

#include "Arduino.h"

class Transformer
{
  public:
    Transformer(int en, int ms1, int ms2, int ms3, int stp, int dir,
                int EN, int MS1, int MS2, int MS3, int STP, int DIR);
    /*
      Transformer constructor, enable the code to be generic, possible to use on other MCUs
        - Input is the motor driver pins
    */
    void headup(int steps);
    /*
      Move the head up ONLY with the input steps 
        - Full range is 500
        - Up 250 and down 250
    */
    void headdown(int steps);
    /*
      Moves the head down
    */
    void headcalibrate();
    /*
      Do calibration with the homing system in the head.
        - The head will turn right until click the switch and the to the center which is at position 250
    */
    void neckleft(int steps);
    void neckright(int steps);
    void leftup(int steps);
    void leftdown(int steps);
    void rightup(int steps);
    void rightdown(int steps);
    void shield(bool on);
    void headMotorOn(bool on);
    void neckMotorOn(bool on);
    bool isTime(char * day, char * str, int start_time, int duration);
    bool VIP();
    void eyeinit();
    

  private:
  /*
    Private stuff, user in main cannot use this premitive functions!
    */
    int _en;
    int _ms1;
    int _ms2;
    int _ms3;
    int _stp;
    int _dir;
    int _EN;
    int _MS1;
    int _MS2;
    int _MS3;
    int _STP;
    int _DIR;
    void run();
    void RUN();
    void run2();
    void RUN2();
};

#endif
