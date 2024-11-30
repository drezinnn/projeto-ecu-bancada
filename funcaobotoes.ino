/***********************************************************************
                      DECLARAÇÃO DAS VARIÁVEIS
***********************************************************************/
void habilitasaidapwm();
void funcao1escolhida();
void funcao2escolhida();
void funcao3escolhida();
void funcao4escolhida();
void funcao5escolhida();
void funcao6escolhida();
void funcao7escolhida();
void desabilitatudo();


/***********************************************************************
                    ACIONA AS FUNÇÕES DE CADA BOTÃO
***********************************************************************/
void habilitasaidapwm(){
  switch(bot_acionado){
    case 1: 
      desabilitatudo();
      funcao1escolhida();
      break;
    case 2: 
      desabilitatudo();
      funcao2escolhida();
      break;
    case 3: 
      desabilitatudo();
      funcao3escolhida();
      break;
    case 4: 
      desabilitatudo();
      funcao4escolhida();
      break;
    case 5: 
      desabilitatudo();
      funcao5escolhida();
      break;
    case 6: 
      desabilitatudo();
      funcao6escolhida();
      break;
    case 7: 
      desabilitatudo();
      funcao7escolhida();
      break;
    case 8: 
      desabilitatudo();
      break;
  }
}


/***********************************************************************
                          FUNÇÃO BOTÃO 8
***********************************************************************/
void desabilitatudo(){
      for (int i = 0; i <= sizeof(pwmPins); i++) {
        int channel = i; 
        ledcWrite(channel, dcvaluesdesabilitado[i]);
      }
}


/***********************************************************************
                          FUNÇÃO BOTÃO 1
***********************************************************************/
void funcao1escolhida(){

}


/***********************************************************************
                          FUNÇÃO BOTÃO 2
***********************************************************************/
void funcao2escolhida(){
  
}


/***********************************************************************
                          FUNÇÃO BOTÃO 3
***********************************************************************/
void funcao3escolhida(){
  
}


/***********************************************************************
                          FUNÇÃO BOTÃO 4
***********************************************************************/
void funcao4escolhida(){
  
}


/***********************************************************************
                          FUNÇÃO BOTÃO 5
***********************************************************************/
void funcao5escolhida(){
  
}


/***********************************************************************
                          FUNÇÃO BOTÃO 6
***********************************************************************/
void funcao6escolhida(){
  
}


/***********************************************************************
                          FUNÇÃO BOTÃO 7
***********************************************************************/
void funcao7escolhida(){
  
}
