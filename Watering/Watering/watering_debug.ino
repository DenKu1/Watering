#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS3231);

String wateringtime = "16-09";//Время полива
String Resettime = "16-11";//Время сброса
String hourminute = "";
int Relay = 4;//порт реле
int watering = 15000; //длительность полива
long previousMillis = 0;
long previousMillis1 = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
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
  if (millis() - previousMillis2 > 1000) {
    previousMillis2 = millis();
    Serial.println(time.gettime("d-m-Y, H:i:s, D"));
  }

  if (hourminute == Resettime && start == true)
  {
    today = false;
    finished = false;
    start = false;
    Serial.println("Сброс совершён");
  }

  if (hourminute == wateringtime && start == false)
  {
    start = true;
    Serial.println("Приступаю к поливке");
  }

  if (start == true && finished == false)
  {
    if (millis() - previousMillis1 > 1000) {
      previousMillis1 = millis();
      Serial.println("Полив...");
    }
    if (today == false)
    {
      digitalWrite(Relay, HIGH);   // реле включено
      previousMillis = millis();
      today = true;
    }

    if (millis() - previousMillis3 > 1000) {
      previousMillis3 = millis();
      Serial.println("Осталось:");
      Serial.println(  (  (watering - (millis() - previousMillis) )  / 1000));
    }

    if (millis() - previousMillis > watering)
    {
      Serial.println("Полив завершён");
      digitalWrite(Relay, LOW);  // реле выключено
      finished = true;


    }

  }


}

