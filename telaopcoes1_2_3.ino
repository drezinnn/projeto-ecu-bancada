/***********************************************************************
                      DECLARAÇÃO DAS VARIÁVEIS
***********************************************************************/
void telaopcao1();
void telaopcao2();

void telaopcao1(){
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  // (18 caracteres horizontal e 6 caracteres por vericais)
  display.setCursor(0,0); // Posiciona o cursor (linha, coluna)
  display.println("opcao 1 de 2"); // Imprime mensagem
  display.setCursor(15,25); // Posiciona o cursor (linha, coluna)
  display.println("AJUSTAR A INTENS."); // Imprime mensagem
  display.setCursor(30,35);
  display.println("IDADE DO PWM."); // Imprime mensagem
  display.display();
}

void telaopcao2(){
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  // (18 caracteres horizontal e 6 caracteres por vericais)
  display.setCursor(0,0); // Posiciona o cursor (linha, coluna)
  display.println("opcao 2 de 2"); // Imprime mensagem
  display.setCursor(40,30); // Posiciona o cursor (linha, coluna)
  display.println("CONCLUIR"); // Imprime mensagem
  display.display();
}


