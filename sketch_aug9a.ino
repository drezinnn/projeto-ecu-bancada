/***********************************************************************
                              BIBLIOTECAS
***********************************************************************/
#include <RCSwitch.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



/***********************************************************************
                              DEFINES
***********************************************************************/
#define led1 15
#define led2 25
#define led3 4
#define led4 5
#define rfpin 17
#define buttonPin 18
#define ledPin 2
#define sdadisplay 21
#define sckdisplay 22


/***********************************************************************
                        DECLARAÇÃO DE VARIÁVEIS
***********************************************************************/
/***********************************************************************
                                PWM
***********************************************************************/
const int numpwms=4;                                                  /define o número de saidas pwm.
const int pwmPins[] = {15, 13, 4, 5, 26, 19, 23, 13, 12, 14};         //Determina os pinos usados para PWM
int dcvalues[] = {127, 127, 127, 127, 127, 127, 127, 127, 127, 127};  //0 é 0% e 255 é 100% de DC
const int dcvaluesdesabilitado[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    //vetor de DC todo zerado
const int pwmFrequency = 5000;                                        //Frequencia do PWM
const int pwmResolution = 8;                                          //Resolução do PWM de 8 bits -> de 0 a 255
extern void habilitasaidapwm();
extern void funcao1escolhida();
extern void funcao2escolhida();
extern void funcao3escolhida();
extern void funcao4escolhida();
extern void funcao5escolhida();
extern void funcao6escolhida();
extern void funcao7escolhida();
extern void desabilitatudo();


/***********************************************************************
                                RF
***********************************************************************/
const int receiverPin = 17;         // Pino D27 do ESP32 conectado ao modulo RF
const int numbotoes = 8;            // Armazena o número de botões que o controle tem
unsigned long value;                //variavel utilizada para receber os codigos que vem do controle remoto
bool isProgrammingMode = false;     //variavel usada para indicar se o código está em modo de programação do controle
int i=0;                            //variável auxiliar
unsigned long buttonCodes[numbotoes];// Armazena os códigos dos 8 botões
int currentButton = 0;              // Índice do botão atual
bool isPrefixEqual;                 //variavel usada para indicar se os códigos recebidos vem do mesmo controle
unsigned long firstPrefix;          //armazena o primeiro prefixo, que será usado para comparar com os próximos
unsigned long prefix;               //armazena o identificador do controle
byte lastDigits[numbotoes];         //vetor que armazena o código de cada digito
int bot_acionado;                   //variável que armazena o número do botão que está acionado
RCSwitch mySwitch = RCSwitch();     //Declarando o objeto RF
//Funcoes globais que sao usadas
extern void verificabotaoacionado();
extern void gravabotoes();
extern void identificabotoes();


/***********************************************************************
                              DISPLAY
***********************************************************************/
//DECLARAÇÃO DAS VARIÁVEIS
Adafruit_SSD1306 display(-1);
//Essas variaveis tipo booleanas são usadas para identificar em qual tela o codigo está.
bool estanatelasenha=false;
bool estanatelaopcoes=false; 
bool telaconfigurapwm=false;
bool telaajusteintpwm=false; 
//outras variaveis
int telaopcao=1;
int canal=1;
int intensidade=0;
int canalescolhido=0;
unsigned long tempoinicio;
//funcoes globais que sao usadas
/****** Telas usadas*******/
extern void interfacedisplay();
extern void apresentacaodisplay();
extern void telainicial();
extern void logomarelli();
extern void telasenha();
extern void telaopcao1();
extern void telaopcao2();
extern void telasopcaopwm();
extern void telasajustaintpwm();
extern void telacanaisusados();
extern void telamodopisca();
extern void telapiscasegmentado();
/****** Codigos de interação com as telas******/
extern void interfacetelasenha();
extern void interfacetelaopcoes();
extern void interfacetelapwm();



/***********************************************************************
                                EEPROM
***********************************************************************/
extern void recuperacodigodosbotoes();
extern void recuperadcvalueseeprom();
extern void gravadcvalueseeprom();



/***********************************************************************
                                FUNÇÃO SETUP
***********************************************************************/
void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  mySwitch.enableReceive(receiverPin);                                // Habilita o receptor RF no pino 27
  for (int i = 0; i < numpwms; i++) {                         //Configura o PWM
    int channel = i; // Canal PWM (de 0 a 15)
    ledcSetup(channel, pwmFrequency, pwmResolution);
    ledcAttachPin(pwmPins[i], channel);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  tempoinicio=millis();
  for(int i=0; i<12; i++){
    dcvalues[i] = 127;
    Serial.println(dcvalues[i]);
  }
  recuperadcvalueseeprom();
}


/***********************************************************************
                                FUNÇÃO LOOP
***********************************************************************/
void loop() {
  if (digitalRead(buttonPin) == LOW) {                        //caso o botão esteja em nivel baixo o codigo entra em modo de programação dos botões do controle remoto
    isProgrammingMode = true;
    currentButton = 0;
    Serial.println("Modo de programação ativado");
    delay(500); // Debounce para o botão
    gravabotoes();
  }
  verificabotaoacionado();                                    //essa função faz com que o código fique o tempo todo verificando se algum botão foi acionado
  habilitasaidapwm();                                         //algum botão tendo sido acionado essa função aciona a função específica que esse botão deve realizar
  apresentacaodisplay();
}






