#include <Wire.h> // J'avais mis des "" au lieu des <>
#define F_CPU 16000000UL
#include "stdio.h"
#include "stdlib.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
// Attention, j'ai gardé cette pin pour le moment dans le code mais je ne dois pas m'en servir

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void ConfigClkArd();
void TFTRELATED();
byte DataR[240];
byte DataR2[240];
int i = 0;
int i2 = 0;
int i3 =0;
int i4 =0;
bool PremLrecue = false;
bool BesImp = false;
short Color[240]; // Besoin de m'assurer que c'est pas la conversion implicite en paramètre dans le drawPixel qui fait ce bordel.


void setup()
{
  delay(500);
  Wire.begin(0x0B);              // join i2c bus with address 0x0B // Ca j’ai du la remettre :p
  Wire.setClock(400000);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);

  // JE N'AI DEFINITIVEMENT ACCES A LA FONCTION RECEIVE EVENT QUE QUAND JE N4AI PAS ENCORE FAIT LES DEUX FONCTIONS SUIVANTES   !!!

  TFTRELATED();

}


void loop()
{
  delay(100);
 if(BesImp == true)
  {
   for ( i3 = 0; i3<240; i3++)
    {
    //Serial.println(DataR[i2]);
     tft.drawPixel(i3,i4, Color[i3]);
      }
      BesImp = false;
      Serial.println(i4);
   }


}





void TFTRELATED()
{

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  uint16_t identifier = tft.readID();

  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  }

  tft.begin(identifier);
  tft.setRotation(0); // Place l'écran en position initial, le bord supérieur est celui qui est plein de pins
  tft.fillScreen(BLACK);
  tft.fillScreen(YELLOW);
  tft.fillScreen(BLACK);
  tft.fillScreen(BLUE);
  tft.fillScreen(RED);
  tft.fillScreen(YELLOW);
  Serial.flush();


}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{

   DataR[i] = Wire.read();
   Color[i] = (short)DataR[i];
   Serial.println(DataR[i]);

   //tft.drawPixel(i,i2,Color);
   i++;
   if(i==239)
   {
    i2++;
    i=0;
   // memcpy(Color,(short)DataR,240);
    i4=(i2-1);
   // PremLrecue = true;
    BesImp = true;
    //Serial.println(i2);
 // Serial.flush();
   }
    //
}
