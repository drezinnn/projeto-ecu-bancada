/***********************************************************************
Essa parte do código configura o controle remoto, entre as funçoes estão:
-> Funcao que recebe o codigo do modulo RF
-> Função que grava os botoes
-> Funcao que identifica os botoes gravados
-> Funcao que guarda os botões gravados na memória.
***********************************************************************/

/***********************************************************************
                      DECLARAÇÃO DAS VARIÁVEIS
***********************************************************************/
void gravabotoes();
void identificabotoes();
void verificabotaoacionado();

int contadordeoitos=0;


/***********************************************************************
                  VERIFICA QUAL BOTÃO FOI ACIONADO
***********************************************************************/
void verificabotaoacionado()
{
  recuperacodigodosbotoes();
  if (mySwitch.available()) {
    value = mySwitch.getReceivedValue();
    Serial.print("value É:");
    Serial.println(value);
    mySwitch.resetAvailable();
    if((value/100) == prefix)
    {
      for(int a=0; a<numbotoes; a++)
      {
        if((value%100) == lastDigits[a])
        {
          bot_acionado=a+1;
        Serial.print("BOTAO ACIONADO É O:");
          Serial.println(bot_acionado);
        }
      }
    }
  }
  if(bot_acionado == 8 )
  {
    contadordeoitos++;
    bot_acionado=80;
    Serial.print("Contador de 8:");
    Serial.println(contadordeoitos);
  }
  if(bot_acionado != 8 && bot_acionado != 80)
  {
    contadordeoitos=0;
  }
  if(contadordeoitos==8)
  {
    estanatelasenha=true;
    interfacedisplay();
    contadordeoitos=0;
  }
}

/***********************************************************************
              GRAVA O CÓDIGO DE CADA BOTÃO
              ENTRA NESSA FUNÇÃO QUANDO D26 -> 0
***********************************************************************/
void gravabotoes()
{
  if (isProgrammingMode) {
    while (currentButton < numbotoes) {
      // Liga o LED para indicar que está pronto para receber um código
      digitalWrite(ledPin, HIGH);

      // Verifica se algum código foi recebido
      if (mySwitch.available()) {
        unsigned long receivedValue = mySwitch.getReceivedValue();
        if (receivedValue != 0) {
          // Armazena o código recebido
          buttonCodes[currentButton] = receivedValue;
          Serial.print("Código do botão ");
          Serial.print(currentButton + 1);
          Serial.print(": ");
          Serial.println(receivedValue);

          // Desliga o LED e aguarda 2 segundos
          digitalWrite(ledPin, LOW);
          delay(2000);

          // Incrementa para o próximo botão
          currentButton++;

          // Pisca o LED por 2 segundos para indicar o recebimento do código
          digitalWrite(ledPin, HIGH);
          delay(2000);
          digitalWrite(ledPin, LOW);
        }

        // Reseta a disponibilidade do receptor
        mySwitch.resetAvailable();
      }
    } 
    if (currentButton > numbotoes) {
      // Se todos os botões foram programados, sai do modo de programação
      isProgrammingMode = false;
      Serial.println("Modo de programação finalizado");
    }
  }
  Serial.println("Voltei");
  identificabotoes();
}



/***********************************************************************
          IDENTIFICA OS BOTÕES GRAVADOS E RELACIONA DE 1 A 8.
***********************************************************************/
void identificabotoes() {
  isPrefixEqual = true;
  firstPrefix = buttonCodes[0]/100; // Obtém os 4 primeiros dígitos do primeiro código
  // Verifica se os 4 primeiros dígitos de todos os códigos são iguais
  for (int a = 1; a < numbotoes; a++) {
    prefix = buttonCodes[a]/100; // Obtém os 4 primeiros dígitos de cada código
    if (prefix != firstPrefix) {
      isPrefixEqual = false;
      break;
    }
  }
  if (isPrefixEqual) {
    // Se os prefixos forem iguais, cria um vetor com os 2 últimos dígitos de cada código
    EEPROM.put(0, prefix/100);
    EEPROM.put(1, prefix%100);
    lastDigits[8];
    for (int a = 0; a < numbotoes; a++) {
      lastDigits[a] = buttonCodes[a]%100; // Obtém os 2 últimos dígitos de cada código
      Serial.print("Últimos dígitos do botão ");
      Serial.print(a + 1);
      Serial.print(": ");
      Serial.println(lastDigits[a]); 
      EEPROM.put((a+2), lastDigits[a]);
    }
  } else {
    // Se os prefixos não forem iguais, imprime "erro" na Serial
    Serial.println("Erro: os primeiros 4 dígitos dos códigos não são iguais.");
  }
  EEPROM.commit();
}



