#include <Wire.h> //dodaje bibliotekę odpowiedzialną za interfejs 1-wire
#include <OneWire.h> //dodaje bibliotekę odpowiedzialną za interfejs 1-wire
#include <DallasTemperature.h> //dodaje bibliotekę odpowiedzialną za obsługę czujnika temperatury
#include <TimerOne.h> //dodaje bibliotekę odpowiedzialną za przerwanie 
void Wyswietlacz(void);
#include "SevSeg.h" //dodaje bibliotekę odpowiedzialną za obsługe wyświetlacza
SevSeg sevseg;
int temp;
float tempC; //zmienna temperatury 
boolean stan; /zmienna odpowiedzialna za zmianę jednostki 
#define ONE_WIRE_BUS 13 //zdefiniowanie pinu odpowiedzialnego za komunikację 1-wire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup() {
 
pinMode(12, INPUT_PULLUP); //zdefiniowanie pinu do którego podłączony jest przycisk
  sensors.begin();//włączenie czujnika
stan=true;
     byte numDigits = 4;   //konfiguracja wyświetlacza
byte digitPins[] = {8, 9,10,11}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
   byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6}; //Segments: A,B,C,D,E,F,G,Period
bool resistorsOnSegments = true; // Use 'true' if on digit pins
byte hardwareConfig = N_TRANSISTORS;
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins,resistorsOnSegments, updateWithDelays, leadingZeros);
  //Ustawienie przerwania 
  Timer1.initialize(1000);
  //Przyczepienie funkcji Wyswietlacz do timera1
  Timer1.attachInterrupt(Wyswietlacz);
}

void loop() {
  if (digitalRead(12) == LOW) { //Jeśli przycisk wciśnięty
    stan=!stan; //zmiana stanu zmiennej odpowiedzialnej za jednostkę 
    delay(40);
 
  }
 
  sensors.requestTemperatures(); 
 if(stan==true){                 //temperatura w C jeśli zmienna stan=1
 temp = sensors.getTempCByIndex(0); //odczytanie temepratury 
 }
if(stan==false){                //temperatura w F jeśli zmienna stan=0
 tempC = sensors.getTempCByIndex(0); //odczytanie temepratury 
 temp = DallasTemperature::toFahrenheit(tempC); //zmiana jednostki
}
 
 
}
void Wyswietlacz() {
 
 
  sevseg.setNumber(temp,1); //wyświetlanie temepratury
  sevseg.refreshDisplay();

     
}
//end
