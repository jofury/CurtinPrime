//////////////////////////////
///  IEEE Curtin Prime Project
///    by Technical Division
///     Author: jojo

#include "Tlc5940.h"
#include "tlc_fades.h"
#include "DS3231.h"
#include "Transformer.h"
#include <avr/wdt.h>

#define day rtc.getDOWStr()
#define hour_min rtc.getTimeStr()
/*************************************
Set the start time here
*************************************/
#define start_time 12 // Time in 24 Hr <--- Edit the value
#define duration 5

// HEADMOTOR
#define en  30
#define ms1 32
#define ms2 34
#define ms3 36
#define stp 38
#define dir 40

// NECKMOTOR
#define EN  31
#define MS1 33
#define MS2 35
#define MS3 37
#define STP 39
#define DIR 41
/////////////////////////
DS3231 rtc(SDA, SCL);
Transformer curtinPrime( en,  ms1,  ms2,  ms3,  stp,  dir,
                          EN,  MS1,  MS2,  MS3,  STP,  DIR);
void setup()
{
  Serial.begin(57600);
  wdt_disable();
  rtc.begin();
  Tlc.init();
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(3, 14, 2016);   // Set the date to January 1st, 2014

  /// Initiate the Transformer
  curtinPrime.headMotorOn(false);
  curtinPrime.neckMotorOn(false);
  curtinPrime.shield(false);
  Tlc.clear();
  delay(100);
  Tlc.update();
  delay(100);
  wdt_enable(WDTO_4S);
  //////////////////
}

void loop()
{
  bool init = false;
  bool vip_start = false;
  wdt_reset();
  if(curtinPrime.VIP()) vip_start = true;
    while(curtinPrime.isTime(day, hour_min, start_time, duration) || vip_start)
    {
      wdt_disable();
      if(!init)
      {
        
        curtinPrime.shield(true);
        Serial.println("Calibrating");
        curtinPrime.headMotorOn(true);
        curtinPrime.neckMotorOn(true);
        curtinPrime.headup(250);
        delay(100);
        eyeinit();
        delay(100);
        curtinPrime.headcalibrate();
        delay(100);
        init = true;
        vip_start = false;
      }
      Serial.println("Animation Start");
      /***********************************************************
       *  Main function here
       *  ** Preset is the stock function build in the transformer program
       */
       
      preset();

      /************************************************************
       * Fucntion end here
       */
    }
    if(init)
    {
      curtinPrime.headdown(250);
      delay(100);
      wdt_enable(WDTO_4S);
    }
    curtinPrime.shield(false);
    curtinPrime.headMotorOn(false);
    curtinPrime.neckMotorOn(false);
    Tlc.clear();
    delay(100);
    Tlc.update();
    delay(100);
    Serial.println("Idle Mode");
}

void preset()
{
  blueeye();
  delay(1000);
  curtinPrime.leftup(250);
  delay(100);
  curtinPrime.leftdown(250);
  delay(100);
  curtinPrime.headdown(100);
  pupilgreen();
  delay(500);
  curtinPrime.neckleft(100);
  pupilgreen();
  delay(2000);
  pupilgreen();
  delay(500);
  curtinPrime.neckright(100);
  pupilgreen();
  delay(2000);
  blueeye();
  curtinPrime.headup(100);
  delay(500);
  curtinPrime.rightdown(250);
  delay(100);
  curtinPrime.rightup(250);
  delay(100);
  curtinPrime.neckright(500);
  delay(500);
  curtinPrime.neckleft(500);
  delay(500);
  curtinPrime.leftup(300);
  delay(500);
  curtinPrime.neckright(600);
  delay(500);
  curtinPrime.neckleft(300);
  delay(500);
  curtinPrime.headdown(350);
  delay(500);
}

void eyeinit()
{

  for(int channel = 0; channel < 48; channel++)
  {
    Tlc.clear();
    Tlc.set(channel, 4095);
    Tlc.set(channel + 1, 1000);
    Tlc.update();
     delay(200);
  }

  for(int channel = 47; channel >=0 ; channel--)
  {
    Tlc.clear();
    Tlc.set(channel, 4095);
    Tlc.update();
     delay(100);
  }

  Tlc.clear();
  for(int channel = 0; channel < 16; channel++)
  {
    Tlc.set(channel, 4095);
    Tlc.set(channel + 1, 1000);
    Tlc.update();
    delay(100);
  }
}

void greeneye()
{
  Tlc.clear();
  for(int channel = 16; channel < 32; channel++)
  {

    Tlc.set(channel, 4095);
    Tlc.set(channel + 1, 1000);
  }
  Tlc.update();
}

void blueeye()
{
  Tlc.clear();
  for(int channel = 32; channel < 48; channel++)
  {

    Tlc.set(channel, 4095);
    Tlc.set(channel + 1, 1000);
  }
  Tlc.update();
}

void pupilgreen()
{
  Tlc.clear();
  for(int channel = 16; channel < 32; channel++)
  {
    Tlc.set(channel, 4095);
  }
  Tlc.update();
  delay(100);

  Tlc.clear();
    Tlc.set(16, 1000);
    Tlc.set(17, 1000);
    Tlc.set(18, 1000);
    Tlc.set(19, 4095);
    Tlc.set(20, 4095);
    Tlc.set(21, 1000);
    Tlc.set(22, 1000);
    Tlc.set(23, 4095);
    Tlc.set(24, 4095);
    Tlc.set(25, 1000);
    Tlc.set(26, 1000);
    Tlc.set(27, 4095);
    Tlc.set(28, 4095);
    Tlc.set(29, 1000);
    Tlc.set(30, 1000);
    Tlc.set(31, 1000);
    Tlc.update();
    delay(100);

    Tlc.clear();
     Tlc.set(19, 4095);
    Tlc.set(20, 4095);
     Tlc.set(23, 4095);
    Tlc.set(24, 4095);
    Tlc.set(27, 4095);
    Tlc.set(28, 4095);
    Tlc.update();
    delay(100);

    Tlc.clear();
    Tlc.set(16, 1000);
    Tlc.set(17, 1000);
    Tlc.set(18, 1000);
    Tlc.set(19, 4095);
    Tlc.set(20, 4095);
    Tlc.set(21, 1000);
    Tlc.set(22, 1000);
    Tlc.set(23, 4095);
    Tlc.set(24, 4095);
    Tlc.set(25, 1000);
    Tlc.set(26, 1000);
    Tlc.set(27, 4095);
    Tlc.set(28, 4095);
    Tlc.set(29, 1000);
    Tlc.set(30, 1000);
    Tlc.set(31, 1000);
    Tlc.update();
    delay(100);
    Tlc.clear();
  for(int channel = 16; channel < 32; channel++)
  {
    Tlc.set(channel, 4095);
  }
  Tlc.update();
}


