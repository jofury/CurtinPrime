#include "Arduino.h"
#include "Transformer.h"
/////////////////////
// Head motor
//
// dir >>> HIGH >>>> Down  /////  Max Up/Down 250
// dir >>> LOW >>>> Up     /////  Full range 500
//
// Neck motor
//
// DIR >>> HIGH >>>> Left  ////   Max left/right 500
// DIR >>> LOW >>>> Right  ////   Full range 1000
#define LEFT digitalWrite(_DIR, HIGH)
#define RIGHT digitalWrite(_DIR, LOW)
#define DOWN digitalWrite(_dir, HIGH)
#define UP digitalWrite(_dir, LOW)


#define _smallMotorOff  digitalWrite(_en, HIGH)
#define _bigMotorOff  digitalWrite(_EN, HIGH)
#define _smallMotorOn  digitalWrite(_en, LOW)
#define _bigMotorOn  digitalWrite(_EN, LOW)


#define _shieldOn digitalWrite(_shield, HIGH)
#define _shieldOff digitalWrite(_shield, LOW)

// Clibration switch
#define _cal A0 //Detect Low as activate

// Vip switch
#define _vip_vcc A14
#define _vip A15 //Detect Low as activate

//Fan mode
#define _shield 53


Transformer::Transformer(int en, int ms1, int ms2, int ms3, int stp, int dir,
                         int EN, int MS1, int MS2, int MS3, int STP, int DIR)
{
  ////VIP swicth
  pinMode(_vip, INPUT);
  pinMode(_vip_vcc, OUTPUT);
  digitalWrite(_vip_vcc, HIGH);
  //// Calibrate switch
  pinMode(_cal, INPUT);
//// VIP switch
  pinMode(_shield, OUTPUT);
  //// Small Stepper
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  pinMode(en, OUTPUT);
  //// Big Stepper
  pinMode(STP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);
  /// Enable 1/16 steps
  digitalWrite(ms1, HIGH);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);

  _en = en;
  _ms1 = ms1;
  _ms2 = ms2;
  _ms3 = ms3;
  _stp = stp;
  _dir = dir;
  _EN = EN;
  _MS1 = MS1;
  _MS2 = MS2;
  _MS3 = MS3;
  _STP = STP;
  _DIR = DIR;
}

void Transformer::run()
{
    digitalWrite(_stp,HIGH);
    delay(1);
    digitalWrite(_stp,LOW);
    delay(1);
}

void Transformer::RUN()
{
    digitalWrite(_STP,HIGH);
    delay(1);
    digitalWrite(_STP,LOW);
    delay(1);
}

void Transformer::run2()
{
    digitalWrite(_stp,HIGH);
    delay(1);
    digitalWrite(_stp,LOW);
    delay(1);
    digitalWrite(_STP,HIGH);
    delay(1);
    digitalWrite(_STP,LOW);
    delay(1);
}

void Transformer::headup(int steps)
{
  //digitalWrite(dir, LOW); // ClockWise
  UP;
  for(int x= 0; x<steps; x++)
  {
    run();
  }
}

void Transformer::headdown(int steps){
  //digitalWrite(dir, HIGH);
  DOWN;
  for(int x= 0; x<steps; x++)
  {
    run();
  }
}

void Transformer::neckright(int steps){
  RIGHT;
  for(int x= 0; x<steps; x++)
  {
    RUN();
  }
}

void Transformer::neckleft(int steps){
  //digitalWrite(DIR, HIGH);
  LEFT;
  for(int x= 0; x<steps; x++)
  {
    RUN();
  }
}

void Transformer::leftup(int steps){
  //digitalWrite(dir, LOW);
  //igitalWrite(DIR, HIGH);
  LEFT;
  UP;
  for(int x=0; x<steps; x++){
    run2();
  }
}

void Transformer::leftdown(int steps){
  //digitalWrite(dir, HIGH);
  //digitalWrite(DIR, HIGH);
  LEFT;
  DOWN;
  for(int x=0; x<steps; x++){
    run2();
  }
}

void Transformer::rightdown(int steps){
  //digitalWrite(dir, HIGH);
  //digitalWrite(DIR, LOW);
  RIGHT;
  DOWN;
  for(int x=0; x<steps; x++){
    run2();
  }
}

void Transformer::rightup(int steps)
{
  //digitalWrite(dir, LOW);
  //digitalWrite(DIR, LOW);
  RIGHT;
  UP;
  for(int x=0; x<steps; x++)
  {
    run2();
  }
}

void Transformer::headcalibrate()
{
  //digitalWrite(DIR, LOW);
  RIGHT;
  while(digitalRead(_cal)==HIGH)
  {
    RUN();
  }
  delay(100);
  Serial.println("Hello");
  //digitalWrite(DIR, HIGH);
  LEFT;
    for(int x=0; x<500; x++)
    {
        RUN();
    }
}

void Transformer::shield(bool on)
{
  if(on) _shieldOn;
  else _shieldOff;
}

void Transformer::headMotorOn(bool on)
{
  if(on) _smallMotorOn;
  else _smallMotorOff;
}

void Transformer::neckMotorOn(bool on)
{
  if(on) _bigMotorOn;
  else _bigMotorOff;
}

bool Transformer::isTime(char * day, char * hour_min, int start_time, int duration)
{
  char * split;
  char ** times = new char*[3];
  for(int q=0; q<3; ++q)
  {
    times[q] = new char[5];
  }
  split = strtok (hour_min,":");
  strcpy(times[0], split);
  int i = 1;
  while (split != NULL)
  {
    split = strtok (NULL, ":");
    times[i][0] = '\0';
    strcpy(times[i], split);
    i++;
  }
  if(day != "SATURDAY" && day != "SUNDAY")
  {
    Serial.println("It is the day");
    if(strtol(times[0], NULL, 10) == start_time)
    {
      Serial.println("Not time yet");
      if(strtol(times[1], NULL, 10) <= duration)
      {
        Serial.println("Running");
        delete[] split;
        for(int q=0; q<3; ++q)
        {
          delete[] times[q];
        }
        delete[] times;
        return true;
      }
    }
  }
  Serial.println("Not the day");
  delete[] split;
  for(int q=0; q<3; ++q)
  {
    delete[] times[q];
  }
  delete[] times;
  return false;
}

bool Transformer::VIP()
{
  if(digitalRead(_vip) == LOW) 
  {
    Serial.println("VIP Start!");
    return true;
  }
  return false;
}

