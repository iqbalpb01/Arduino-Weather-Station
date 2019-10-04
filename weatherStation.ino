/*
 * Arduino Weather Station by filler
 * 
 * 
 */


#include<SPI.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

int buttonPin = 7;


//If you are using an SPI oled module, uncomment this block of code and connect accordingly
/*
#define oled_mosi 11
#define oled_clk 10
#define oled_dc 13
#define oled_reset 12
#define oled_cs 2

Adafruit_SSD1306 oled(oled_mosi,oled_clk,oled_dc,oled_reset,oled_cs);
*/

//If you are using an I2C oled module, uncomment this block of code and connect accordingly
/*
 * Connect the SCl and SDA pins to the respective SCL and SDA pins of your board
 * 
 * #define OLED_RESET 4
   Adafruit_SSD1306 oled(OLED_RESET);

 */


boolean state;



void setup() {
  
 
 oled.begin(SSD1306_SWITCHCAPVCC);
 oled.clearDisplay();
 oled.setTextColor(WHITE);
 oled.setTextSize(1);

 pinMode(buttonPin,INPUT_PULLUP);
 
 dht.begin();                        // this command initializes the dht module
 Serial.begin(9600);                 //innitiate Serial Communication
 

}

void loop() {
 
  Serial.print("humidity:",h);    //printing humidity on serial monnitor
  Serial.print("temprature:",t);  //printing temprature on serial monnitor


  oled.clearDisplay();
  
  float h = dht.readHumidity();
  float t;
  float hi;
 
  int mode = digitalRead(buttonPin);    //read the pushbutton

 if(mode == LOW)                        //change the state variable if there is a change in pushbutton
  {
    state = !state;
  }

  if(state == HIGH)                          //if state is high, display in celcius
 {
    t = dht.readTemperature();               //this function displays temperature in celsius
    hi = dht.computeHeatIndex(t, h, false);  //this function displays heat index in celsius

  }
  else if(state == LOW)                 //if state is low, display in fahrenheit
  {
   t = dht.readTemperature(true);       //if true is passed as an argument, returns temperature in fahrenheit
    hi = dht.computeHeatIndex(t, h);    // if false is not passed as an additionalargument, returns heat index in fahrenheit
  }

  oled.setCursor(1,1);
  oled.print("Humidity    : ");
  oled.print(h);
  oled.print(" %");
  oled.setCursor(1,11);
  oled.print("Temperature : ");
  oled.print(t);

  if(state == HIGH)                    // the same conditionals as above, to display the units of temperature
    oled.print(" C");
  else if(state == LOW)
    oled.print(" F"); 

  oled.setCursor(1,21);
  oled.print("Heat Index  : ");
  oled.print(hi);  

  if(state == HIGH)                   // the same conditionals as above, to display units of heat index
   oled.print(" C");
  else if(state == LOW)
    oled.print(" F"); 

  oled.display();

  delay(1000);
 
}
