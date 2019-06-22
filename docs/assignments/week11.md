# 11. Input devices

Goal(s):

- Group assignment:
  - Probe an input device's analog levels and digital signals

- Individual assignment:
  - Measure something: add a sensor to a microcontroller board that you have designed and read it

## Research

For this assignment, I used an Arduino Uno to test the input to a Moisture Sensor which I will be using in my Final project.

Due to my limitation in being able to assimilate Electronics I have used commercial Arduino Boards.

Later as my progress into electronics progressed, I used the following [tutorial](http://www.theparsley.com/arduino/diy/) to produce my own Arduino boards for the Electronics Process


## Useful links

- [Jekyll](http://jekyll.org)
- [Google](http://google.com)
- [Markdown](https://en.wikipedia.org/wiki/Markdown)

## Code Example

Code used

```
int sensor_pin = A0;

int output_value ;

void setup() {

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

   }

void loop() {

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");

   delay(1000);

   }
```

## Gallery

![](../images/week11/1A.png)

![](../images/week11/1B.png)

![](../images/week11/1C.png)

![](../images/week11/1D.jpg)

![](../images/week11/1E.jpg)
