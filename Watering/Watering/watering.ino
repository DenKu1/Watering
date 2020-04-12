#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS3231);

String wateringtime = "21-22";//Время полива
String Resettime = "21-24";//Время сброса
String hourminute = "";
int Relay = 4;//порт реле
int watering = 25000; //длительность полива
long previousMillis = 0;

bool today = false;
bool finished = false;
bool start = false;

void setup() {
  delay(300);
  Serial.begin(9600);
  time.begin();
  //time.settime(0,54,16,6,8,18,1);  // 0  сек, 51 мин, 21 час, 27, октября, 2015 года, вторник
  pinMode(Relay, OUTPUT);//установка реле
}
void loop() {
  hourminute = time.gettime("H-i");
  
    if (hourminute == Resettime && start == true)
  {
    today = false;
    finished = false;
    start = false;
      }

  if (hourminute == wateringtime && start == false)
  {
    start = true;
      }

  if (start == true && finished == false)
  {
    
    if (today == false)
    {
      digitalWrite(Relay, HIGH);   // реле включено
      previousMillis = millis();
      today = true;
    }
   
    if (millis() - previousMillis > watering)
    {
      digitalWrite(Relay, LOW);  // реле выключено
      finished = true;


    }

  }


}

