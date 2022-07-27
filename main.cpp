
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String message = "";
BluetoothSerial SerialBT;

// Motor1 D2 D4 (GPIO2 GPIO4 ) [22 24] |  Motor 2 D18 D19 (GPIO18 GPIO19 ) [35 38]
// enA D21 (GPIO21)[42] |  enB D15 (GPIO15) [21]

// motor forwords - backwards
// Motor1 D2 D4 (GPIO2 GPIO4 ) [22 24]

// motor left - Right
// Motor 2 D18 D19 (GPIO18 GPIO19 ) [35 38]

// Motor A Forward/Backward connections
int enA = 21; // for speed control motor low
int in1 = 2;  // for direction control motor low
int in2 = 4;  // for direction control motor low
// Motor B Left/Right connections
int enB = 15; // for speed control motor high
int in3 = 18; // for direction control motor High
int in4 = 19; // for direction control motor

// int motorforword = 2;
// int motorbackword = 4;

// int motorleft = 18;
// int motorright = 19;

int state = HIGH;    // the current state of the output pin
char reading;        // the current reading from the input pin
char previous = LOW; // the previous reading from the input pin

String valor = "";

void setup()
{
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{

  if (SerialBT.available())
  {
    char val = SerialBT.read(); // reads the signal
    Serial.println(val);
    //

    switch (val)
    {
    case 'F':
      Aforward();
      break;
    case 'B':
      Abackward();
      break;
    case 'S':
      stopall();
      break;
    case 'R':
      Bright();
      break;
    case 'L':
      Bleft();
      break;
    case 'G':
      Aforward();
      Bleft();
      break;
    case 'I':
      Aforward();
      Bright();
      break;
    case 'H':
      Abackward();
      Bleft();
      break;
    case 'J':
      Abackward();
      Bright();
      break;
    }
  }
  delay(20);
}

void Aforward()
{

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}

void Abackward()
{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void Astop()
{

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}

void Bleft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
}

void Bright()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

void Bstop()
{

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}

void stopall()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
  analogWrite(enA, 0);
}
