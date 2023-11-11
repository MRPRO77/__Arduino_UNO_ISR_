/********************************Função que configura Pinos do MCU**************************************

                                   configuração para placa Arduino Uno

********************************************************************************************************/
/*******************************************************************************************************/
                                      /* Arquivos de inclusão */

#ifndef Config_mcu_h_
#define Config_mcu_h_
               
               
// ======================================================================================================
// --- Protótipo das Funções ---

void Config_mcu();
int display7seg(int number);                 //Retorna o dado para o barramento do display
void multiplex(int value);                   //Faz a multiplexação do display
void changeCounter(); 

void Supervisionamento();

#endif
