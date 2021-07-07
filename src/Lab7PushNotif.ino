/*
 * Project Lab7PushNotif
 * Description:
 * Author:
 * Date:
 */
SYSTEM_THREAD(ENABLED);
#include <blynk.h>
#include "oled-wing-adafruit.h"
OledWingAdafruit display;

//the variables
uint16_t reading;
double voltage;
double temperature;

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.

  Blynk.begin("vIEsJzXq3UHlk5uwXTEYiv53uXgHfv_q", IPAddress(167, 172, 234, 162), 9090);
  pinMode(A3, INPUT);

  display.setup();
  display.clearDisplay();
  display.display(); // cause the display to be updated
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");

  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.

  Blynk.run();
  display.loop();
  uint64_t reading = analogRead(A3);
  double voltage = (reading * 3.3) / 4095.0;
  double temperature = (voltage - 0.5) * 100;

  //print the temp
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Fahrenheit = ");
  display.print((temperature * 9 / 5) + 32);
  display.print("\n Celsius= ");
  display.print(temperature);
  display.display();

  if (display.pressedA())
  {
    display.clearDisplay(); //clears the display
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    Blynk.notify("Hey, you got a push notification"); //sends notif to blynk
    display.println("Push Sent"); 
    display.display(); // displays message
    delay(5000); //Wait five Seconds then goes back to temperature
    
  }
}