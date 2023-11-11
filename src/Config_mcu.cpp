/************************************************************************************************************

                                      configurações Esp32
************************************************************************************************************/

                                   /* Arquivos de Bibliotecas */

 // ========================================================================================================
// --- Bibliotecas Auxiliares --- //

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "wire.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <avr/pgmspace.h>


/**********************************************************************************************************/
                                        /* Arquivos de inclusão */

#include "Config_mcu.h"




// ======================================================================================================
// --- Constantes ---


#define disp1   A0                             //Display unidade   A0
#define disp2   A1                             //Display dezena    A1
#define disp3   A2                             //Display centena   A2
#define disp4   A3                             //Display milhar    A3

#define mais    A4                             //Botão para incremento no digital A4
#define menos   A5                             //Botão para decremento no digital A5

const uint16_t T1_init = 0;
const uint16_t T1_comp = 50;

#define myAdress 0x08             // Arduino Uno I2C

const int pinoLED_UNO = 13;  

#define ReleledPin   11          // numero do pino onde o Rele esta conectado
#define ReleledPin_1 10          // numero do pino onde o Rele esta conectado

// --- Variáveis Globais ---
int  mil, 
    cent,
     dez,                                     //Armazena o valor da dezena
     uni,                                     //Armazena o valor da unidade
    counter = PORTD;                            //Variável para contagem
    
boolean flagMais, 
        flagMenos;

// ======================================================================================================
// --- Interrupção ---
// Vetor de Interrupção Display  Sete segmentos
ISR(TIMER1_COMPA_vect)
{
  
  TCNT1 = T1_init;      //reinicializa TIMER1



      multiplex(counter);
         changeCounter();



  
} //end ISR

// ======================================================================================================
// --- Interrupção ---
// Vetor de Interrupção Comunicação I2C
ISR(TWI_vect_1)
{



}



// ======================================================================================================


  // verifica se existem dados para serem lidos no barramento I2C
void receiveEvent(int howMany) {
  
  if (Wire.available()) {
    // le o byte recebido
    char received = Wire.read();

    // se o byte recebido for igual a 0, apaga o LED
    if (received == 0) {
      digitalWrite(ReleledPin_1, LOW);
    }

    // se o byte recebido for igual a 1 acende o LED
    if (received == 1) {
      digitalWrite(ReleledPin_1, HIGH);
    }
  }
}




void Config_mcu()

{
  
  // ======================================================================================================
  // --- Interrupção ---
  // Vetor de Interrupção Display  Sete segmentos

    //Modo de Comparação
    TCCR1A = 0;

    //Prescaler 1:256
    TCCR1B |=  (1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);

    //Inicializa Registradores
    TCNT1 = T1_init;
    OCR1A = T1_comp;
    
    //Habilita Interrupção do Timer1
   // TIMSK1 = (1 << OCIE1A);

  // ======================================================================================================
  // --- Interrupção ---
  // Vetor de Interrupção Comunicação I2C

  // TWSR - TWI Status Register
  TWSR = 0b11111000;

  // TWCR - TWI Control Register
  TWCR = 0b00000000;

  // TWDR - TWI Data Register
  TWDR = 0b11111111;

  // TWAR - TWI (Slave) Address Register
  TWAR = 0b11111110;










  // ======================================================================================================


    for(char i=  0; i< 7; i++)  pinMode(i,       OUTPUT); //Saídas (barramento do display no PORTD)
    for(char j= A0; j<A3; j++)  pinMode(j,       OUTPUT); //Saídas (controle do display)
    for(char k= A4; k<A5; k++)  pinMode(k, INPUT_PULLUP); //Entrada botões
    
    digitalWrite(disp1, LOW);
    digitalWrite(disp2, LOW);
    digitalWrite(disp3, LOW);
    digitalWrite(disp4, LOW);
      
    Serial.begin(115200);

  
  

    // ingressa ao barramento I2C com o endereço definido no myAdress (0x07)

    Wire.begin((uint8_t)myAdress);





  
    
    flagMais  = 0x00; 
    flagMenos = 0x00;

    pinMode (pinoLED_UNO, OUTPUT);        // configura o pino do LED 2 como saida
    digitalWrite(pinoLED_UNO,LOW);



    

    pinMode(ReleledPin_1, OUTPUT);  // configura o pino do LED como saida
    digitalWrite(ReleledPin_1,HIGH);


    //Registra um evento para ser chamado quando chegar algum dado via I2C
    Wire.onReceive(receiveEvent);












}

// --- Desenvolvimento das Funções Auxiliares ---
int display7seg(int number)
{
  int catodo;                                  //Variável que receberá o número indexado ao vetor
  
  //Declaração e inicialização do vetor segmento
  int segmento[10] = {0x3f,                    //Dado referente ao BCD '0'
                      0x06,                    //Dado referente ao BCD '1'
                      0x5b,                    //Dado referente ao BCD '2'
                      0x4f,                    //Dado referente ao BCD '3'
                      0x66,                    //Dado referente ao BCD '4'
                      0x6d,                    //Dado referente ao BCD '5'
                      0x7d,                    //Dado referente ao BCD '6'
                      0x07,                    //Dado referente ao BCD '7'
                      0x7f,                    //Dado referente ao BCD '8'
                      0x67};                   //Dado referente ao BCD '9'
  
  catodo = segmento[number];  
  
  return(catodo);

} //end display7seg


    void    multiplex(int value)
        {

        mil = (value/1000);
        PORTD = display7seg(mil);
        digitalWrite(disp1, LOW);
        digitalWrite(disp2, LOW);
        digitalWrite(disp3, LOW);
        digitalWrite(disp4, HIGH);
        delay(1);
        digitalWrite(disp4, LOW);

        cent = ((value/100)%10);
        PORTD = display7seg(cent);
        digitalWrite(disp4, LOW);
        digitalWrite(disp1, LOW);
        digitalWrite(disp2, LOW);
        digitalWrite(disp3, HIGH);
        delay(1);
        digitalWrite(disp3, LOW);

        dez = ((value/10)%10);
        PORTD = display7seg(dez);
        digitalWrite(disp3, LOW);
        digitalWrite(disp4, LOW);
        digitalWrite(disp1, LOW);
        digitalWrite(disp2, HIGH);
        delay(1);
        digitalWrite(disp2, LOW);
        
        uni = ((value/1)%10);
        PORTD = display7seg(uni);
        digitalWrite(disp2, LOW);
        digitalWrite(disp3, LOW);
        digitalWrite(disp4, LOW);
        digitalWrite(disp1, HIGH);
        delay(1);
        digitalWrite(disp1,  LOW);

        } //end multiplex



void changeCounter()
{

   
   if(!digitalRead( mais)) flagMais  = 0x01;
   if(!digitalRead(menos)) flagMenos = 0x01;
   
   if(digitalRead(mais) && flagMais)
   {
      flagMais = 0x00;
      counter++;
      
      if(counter == 9999) counter = 0x00;
   }
   
   if(digitalRead(menos) && flagMenos)
   {
      flagMenos = 0x00;
      counter--;
      
      if(counter == 0) counter = 9999;
   }


} //end changeCounter




void Supervisionamento() {


  static unsigned long ultimaMudanca = 0;
 
  if (millis() - ultimaMudanca >= 1000)
  {
    int estado = !digitalRead (pinoLED_UNO);
    digitalWrite(pinoLED_UNO, estado);
    ultimaMudanca = millis();
  }

} 

