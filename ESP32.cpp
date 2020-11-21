#include <Wire.h>
#include "soc/rtc_wdt.h"
#include "esp_int_wdt.h"
#include "esp_task_wdt.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

void FeedTheDog();

//I2C
#define I2C_SDA 17
#define I2C_SCL 16

// Camera
#define VSYNC 13
#define CLK_INT 18 // N�c�ssaire � l'utilisation des routines d'interuptions

// Fifo
#define WRST 12
#define RRST 14
#define OE 27
#define WEN 26
#define D0 25
#define D1 33
#define D2 32
#define D3 35
#define D4 34
#define D5 23
#define D6 22
#define D7 21

uint8_t Y;
byte Tab[76800];
byte Lu;
int i = 0; // Indice de comptage de la boucle
int i2 = 0; // Indice de comptage de proc�dure de tri de composante du pixel
int i3 = 0; // Indice de rep�rage du Y
int i4 = 0; // Buffer de i
int Bytecase = 0;
volatile bool FrameReading = false;
volatile bool FrameLu = false;
volatile int OneFrameOnly = 0;
bool TransmitOn = false;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; // N�c�ssaire � l'utilisation des ISR

// Toutes mes variables sont globales

void IRAM_ATTR CaptFrame()
{

      if(FrameReading==true)
      {

                    switch(Bytecase)
                    {
                      case 0 : // La premi�re acquisition est celle du premier CB
                               // Avant de paniquer si mes donn�es ont une dr�le de t�te voir si j'ai pas invers� MSB et LSB

                                Bytecase = 1;
                                break;
                      case 1 :
                                if(digitalRead(D0)) Y = Y +1;
                                if(digitalRead(D1)) Y = Y +2;
                                if(digitalRead(D2)) Y = Y +4;
                                if(digitalRead(D3)) Y = Y +8;
                                if(digitalRead(D4)) Y = Y +16;
                                if(digitalRead(D5)) Y = Y +32;
                                if(digitalRead(D6)) Y = Y +64;
                                if(digitalRead(D7)) Y = Y +128;

                                Tab[i3] = Y;
                                i3++; // Ne comptera que la composante Y
                                Y = 0;

                                if (i2 >= 1)
                                {
                                    i2 = 0; // R�initialise le compteur proc�dure � 0
                                    Bytecase = 0; // Et ram�ne cette boucle algorythmique � son �tat d'initial ou elle prend dans un premier temps Cb
                                }
                                else
                                {
                                    i2++; // i2 est l� pour checker que la fonction n'est pas d�j� pass� par le Bytecase 1
                                    Bytecase = 2;
                                }

                                break;
                      case 2 :

                                 if (i2 >= 1)
                                  {
                                    Bytecase = 1; // Retourne � la prise d'Y pour le deuxi�me Pixel compress�
                                  }

                                break;
                      default :
                                Serial.println("What The fuck ?");
                                break;
                      }
                 }
                 if(i3 == 76799)
                 {
                  FrameReading = false; // Signifie que le tableau est rempli, j'arr�te d'agir dans ma routine d'interruption
                  Serial.println("Tableau Rempli");
                  FrameLu = true;
                  //i3 = 0;// Dans le doute que je doive recapturer des images un jour


                        FeedTheDog();
                        vTaskDelay(50);
                        OneFrameOnly ++;
                        vTaskDelay(50);
                        detachInterrupt(CLK_INT);
                        Serial.println("detachInterrupt a eu lieu");
                        TransmitOn = true;
                        vTaskDelay(50);
                       /* while(1)
                        {
                          FeedTheDog();
                          vTaskDelay(50);
                          }*/

                  }

  }



void setup()
{
  delay(1500); //Eviter les glitchs
   Wire.begin(I2C_SDA,I2C_SCL,400000); // Active le protocole I2C � 400kHz
  Serial.begin(115200); // N�c�ssit� d'afficher le tableau en fin de code

  pinMode(CLK_INT, INPUT_PULLDOWN);
  void disableCore1WDT();

  //Outputs
  pinMode(RRST, OUTPUT);
  pinMode(WRST, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(WEN, OUTPUT); //WEN,OE,WRST et OE sont actifs bas
  //Inputs
  pinMode(VSYNC, INPUT); // Signal -> quand il est � l'�tat bas que je suis en train de capturer une frame
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  digitalWrite(WRST,HIGH);
  digitalWrite(RRST,HIGH);
  digitalWrite(OE,LOW); // Output enable activ�, actif bas
  digitalWrite(WEN,LOW); // Write enable activ�, actif bas

  Serial.println(" Le setup est termin�");
  Wire.setClock(400000);


  delay(2000);// Laisse surtout le temps de lire

  delayMicroseconds(100);
  digitalWrite(WRST,LOW);
  delayMicroseconds(1);
  digitalWrite(WRST,HIGH);
  digitalWrite(RRST,LOW);
  delayMicroseconds(1);
  digitalWrite(RRST,HIGH);// Instructions recommand�e dans la datasheet de l'AL422b

  while (digitalRead(VSYNC)!=1)
  {} // Attends qu'une Frame ait �t� captur�e pour la premi�re fois
  digitalWrite(WEN,1); // Arr�te l'�criture pendant que je lis l'image � mon aise // Pas s�r que ce soit n�c�ssaire





  Serial.println("Frame captur�e");

  digitalWrite(RRST,LOW);
  delayMicroseconds(1);
  digitalWrite(RRST,HIGH);//Reset l'adresse de lecture de la m�moire � la premi�re
  FrameReading = true;
}


// Une des astuces trouv�es en ligne est de ne jamais trainer trop longtemps dans la loop

void loop()
{

  if (OneFrameOnly < 1)
  {

    attachInterrupt(digitalPinToInterrupt(CLK_INT),CaptFrame,RISING);// Cr�er un routine d'interruption qui active une capture d'octet de donn�e cam�ra
    }
while(1)
{
  FeedTheDog();
 // Serial.println("Really");
 if(TransmitOn == true)
 {
        Serial.println("D�but de transmission");


                     /* for (i = 0; i<76800; i++)
                      {
                        Wire.beginTransmission(0x0B);
                        Wire.write(Tab[i]);
                        Wire.endTransmission();
                        Serial.println(Tab[i]);

                        }
                        */
             i3 = 0;
             while (i < 76800)
             {
              i4 = i3*240;
              for(i2 = i4; i2<((i3+1)*240); i2++)
              {
                        Wire.beginTransmission(0x0B);
                        Wire.write(Tab[i]);
                        Wire.endTransmission();
                       // Serial.println(Tab[i]);
                        i++;
                        //Serial.print("i=");Serial.println(i);
                }
delay(500);
                i3++;
                Serial.print("i3=");
                Serial.println(i3);
              }



                        Serial.println("Frame Transmise");
                        TransmitOn =false;
  // J'arrive enfin vraiment ici, c'est miraculeux, j'vais tenter la communication i2C pour voir si elle a v�ritablement lieux cette fois.
  }

 // Toute fa�on ca sert � rien, n'arrive jamais � revenir ici.

}
}

void FeedTheDog()
{
  // feed dog du CPU1
  TIMERG1.wdt_wprotect=TIMG_WDT_WKEY_VALUE; // write enable
  TIMERG1.wdt_feed=1;                       // feed dog
  TIMERG1.wdt_wprotect=0;                   // write protect
}


