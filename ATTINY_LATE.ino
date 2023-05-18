//Attiny85
// RST-|1     8|-VCC
// bom-|2     7|-L1
//  D7-|3     6|-D6
// GND-|4     5|-D5
#include <Arduino.h>
#include <Ds1302.h>
int PIN_RST = 0;
int PIN_CLK = 4;
int PIN_DAT = 1;
int relay = 3;
int cb = 2;
int giomo; int phutmo;
int phuttat;
int Ds = 0; //Tin hieu dieu khien LM393
Ds1302 rtc(PIN_RST, PIN_CLK, PIN_DAT);
// DS1302 RTC instance
void setup()
{
    pinMode(PIN_RST, INPUT);
    pinMode(PIN_DAT, INPUT);
    pinMode(PIN_CLK, INPUT);
    pinMode(relay, OUTPUT);
    pinMode(cb,INPUT);
    // initialize the RTC
    rtc.init();
    // test if clock is halted and set a date-time (see example 2) to start it
    Ds1302::DateTime dt = {
            .year = 0,
            .month = Ds1302::MONTH_OCT,
            .day = 0,
            .hour = 0,
            .minute = 0,
            .second = 0,
            .dow = Ds1302::DOW_TUE
        };
        rtc.setDateTime(&dt);
        giomo = dt.second; //cai gio mo hien tai
}

void loop()
{
//Ds1302
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    static uint8_t last_second = 0;
    if (last_second != now.second)
    {
        last_second = now.second;
    }
    phuttat = phutmo + 10; //mo Relay 10 phut
    if (now.minute == giomo + 1) //cach 4 gio thi mo may bom
    {
        digitalWrite(relay, HIGH);    // mo Relay
        phutmo = now.second; // set phut
        giomo = now.second; // set gio
        Ds = 1; //tin hieu khich hoat LM393
    }
    else if (now.second == phuttat) //mo bom trong 10 phut
    {
       digitalWrite(relay, LOW);      // Dong Relay
       Ds = 0;
    }
//Ds1302
//LM393
  int analog = analogRead(cb);
  int cov = map(analog, 0, 1023, 0, 100);
  int pt = 100 - cov;
  if(Ds != 1){
      if(pt >=40 ) //Do am lon hon 40% dong Relay
  {
     digitalWrite(relay,LOW);
  }
      else
  {
     digitalWrite(relay,HIGH);
  }}
//LM393    
  delay(1000);
}
