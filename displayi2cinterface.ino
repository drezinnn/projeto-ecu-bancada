void apresentacaodisplay();
void interfacedisplay();
void interfacetelasenha();
void interfacetelapwm();
void  interfacetelaopcoes();
int   opcaoescolhida();
void gravadcvalueseeprom();
int vetorsenha[]={0, 0, 0, 0};  
int senha;


/***************************************************
telas possiveis
telainicial
logomarelli
interfacetelasenha -> telasenha() -> estanatelasenha
interfacetelaopcoes -> telaopcao1(), telaopcao2(),telaopcao3() -> estanatelaopcoes
interfacetelapwm -> telasopcaopwm() e telasajustaintpwm() -> telaconfigurapwm e telaajusteintpwm
******************************************************/


void apresentacaodisplay(){
  if(millis () < tempoinicio+2000)
  {
    telainicial();
  }
  if(millis () > tempoinicio+2000 && millis () < tempoinicio+4000)
  {
    logomarelli();
  }
  if(millis () > tempoinicio+4000)
  {
    tempoinicio=millis();
  }
}

void interfacedisplay(){
  interfacetelasenha();
  interfacetelaopcoes();
  interfacetelapwm();
}




/*Essa funcao se diferencia da anterior que recebe o botão pois nessa o código trava até que o botão seja recebido.*/
int opcaoescolhida(){
    recuperacodigodosbotoes();
    while (!mySwitch.available()) {
    }
    if (mySwitch.available()) {
      value = mySwitch.getReceivedValue();
      mySwitch.resetAvailable();
      if((value/100) == prefix)
      {
        for(int a=0; a<numbotoes; a++)
        {
          if((value%100) == lastDigits[a])
          {
            bot_acionado=a+1;
          }
        }
      }
    }
    return bot_acionado;
  }

void interfacetelasenha(){
  while(estanatelasenha)         //o codigo fica na telasenha enquanto optelasenha é false, quando ele passa para true o codigo continua
  {
  telasenha();
  }
}


void interfacetelaopcoes(){
  while(estanatelaopcoes)
  {
    if(telaopcao==1)
    {
      telaopcao1();
    }
    if(telaopcao==2)
    {
      telaopcao2();
    }
    verificabotaoacionado();
    if(bot_acionado == 1)
    {
      bot_acionado = 10;
      telaopcao=telaopcao-1;
      if(telaopcao<1)
      {
        telaopcao=1;
      }
    }
    if(bot_acionado == 2)
    {
      bot_acionado = 20;
      telaopcao=telaopcao+1;
      if(telaopcao>2)
      {
        telaopcao=2;
      }
    }
    if(bot_acionado == 3)
    {
      bot_acionado = 30;
      if(telaopcao==1)
      {
        estanatelasenha=false;
        estanatelaopcoes=false;
        telaconfigurapwm = true;
        telaajusteintpwm=false;
      }
      if(telaopcao==2)
      {
        estanatelasenha=false;
        estanatelaopcoes = false;
        telaconfigurapwm=false;
        telaajusteintpwm=false;
      }
    }
  }
}

void interfacetelapwm(){
  while(telaconfigurapwm)
  {
    telasopcaopwm();
    verificabotaoacionado();
    if(bot_acionado == 1)
    {
      bot_acionado = 10;
      canal=canal-1;
      if(canal<1)
      {
        canal=1;
      }
    }
    if(bot_acionado == 2)
    {
      bot_acionado = 20;
      canal=canal+1;
      if(canal>12)
      {
        canal=12;
      }
    }
    if(bot_acionado == 3)
    {
      bot_acionado = 30;
      canalescolhido=canal;
      telaconfigurapwm=false;
      telaajusteintpwm=true;
    }
  }
    while(telaajusteintpwm)
    {
      telasajustaintpwm();
      verificabotaoacionado();
      if(bot_acionado == 1)
      {
        bot_acionado = 10;
        intensidade=intensidade-5;
        if(intensidade<0)
        {
          intensidade=0;
        }
      }
      if(bot_acionado == 2)
      {
        bot_acionado = 20;
        intensidade=intensidade+5;
        if(intensidade>100)
        {
          intensidade=100;
        }
      }
      if(bot_acionado == 3)
      {
        bot_acionado = 30;
        dcvalues[(canalescolhido-1)]=round(intensidade*2.55);
        estanatelasenha=false;
        telaconfigurapwm=false;
        telaajusteintpwm=false;
        telaopcao=1;
        estanatelaopcoes=true;
        gravadcvalueseeprom();
        interfacetelaopcoes();
      }
    }
}
