#include "DHT.h"
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#define DHTPIN D2 // IMPORTANT D2 on NodeMCU is GPIO 4

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

const char *ssid = "Redmi"; // Your wifi ssid
const char *password = "96639B53"; //Your wifi password

unsigned long myChannelNumber = 810981;
const char * myWriteAPIKey = "AHW1LTDYQPQ4ZC8Z";

const char* server = "api.thingspeak.com";

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);

void updateThingSpeak(float t, float h){
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
    
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    dht.begin();
    ThingSpeak.begin(client);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("waiting for wifi to be connected");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(2000);
    float h = dht.readHumidity();
    //celcius
    float t = dht.readTemperature();
    //fahrenheit
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Compute heat index in Fahrenheit (the default)
   
   
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("\n");
    ThingSpeak.writeField(myChannelNumber, 1,t, myWriteAPIKey); //Update in ThingSpeak
    delay(100);
    
     Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("\n");
    ThingSpeak.writeField(myChannelNumber, 2,h, myWriteAPIKey); //Update in ThingSpeak
    delay(100);
 
 
    
    if(client.connect(server,80)){
        updateThingSpeak(t,h);
    }
}
