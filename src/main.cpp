/*******************************************************************************
   Título:      TCC  Engenharia Mecatrônica.

   Descrição:   C L P   ---  I H M

   Processador: Arduino Uno
   
   Geração Multifolhas


   Desenvolvido: MRPRO Tecnologia e Automação

   Autor: Tecnologo. Marcelo Rodrigues     Crea-SP 5070505617

   Data de Inicio: 20/10/2023       Versão:   2023.1.0

        

 
*******************************************************************************/  
/* ============================================================================  
                                                              
                                       _                      
                                      / \                     
                                     |oo >                    
                                     _\=/_                    
                    ___         #   /  _  \   #               
                   /<> \         \\//|/.\|\\//                
                 _|_____|_        \/  \_/  \/                 
                | | === | |          |\ /|                    
                |_|  0  |_|          \_ _/                    
                 ||  0  ||           | | |                    
                 ||__*__||           | | |                    
                |* \___/ *|          []|[]                    
                /=\ /=\ /=\          | | |                    
________________[_]_[_]_[_]_________/_]_[_\___________________________________
                                                                             
============================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "wire.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/twi.h>



#include "Config_mcu.h"


#define myAdress 0x08            // Arduino Uno I2C




void setup() {

  Config_mcu();

}

void loop() {


   Supervisionamento();

}  

