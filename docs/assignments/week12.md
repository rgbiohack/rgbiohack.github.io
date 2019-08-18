# 12. Output devices

Goal(s):

- Individual assignment:
  - Add an output device to a microcontroller board you've designed, and program it to do something

- Group assignment:
  - Measure the power consumption of an output device

## Research

For this assignment, I used an the Satshakit to test the output to a 4-pin LCD screen which I will be using in my Final project.

Due to my limitation in being able to assimilate Electronics assignments effectively I initially used commercial Arduino Boards initially anfd then progress to The Satshakit boards which is prgrammed using Arduino as an ISP.

As per the previous week's assignment, the input sensor was connected to the the Satshakit and the the output sensor used was the LCD Screen with a 4-pin I2C module that greatly simplifies the wiring of the LCD from 16 pins to 4 pins.

## Codes used

Code used

```
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
LiquidCrystal_I2C lcd(0x27,20,4);
OneWire  ds(2);


void setup() {
 lcd.init();
 lcd.backlight();
 lcd.print("Temperature.....");
delay(3000);
lcd.clear();
lcd.print("Starting.....");
delay(3000);
}
void loop() {
  byte i;
byte present = 0;
byte type_s;
byte data[12];
byte addr[8];
float celsius, fahrenheit;
if ( !ds.search(addr)) {
ds.reset_search();
delay(250);
return;
}
for ( i = 0; i < 8; i++) {
}
if (OneWire::crc8(addr, 7) != addr[7]) {
return;
}
// the first ROM byte indicates which chip
switch (addr[0]) {
case 0x10:
type_s = 1;
break;
case 0x28:
type_s = 0;
break;
case 0x22:
type_s = 0;
break;
default:
return;
}
ds.reset();
ds.select(addr);
ds.write(0x44, 1);        // start conversion, with parasite power on at the end
delay(1000);     // maybe 750ms is enough, maybe not
// we might do a ds.depower() here, but the reset will take care of it.
present = ds.reset();
ds.select(addr);
ds.write(0xBE);         // Read Scratchpad
for ( i = 0; i < 9; i++) {           // we need 9 bytes
data[i] = ds.read();
}
int16_t raw = (data[1] << 8) | data[0];
if (type_s) {
raw = raw << 3; // 9 bit resolution default
if (data[7] == 0x10) {
// "count remain" gives full 12 bit resolution
raw = (raw & 0xFFF0) + 12 - data[6];
}
} else {
byte cfg = (data[4] & 0x60);
// at lower res, the low bits are undefined, so let's zero them
if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
//// default is 12 bit resolution, 750 ms conversion time
}
celsius = (float)raw / 16.0;
fahrenheit = celsius * 1.8 + 32.0;
  delay(300);
  lcd.clear();
  
 lcd.setCursor(0,0);
  lcd.print("ICEICE BABY TEMP");
  lcd.setCursor(0,1);
  
  lcd.print(celsius);
  lcd.print("C:");
 
  lcd.setCursor(2,1);
 //lcd.print(set_temperature,1);
  lcd.setCursor(9,1);
  lcd.print(fahrenheit);
  lcd.print("F:");
  
 
 lcd.setCursor(11,1);
// lcd.print(temperature_read,1);
  
}
```

## Useful links

- [Jekyll](http://jekyll.org)
- [Google](http://google.com)
- [Markdown](https://en.wikipedia.org/wiki/Markdown)