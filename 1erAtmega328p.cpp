#define F_CPU 16000000UL
#include "stdio.h"
#include "stdlib.h"
#include <Wire.h>
// Bonjour, je suis un teste d'ajout de code.
byte Lu;

void setup ()
{
    delay(1000);
     Wire.begin();
     Wire.setClock(100000);
     Serial.begin(115200);
     delay(1000);

//RegConfigOrigin();
ConfigRegOVI2C_QVGA_YUV();







    TCCR1A = ( (1 << COM1B0));// Toggle OC1B (PB2) on compare match // QUAND CES DEUX LA NE SONT PAS SUR LA MËME LIGNE CA FAIT DE LA MERDE
    TCCR1B = ((1 << WGM12) | (1 << CS10)); // Active CTC & Prescal à 1
    TIMSK1 = 0; // Des&ctive tout le registre des interrupts
    OCR1A = 3; // le toggle sur output compare match se fait lorsque le counteur atteind 3, redémarre à 0
    //DDRB |= (1<<PB1); // Met le PB1 en sortie qui correspond à OC1A qui va toggle
    DDRB |= (1<<PB2); // Met aussi PB2 en sortie qui correspond à OC1B qui va toggle
    sei(); // Active les interruptions également
    TCNT1 = 0;
    Serial.println("Clk Réglée");


  }

  void loop()
  {

   // Serial.println(Lu);
  //  while(1);

    }

int arduino_i2c_read(byte address, byte reg, byte value)
  {

    Serial.print("arduino_i2c_read: address = 0x");
    Serial.print(address, HEX);
    Serial.print(", reg = 0x");
    Serial.print(reg, HEX);


    Wire.beginTransmission(address);
    Wire.write(reg);
    if (Wire.endTransmission() != 0) {
    Serial.println();
      return -1;
    }

    if (Wire.requestFrom(address, 1) != 1) {
      Serial.println();
      return -1;
    }

    value = Wire.read();


    Serial.print(", value = 0x");
    Serial.println(value, HEX);

    return 0;
  }

  int arduino_i2c_write(byte address, byte reg, byte value)
  {

    Serial.print("arduino_i2c_write: address = 0x");
    Serial.print(address, HEX);
    Serial.print(", reg = 0x");
    Serial.print(reg, HEX);
    Serial.print(", value = 0x");
    Serial.println(value, HEX);


    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);

    if (Wire.endTransmission() != 0) {
      return -1;
      Serial.println("error");
    }

    return 0;
  }

  void ConfigRegOVI2C_QVGA_YUV()
  {

    arduino_i2c_read(0x21,0x3E,Lu); // Scaling PCLK enable + Scaling parameter can be adjusted manually + PCLK Divisé par 2
    arduino_i2c_read(0x21,0x72,Lu);
    arduino_i2c_read(0x21,0x73,Lu); // Même chose que 0x3E
    arduino_i2c_read(0x21,0x17,Lu); // Conf HSTART
    arduino_i2c_read(0x21,0x18,Lu); // Conf HSTOP
    arduino_i2c_read(0x21,0x32,Lu); // Conf HREF
    arduino_i2c_read(0x21,0x19,Lu); // Conf VSTART
    arduino_i2c_read(0x21,0x1A,Lu); // Conf VSTOP
    arduino_i2c_read(0x21,0x03,Lu); // Conf VREF
    arduino_i2c_read(0x21,0xff,Lu); // Conf VREF


    arduino_i2c_write(0x21,0x3E,0x19); // Scaling PCLK enable + Scaling parameter can be adjusted manually + PCLK Divisé par 2
    arduino_i2c_write(0x21,0x72,0x11);
    arduino_i2c_write(0x21,0x73,0xF1); // Même chose que 0x3E
    arduino_i2c_write(0x21,0x17,0x16); // Conf HSTART
    arduino_i2c_write(0x21,0x18,0x04); // Conf HSTOP
    arduino_i2c_write(0x21,0x32,0x24); // Conf HREF
    arduino_i2c_write(0x21,0x19,0x02); // Conf VSTART
    arduino_i2c_write(0x21,0x1A,0x7A); // Conf VSTOP
    arduino_i2c_write(0x21,0x03,0x0A); // Conf VREF
    arduino_i2c_write(0x21,0xff,0xff); // Conf VREF
    // Configuration en QVGA

    arduino_i2c_read(0x21,0x3E,Lu); // Scaling PCLK enable + Scaling parameter can be adjusted manually + PCLK Divisé par 2
    arduino_i2c_read(0x21,0x72,Lu);
    arduino_i2c_read(0x21,0x73,Lu); // Même chose que 0x3E
    arduino_i2c_read(0x21,0x17,Lu); // Conf HSTART
    arduino_i2c_read(0x21,0x18,Lu); // Conf HSTOP
    arduino_i2c_read(0x21,0x32,Lu); // Conf HREF
    arduino_i2c_read(0x21,0x19,Lu); // Conf VSTART
    arduino_i2c_read(0x21,0x1A,Lu); // Conf VSTOP
    arduino_i2c_read(0x21,0x03,Lu); // Conf VREF
    arduino_i2c_read(0x21,0xff,Lu); // Conf VREF


    arduino_i2c_read(0x21,0x12,Lu); // COM7
    arduino_i2c_read(0x21,0x8C,Lu); // RGB444
    arduino_i2c_read(0x21,0x04,Lu); // COM1
    arduino_i2c_read(0x21,0x40,Lu); // COM15
    arduino_i2c_read(0x21,0x14,Lu); // COM9
    arduino_i2c_read(0x21,0x4f,Lu); // C
    arduino_i2c_read(0x21,0x50,Lu); // C
    arduino_i2c_read(0x21,0x51,Lu); // C
    arduino_i2c_read(0x21,0x52,Lu); // C
    arduino_i2c_read(0x21,0x53,Lu); // C
    arduino_i2c_read(0x21,0x54,Lu); // C
    arduino_i2c_read(0x21,0x3d,Lu); // COM13
    arduino_i2c_read(0x21,0xff,Lu); // C


    arduino_i2c_write(0x21,0x12,0x10); // COM7 YUV ACTIVE et QVGA Sélectionné
    arduino_i2c_write(0x21,0x8C,0x00); // RGB444 desactivé
    arduino_i2c_write(0x21,0x04,0x00); // COM1
    arduino_i2c_write(0x21,0x40,0xC0); // COM15
    arduino_i2c_write(0x21,0x14,0x6A); // COM9
    arduino_i2c_write(0x21,0x4f,0x80); // C
    arduino_i2c_write(0x21,0x50,0x80); // C
    arduino_i2c_write(0x21,0x51,0x00); // C
    arduino_i2c_write(0x21,0x52,0x22); // C
    arduino_i2c_write(0x21,0x53,0x5E); // C
    arduino_i2c_write(0x21,0x54,0x80); // C
    arduino_i2c_write(0x21,0x3d,0x40); // COM13
    arduino_i2c_write(0x21,0xff,0xFF); // C
    //YUV422 MODE

    arduino_i2c_read(0x21,0x12,Lu); // COM7
    arduino_i2c_read(0x21,0x8C,Lu); // RGB444
    arduino_i2c_read(0x21,0x04,Lu); // COM1
    arduino_i2c_read(0x21,0x40,Lu); // COM15
    arduino_i2c_read(0x21,0x14,Lu); // COM9
    arduino_i2c_read(0x21,0x4f,Lu); // C
    arduino_i2c_read(0x21,0x50,Lu); // C
    arduino_i2c_read(0x21,0x51,Lu); // C
    arduino_i2c_read(0x21,0x52,Lu); // C
    arduino_i2c_read(0x21,0x53,Lu); // C
    arduino_i2c_read(0x21,0x54,Lu); // C
    arduino_i2c_read(0x21,0x3d,Lu); // COM13
    arduino_i2c_read(0x21,0xff,Lu); // C

    }

     void RegConfigOrigin()
  {


    arduino_i2c_read(0x21,0x00,Lu);// def : 00
    arduino_i2c_read(0x21,0x01,Lu);// def : 80
    arduino_i2c_read(0x21,0x02,Lu);// def : 80
    arduino_i2c_read(0x21,0x03,Lu);// def : 03
    arduino_i2c_read(0x21,0x04,Lu);// def : 00
    arduino_i2c_read(0x21,0x05,Lu);// def : 00
    arduino_i2c_read(0x21,0x06,Lu);// def : 00
    arduino_i2c_read(0x21,0x07,Lu);// def : 00
    arduino_i2c_read(0x21,0x08,Lu);// def : 00
    arduino_i2c_read(0x21,0x09,Lu);// def : 01
    arduino_i2c_read(0x21,0x0A,Lu);// def : 76
    arduino_i2c_read(0x21,0x0B,Lu);// def : 76
    arduino_i2c_read(0x21,0x0C,Lu);// def : 00
    arduino_i2c_read(0x21,0x0D,Lu);// def : 40
    arduino_i2c_read(0x21,0x0E,Lu);// def : 01
    arduino_i2c_read(0x21,0x0F,Lu);// def : 43
    arduino_i2c_read(0x21,0x10,Lu);// def : 40
    arduino_i2c_read(0x21,0x11,Lu);// def : 80
    arduino_i2c_read(0x21,0x12,Lu);// def : 00
    arduino_i2c_read(0x21,0x13,Lu);// def : 8F
    arduino_i2c_read(0x21,0x14,Lu);// def : 4A
    arduino_i2c_read(0x21,0x15,Lu);// def : 00
   // arduino_i2c_read(0x21,0x16,Lu);// def : res
    arduino_i2c_read(0x21,0x17,Lu);// def : 11
    arduino_i2c_read(0x21,0x18,Lu);// def : 61
    arduino_i2c_read(0x21,0x19,Lu);// def : 03
    arduino_i2c_read(0x21,0x1A,Lu);// def : 7B
    arduino_i2c_read(0x21,0x1B,Lu);// def : 00
    arduino_i2c_read(0x21,0x1C,Lu);// def : 7F
    arduino_i2c_read(0x21,0x1D,Lu);// def : A2
    arduino_i2c_read(0x21,0x1E,Lu);// def : 00
    arduino_i2c_read(0x21,0x1F,Lu);// def : 00
    arduino_i2c_read(0x21,0x20,Lu);// def : 04
    arduino_i2c_read(0x21,0x21,Lu);// def : 02
    arduino_i2c_read(0x21,0x22,Lu);// def : 01
    arduino_i2c_read(0x21,0x23,Lu);// def : 80
    arduino_i2c_read(0x21,0x24,Lu);// def : 75
    arduino_i2c_read(0x21,0x25,Lu);// def : 63
    arduino_i2c_read(0x21,0x26,Lu);// def : D4
    arduino_i2c_read(0x21,0x27,Lu);// def : 80
    arduino_i2c_read(0x21,0x28,Lu);// def : 80
   // arduino_i2c_read(0x21,0x29,Lu);// def : res
    arduino_i2c_read(0x21,0x2A,Lu);// def : 00
    arduino_i2c_read(0x21,0x2B,Lu);// def : 00
    arduino_i2c_read(0x21,0x2C,Lu);// def : 80
    arduino_i2c_read(0x21,0x2D,Lu);// def : 00
    arduino_i2c_read(0x21,0x2E,Lu);// def : 00
    arduino_i2c_read(0x21,0x2F,Lu);// def : 00
    arduino_i2c_read(0x21,0x30,Lu);// def : 08
    arduino_i2c_read(0x21,0x31,Lu);// def : 30
    arduino_i2c_read(0x21,0x32,Lu);// def : 80
    arduino_i2c_read(0x21,0x33,Lu);// def : 08
    arduino_i2c_read(0x21,0x34,Lu);// def : 03
    //arduino_i2c_read(0x21,0x35,Lu);// def : res
    //arduino_i2c_read(0x21,0x36,Lu);// def : res
    arduino_i2c_read(0x21,0x37,Lu);// def : 04
    arduino_i2c_read(0x21,0x38,Lu);// def : 12
    arduino_i2c_read(0x21,0x39,Lu);// def : 00
    arduino_i2c_read(0x21,0x3A,Lu);// def : 0C
    arduino_i2c_read(0x21,0x3B,Lu);// def : 00
    arduino_i2c_read(0x21,0x3C,Lu);// def : 40
    arduino_i2c_read(0x21,0x3D,Lu);// def : 99
    arduino_i2c_read(0x21,0x3E,Lu);// def : 0E
    arduino_i2c_read(0x21,0x3F,Lu);// def : 88
    arduino_i2c_read(0x21,0x40,Lu);// def : C0
    arduino_i2c_read(0x21,0x41,Lu);// def :
    arduino_i2c_read(0x21,0x42,Lu);// def :
    arduino_i2c_read(0x21,0x43,Lu);// def :
    arduino_i2c_read(0x21,0x44,Lu);// def :
    arduino_i2c_read(0x21,0x45,Lu);// def :
    arduino_i2c_read(0x21,0x46,Lu);// def :
    arduino_i2c_read(0x21,0x47,Lu);// def :
    arduino_i2c_read(0x21,0x48,Lu);// def :
   // arduino_i2c_read(0x21,0x49,Lu);// def : res
   // arduino_i2c_read(0x21,0x4A,Lu);// def : res
    arduino_i2c_read(0x21,0x4B,Lu);// def :
    arduino_i2c_read(0x21,0x4C,Lu);// def :
    arduino_i2c_read(0x21,0x4D,Lu);// def :
   // arduino_i2c_read(0x21,0x4E,Lu);// def : res
    arduino_i2c_read(0x21,0x4F,Lu);// def :
    arduino_i2c_read(0x21,0x50,Lu);// def :
    arduino_i2c_read(0x21,0x51,Lu);// def :
    arduino_i2c_read(0x21,0x52,Lu);// def :
    arduino_i2c_read(0x21,0x53,Lu);// def :
    arduino_i2c_read(0x21,0x54,Lu);// def :
    arduino_i2c_read(0x21,0x55,Lu);// def :
    arduino_i2c_read(0x21,0x56,Lu);// def :
    arduino_i2c_read(0x21,0x57,Lu);// def :
    arduino_i2c_read(0x21,0x58,Lu);// def :
    arduino_i2c_read(0x21,0x59,Lu);// def :
    arduino_i2c_read(0x21,0x5A,Lu);// def :
    arduino_i2c_read(0x21,0x5B,Lu);// def :
    arduino_i2c_read(0x21,0x5C,Lu);// def :
    arduino_i2c_read(0x21,0x5D,Lu);// def :
    arduino_i2c_read(0x21,0x5E,Lu);// def :
    arduino_i2c_read(0x21,0x5F,Lu);// def :
    arduino_i2c_read(0x21,0x60,Lu);// def :
    arduino_i2c_read(0x21,0x61,Lu);// def :
    arduino_i2c_read(0x21,0x62,Lu);// def :
    arduino_i2c_read(0x21,0x63,Lu);// def :
    arduino_i2c_read(0x21,0x64,Lu);// def :
    arduino_i2c_read(0x21,0x65,Lu);// def :
    arduino_i2c_read(0x21,0x66,Lu);// def :
    arduino_i2c_read(0x21,0x67,Lu);// def :
    arduino_i2c_read(0x21,0x68,Lu);// def :
    arduino_i2c_read(0x21,0x69,Lu);// def :
    arduino_i2c_read(0x21,0x6A,Lu);// def :
    arduino_i2c_read(0x21,0x6B,Lu);// def :
    arduino_i2c_read(0x21,0x6C,Lu);// def :
    arduino_i2c_read(0x21,0x6D,Lu);// def :
    arduino_i2c_read(0x21,0x6E,Lu);// def :
    arduino_i2c_read(0x21,0x6F,Lu);// def :
    arduino_i2c_read(0x21,0x70,Lu);// def :
    arduino_i2c_read(0x21,0x71,Lu);// def :
    arduino_i2c_read(0x21,0x72,Lu);// def :
    arduino_i2c_read(0x21,0x73,Lu);// def :
    arduino_i2c_read(0x21,0x74,Lu);// def :
    arduino_i2c_read(0x21,0x75,Lu);// def :
    arduino_i2c_read(0x21,0x76,Lu);// def :
    arduino_i2c_read(0x21,0x77,Lu);// def :
   // arduino_i2c_read(0x21,0x78,Lu);// def : res
   // arduino_i2c_read(0x21,0x79,Lu);// def : res
    arduino_i2c_read(0x21,0x7A,Lu);// def :
    arduino_i2c_read(0x21,0x7B,Lu);// def :
    arduino_i2c_read(0x21,0x7C,Lu);// def :
    arduino_i2c_read(0x21,0x7D,Lu);// def :
    arduino_i2c_read(0x21,0x7E,Lu);// def :
    arduino_i2c_read(0x21,0x7F,Lu);// def :
    arduino_i2c_read(0x21,0x80,Lu);// def :
    arduino_i2c_read(0x21,0x81,Lu);// def :
    arduino_i2c_read(0x21,0x83,Lu);// def :
    arduino_i2c_read(0x21,0x84,Lu);// def :
    arduino_i2c_read(0x21,0x85,Lu);// def :
    arduino_i2c_read(0x21,0x86,Lu);// def :
    arduino_i2c_read(0x21,0x87,Lu);// def :
    arduino_i2c_read(0x21,0x88,Lu);// def :
    arduino_i2c_read(0x21,0x89,Lu);// def :
   /* arduino_i2c_read(0x21,0x8A,Lu);// def :
    arduino_i2c_read(0x21,0x8B,Lu);// def :
    arduino_i2c_read(0x21,0x8C,Lu);// def :
    arduino_i2c_read(0x21,0x8D,Lu);// def :
    arduino_i2c_read(0x21,0x8E,Lu);// def :
    arduino_i2c_read(0x21,0x8F,Lu);// def :
    arduino_i2c_read(0x21,0x90,Lu);// def :
    arduino_i2c_read(0x21,0x91,Lu);// def : res */
    arduino_i2c_read(0x21,0x92,Lu);// def :
    arduino_i2c_read(0x21,0x93,Lu);// def :
    arduino_i2c_read(0x21,0x94,Lu);// def :
    arduino_i2c_read(0x21,0x95,Lu);// def :
   /* arduino_i2c_read(0x21,0x96,Lu);// def :
    arduino_i2c_read(0x21,0x97,Lu);// def :
    arduino_i2c_read(0x21,0x98,Lu);// def :
    arduino_i2c_read(0x21,0x99,Lu);// def :
    arduino_i2c_read(0x21,0x9A,Lu);// def :
    arduino_i2c_read(0x21,0x9B,Lu);// def :
    arduino_i2c_read(0x21,0x9C,Lu);// def : res */
    arduino_i2c_read(0x21,0x9D,Lu);// def :
    arduino_i2c_read(0x21,0x9E,Lu);// def :
    arduino_i2c_read(0x21,0x9F,Lu);// def :
    arduino_i2c_read(0x21,0xA0,Lu);// def :
    arduino_i2c_read(0x21,0xA1,Lu);// def :
    arduino_i2c_read(0x21,0xA2,Lu);// def :
//    arduino_i2c_read(0x21,0xA3,Lu);// def : res
    arduino_i2c_read(0x21,0xA4,Lu);// def :
    arduino_i2c_read(0x21,0xA5,Lu);// def :
    arduino_i2c_read(0x21,0xA6,Lu);// def :
    arduino_i2c_read(0x21,0xA7,Lu);// def :
    arduino_i2c_read(0x21,0xA8,Lu);// def :
    arduino_i2c_read(0x21,0xA9,Lu);// def :
    arduino_i2c_read(0x21,0xAA,Lu);// def :
  //  arduino_i2c_read(0x21,0xAB,Lu);// def : res
    arduino_i2c_read(0x21,0xAC,Lu);// def :
    arduino_i2c_read(0x21,0xAD,Lu);// def :
    arduino_i2c_read(0x21,0xAE,Lu);// def :
    arduino_i2c_read(0x21,0xAF,Lu);// def :
  //  arduino_i2c_read(0x21,0xB0,Lu);// def : res
    arduino_i2c_read(0x21,0xB1,Lu);// def :
    arduino_i2c_read(0x21,0xB2,Lu);// def :
    arduino_i2c_read(0x21,0xB3,Lu);// def :
    arduino_i2c_read(0x21,0xB4,Lu);// def :
    arduino_i2c_read(0x21,0xB5,Lu);// def :
 /*   arduino_i2c_read(0x21,0xB6,Lu);// def :
    arduino_i2c_read(0x21,0xB7,Lu);// def :
    arduino_i2c_read(0x21,0xB8,Lu);// def :
    arduino_i2c_read(0x21,0xB9,Lu);// def :
    arduino_i2c_read(0x21,0xBA,Lu);// def :
    arduino_i2c_read(0x21,0xBB,Lu);// def :
    arduino_i2c_read(0x21,0xBC,Lu);// def :
    arduino_i2c_read(0x21,0xBD,Lu);// def : res */
    arduino_i2c_read(0x21,0xBE,Lu);// def :
    arduino_i2c_read(0x21,0xBF,Lu);// def :
    arduino_i2c_read(0x21,0xC0,Lu);// def :
    arduino_i2c_read(0x21,0xC1,Lu);// def :
 /*   arduino_i2c_read(0x21,0xC2,Lu);// def :
    arduino_i2c_read(0x21,0xC3,Lu);// def :
    arduino_i2c_read(0x21,0xC4,Lu);// def :
    arduino_i2c_read(0x21,0xC5,Lu);// def :
    arduino_i2c_read(0x21,0xC6,Lu);// def :
    arduino_i2c_read(0x21,0xC7,Lu);// def :
    arduino_i2c_read(0x21,0xC8,Lu);// def : res*/
    arduino_i2c_read(0x21,0xC9,Lu);// def :


    Serial.println();
    Serial.println();
    arduino_i2c_write(0x21,0x12,0x80); // Reset tous les registres SCCB à leur valeur d'origine
    Serial.println();
    Serial.println();


    arduino_i2c_read(0x21,0x00,Lu);// def : 00
    arduino_i2c_read(0x21,0x01,Lu);// def : 80
    arduino_i2c_read(0x21,0x02,Lu);// def : 80
    arduino_i2c_read(0x21,0x03,Lu);// def : 03
    arduino_i2c_read(0x21,0x04,Lu);// def : 00
    arduino_i2c_read(0x21,0x05,Lu);// def : 00
    arduino_i2c_read(0x21,0x06,Lu);// def : 00
    arduino_i2c_read(0x21,0x07,Lu);// def : 00
    arduino_i2c_read(0x21,0x08,Lu);// def : 00
    arduino_i2c_read(0x21,0x09,Lu);// def : 01
    arduino_i2c_read(0x21,0x0A,Lu);// def : 76
    arduino_i2c_read(0x21,0x0B,Lu);// def : 76
    arduino_i2c_read(0x21,0x0C,Lu);// def : 00
    arduino_i2c_read(0x21,0x0D,Lu);// def : 40
    arduino_i2c_read(0x21,0x0E,Lu);// def : 01
    arduino_i2c_read(0x21,0x0F,Lu);// def : 43
    arduino_i2c_read(0x21,0x10,Lu);// def : 40
    arduino_i2c_read(0x21,0x11,Lu);// def : 80
    arduino_i2c_read(0x21,0x12,Lu);// def : 00
    arduino_i2c_read(0x21,0x13,Lu);// def : 8F
    arduino_i2c_read(0x21,0x14,Lu);// def : 4A
    arduino_i2c_read(0x21,0x15,Lu);// def : 00
   //arduino_i2c_read(0x21,0x16,Lu);// def : res
    arduino_i2c_read(0x21,0x17,Lu);// def : 11
    arduino_i2c_read(0x21,0x18,Lu);// def : 61
    arduino_i2c_read(0x21,0x19,Lu);// def : 03
    arduino_i2c_read(0x21,0x1A,Lu);// def : 7B
    arduino_i2c_read(0x21,0x1B,Lu);// def : 00
    arduino_i2c_read(0x21,0x1C,Lu);// def : 7F
    arduino_i2c_read(0x21,0x1D,Lu);// def : A2
    arduino_i2c_read(0x21,0x1E,Lu);// def : 00
    arduino_i2c_read(0x21,0x1F,Lu);// def : 00
    arduino_i2c_read(0x21,0x20,Lu);// def : 04
    arduino_i2c_read(0x21,0x21,Lu);// def : 02
    arduino_i2c_read(0x21,0x22,Lu);// def : 01
    arduino_i2c_read(0x21,0x23,Lu);// def : 80
    arduino_i2c_read(0x21,0x24,Lu);// def : 75
    arduino_i2c_read(0x21,0x25,Lu);// def : 63
    arduino_i2c_read(0x21,0x26,Lu);// def : D4
    arduino_i2c_read(0x21,0x27,Lu);// def : 80
    arduino_i2c_read(0x21,0x28,Lu);// def : 80
   // arduino_i2c_read(0x21,0x29,Lu);// def : res
    arduino_i2c_read(0x21,0x2A,Lu);// def : 00
    arduino_i2c_read(0x21,0x2B,Lu);// def : 00
    arduino_i2c_read(0x21,0x2C,Lu);// def : 80
    arduino_i2c_read(0x21,0x2D,Lu);// def : 00
    arduino_i2c_read(0x21,0x2E,Lu);// def : 00
    arduino_i2c_read(0x21,0x2F,Lu);// def : 00
    arduino_i2c_read(0x21,0x30,Lu);// def : 08
    arduino_i2c_read(0x21,0x31,Lu);// def : 30
    arduino_i2c_read(0x21,0x32,Lu);// def : 80
    arduino_i2c_read(0x21,0x33,Lu);// def : 08
    arduino_i2c_read(0x21,0x34,Lu);// def : 03
    //arduino_i2c_read(0x21,0x35,Lu);// def : res
    //arduino_i2c_read(0x21,0x36,Lu);// def : res
    arduino_i2c_read(0x21,0x37,Lu);// def : 04
    arduino_i2c_read(0x21,0x38,Lu);// def : 12
    arduino_i2c_read(0x21,0x39,Lu);// def : 00
    arduino_i2c_read(0x21,0x3A,Lu);// def : 0C
    arduino_i2c_read(0x21,0x3B,Lu);// def : 00
    arduino_i2c_read(0x21,0x3C,Lu);// def : 40
    arduino_i2c_read(0x21,0x3D,Lu);// def : 99
    arduino_i2c_read(0x21,0x3E,Lu);// def : 0E
    arduino_i2c_read(0x21,0x3F,Lu);// def : 88
    arduino_i2c_read(0x21,0x40,Lu);// def : C0
    arduino_i2c_read(0x21,0x41,Lu);// def :
    arduino_i2c_read(0x21,0x42,Lu);// def :
    arduino_i2c_read(0x21,0x43,Lu);// def :
    arduino_i2c_read(0x21,0x44,Lu);// def :
    arduino_i2c_read(0x21,0x45,Lu);// def :
    arduino_i2c_read(0x21,0x46,Lu);// def :
    arduino_i2c_read(0x21,0x47,Lu);// def :
    arduino_i2c_read(0x21,0x48,Lu);// def :
   // arduino_i2c_read(0x21,0x49,Lu);// def : res
   // arduino_i2c_read(0x21,0x4A,Lu);// def : res
    arduino_i2c_read(0x21,0x4B,Lu);// def :
    arduino_i2c_read(0x21,0x4C,Lu);// def :
    arduino_i2c_read(0x21,0x4D,Lu);// def :
   // arduino_i2c_read(0x21,0x4E,Lu);// def : res
    arduino_i2c_read(0x21,0x4F,Lu);// def :
    arduino_i2c_read(0x21,0x50,Lu);// def :
    arduino_i2c_read(0x21,0x51,Lu);// def :
    arduino_i2c_read(0x21,0x52,Lu);// def :
    arduino_i2c_read(0x21,0x53,Lu);// def :
    arduino_i2c_read(0x21,0x54,Lu);// def :
    arduino_i2c_read(0x21,0x55,Lu);// def :
    arduino_i2c_read(0x21,0x56,Lu);// def :
    arduino_i2c_read(0x21,0x57,Lu);// def :
    arduino_i2c_read(0x21,0x58,Lu);// def :
    arduino_i2c_read(0x21,0x59,Lu);// def :
    arduino_i2c_read(0x21,0x5A,Lu);// def :
    arduino_i2c_read(0x21,0x5B,Lu);// def :
    arduino_i2c_read(0x21,0x5C,Lu);// def :
    arduino_i2c_read(0x21,0x5D,Lu);// def :
    arduino_i2c_read(0x21,0x5E,Lu);// def :
    arduino_i2c_read(0x21,0x5F,Lu);// def :
    arduino_i2c_read(0x21,0x60,Lu);// def :
    arduino_i2c_read(0x21,0x61,Lu);// def :
    arduino_i2c_read(0x21,0x62,Lu);// def :
    arduino_i2c_read(0x21,0x63,Lu);// def :
    arduino_i2c_read(0x21,0x64,Lu);// def :
    arduino_i2c_read(0x21,0x65,Lu);// def :
    arduino_i2c_read(0x21,0x66,Lu);// def :
    arduino_i2c_read(0x21,0x67,Lu);// def :
    arduino_i2c_read(0x21,0x68,Lu);// def :
    arduino_i2c_read(0x21,0x69,Lu);// def :
    arduino_i2c_read(0x21,0x6A,Lu);// def :
    arduino_i2c_read(0x21,0x6B,Lu);// def :
    arduino_i2c_read(0x21,0x6C,Lu);// def :
    arduino_i2c_read(0x21,0x6D,Lu);// def :
    arduino_i2c_read(0x21,0x6E,Lu);// def :
    arduino_i2c_read(0x21,0x6F,Lu);// def :
    arduino_i2c_read(0x21,0x70,Lu);// def :
    arduino_i2c_read(0x21,0x71,Lu);// def :
    arduino_i2c_read(0x21,0x72,Lu);// def :
    arduino_i2c_read(0x21,0x73,Lu);// def :
    arduino_i2c_read(0x21,0x74,Lu);// def :
    arduino_i2c_read(0x21,0x75,Lu);// def :
    arduino_i2c_read(0x21,0x76,Lu);// def :
    arduino_i2c_read(0x21,0x77,Lu);// def :
   // arduino_i2c_read(0x21,0x78,Lu);// def : res
   // arduino_i2c_read(0x21,0x79,Lu);// def : res
    arduino_i2c_read(0x21,0x7A,Lu);// def :
    arduino_i2c_read(0x21,0x7B,Lu);// def :
    arduino_i2c_read(0x21,0x7C,Lu);// def :
    arduino_i2c_read(0x21,0x7D,Lu);// def :
    arduino_i2c_read(0x21,0x7E,Lu);// def :
    arduino_i2c_read(0x21,0x7F,Lu);// def :
    arduino_i2c_read(0x21,0x80,Lu);// def :
    arduino_i2c_read(0x21,0x81,Lu);// def :
    arduino_i2c_read(0x21,0x83,Lu);// def :
    arduino_i2c_read(0x21,0x84,Lu);// def :
    arduino_i2c_read(0x21,0x85,Lu);// def :
    arduino_i2c_read(0x21,0x86,Lu);// def :
    arduino_i2c_read(0x21,0x87,Lu);// def :
    arduino_i2c_read(0x21,0x88,Lu);// def :
    arduino_i2c_read(0x21,0x89,Lu);// def :
   /* arduino_i2c_read(0x21,0x8A,Lu);// def :
    arduino_i2c_read(0x21,0x8B,Lu);// def :
    arduino_i2c_read(0x21,0x8C,Lu);// def :
    arduino_i2c_read(0x21,0x8D,Lu);// def :
    arduino_i2c_read(0x21,0x8E,Lu);// def :
    arduino_i2c_read(0x21,0x8F,Lu);// def :
    arduino_i2c_read(0x21,0x90,Lu);// def :
    arduino_i2c_read(0x21,0x91,Lu);// def : res */
    arduino_i2c_read(0x21,0x92,Lu);// def :
    arduino_i2c_read(0x21,0x93,Lu);// def :
    arduino_i2c_read(0x21,0x94,Lu);// def :
    arduino_i2c_read(0x21,0x95,Lu);// def :
   /* arduino_i2c_read(0x21,0x96,Lu);// def :
    arduino_i2c_read(0x21,0x97,Lu);// def :
    arduino_i2c_read(0x21,0x98,Lu);// def :
    arduino_i2c_read(0x21,0x99,Lu);// def :
    arduino_i2c_read(0x21,0x9A,Lu);// def :
    arduino_i2c_read(0x21,0x9B,Lu);// def :
    arduino_i2c_read(0x21,0x9C,Lu);// def : res */
    arduino_i2c_read(0x21,0x9D,Lu);// def :
    arduino_i2c_read(0x21,0x9E,Lu);// def :
    arduino_i2c_read(0x21,0x9F,Lu);// def :
    arduino_i2c_read(0x21,0xA0,Lu);// def :
    arduino_i2c_read(0x21,0xA1,Lu);// def :
    arduino_i2c_read(0x21,0xA2,Lu);// def :
//    arduino_i2c_read(0x21,0xA3,Lu);// def : res
    arduino_i2c_read(0x21,0xA4,Lu);// def :
    arduino_i2c_read(0x21,0xA5,Lu);// def :
    arduino_i2c_read(0x21,0xA6,Lu);// def :
    arduino_i2c_read(0x21,0xA7,Lu);// def :
    arduino_i2c_read(0x21,0xA8,Lu);// def :
    arduino_i2c_read(0x21,0xA9,Lu);// def :
    arduino_i2c_read(0x21,0xAA,Lu);// def :
  //  arduino_i2c_read(0x21,0xAB,Lu);// def : res
    arduino_i2c_read(0x21,0xAC,Lu);// def :
    arduino_i2c_read(0x21,0xAD,Lu);// def :
    arduino_i2c_read(0x21,0xAE,Lu);// def :
    arduino_i2c_read(0x21,0xAF,Lu);// def :
  //  arduino_i2c_read(0x21,0xB0,Lu);// def : res
    arduino_i2c_read(0x21,0xB1,Lu);// def :
    arduino_i2c_read(0x21,0xB2,Lu);// def :
    arduino_i2c_read(0x21,0xB3,Lu);// def :
    arduino_i2c_read(0x21,0xB4,Lu);// def :
    arduino_i2c_read(0x21,0xB5,Lu);// def :
 /*   arduino_i2c_read(0x21,0xB6,Lu);// def :
    arduino_i2c_read(0x21,0xB7,Lu);// def :
    arduino_i2c_read(0x21,0xB8,Lu);// def :
    arduino_i2c_read(0x21,0xB9,Lu);// def :
    arduino_i2c_read(0x21,0xBA,Lu);// def :
    arduino_i2c_read(0x21,0xBB,Lu);// def :
    arduino_i2c_read(0x21,0xBC,Lu);// def :
    arduino_i2c_read(0x21,0xBD,Lu);// def : res */
    arduino_i2c_read(0x21,0xBE,Lu);// def :
    arduino_i2c_read(0x21,0xBF,Lu);// def :
    arduino_i2c_read(0x21,0xC0,Lu);// def :
    arduino_i2c_read(0x21,0xC1,Lu);// def :
 /*   arduino_i2c_read(0x21,0xC2,Lu);// def :
    arduino_i2c_read(0x21,0xC3,Lu);// def :
    arduino_i2c_read(0x21,0xC4,Lu);// def :
    arduino_i2c_read(0x21,0xC5,Lu);// def :
    arduino_i2c_read(0x21,0xC6,Lu);// def :
    arduino_i2c_read(0x21,0xC7,Lu);// def :
    arduino_i2c_read(0x21,0xC8,Lu);// def : res*/
    arduino_i2c_read(0x21,0xC9,Lu);// def :


    }
