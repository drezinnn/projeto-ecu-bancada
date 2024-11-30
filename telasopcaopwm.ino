/***********************************************************************
                      DECLARAÇÃO DAS VARIÁVEIS
***********************************************************************/
void telasopcaopwm();
void telasajustaintpwm();


void telasopcaopwm(){
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  // (18 caracteres horizontal e 6 caracteres por vericais)
  display.setCursor(10,20); // Posiciona o cursor (linha, coluna)
  display.println("Selecione o canal"); // Imprime mensagem
  display.setCursor(35,35); // Posiciona o cursor (linha, coluna)
  display.println("CANAL:"); // Imprime mensagem
  display.setCursor(80,35);
  display.println(canal); // Imprime mensagem
  display.display();
}


void telasajustaintpwm(){
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  // (18 caracteres horizontal e 6 caracteres por vericais)
  display.setCursor(5,20); // Posiciona o cursor (linha, coluna)
  display.println("Defina a intensidade"); // Imprime mensagem
  display.setCursor(15,35); // Posiciona o cursor (linha, coluna)
  display.print("INTENSIDADE:"); // Imprime mensagem
  display.setCursor(90,35);
  display.print(intensidade); // Imprime mensagem
  display.setCursor(105,35);
  display.print("%"); // Imprime mensagem
  display.display();
}