  /*

                Instituto Federal de Sergipe
             Bacharelado em Engenharia Eletrica

      Aluno : Leonardo Aprigio Nascimento Fontes

      Orientadora : Prof: Dra. Stephanie Kamarry Alves de Sousa
      Coorientador : Prof: Me. Fabio Luiz Sa Prudente

  */

  // Funcao de configuracao inicial

  void setup() {
  
  // Definicao dos pinos que serao usados como saida
  
  int pins[] = {9, 8, 7, 3, 4, 5, 10, 11, 12};
    for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); i++)
    pinMode(pins[i], OUTPUT);

  // Inicia a comunicacao serial com taxa de transferencia em bits por segundo de 9600
  
    Serial.begin(9600);
  }

  // Definicao dos valores das constantes para as ações
  integrativa e de atenuação

  float ki = 0.015, ka = 0.2;

  // Funcao principal executada continuamente

  void loop() {
  
  // Definicao dos pinos que receberao os sinais analogicos dos joysticks
  
  int Y = analogRead(A0), X = analogRead(A1), Z = analogRead(A2);
  
  // Calculo dos valores para os motores direito e esquerdo
  
  float MD = 0.5 * (Y - 512) + 0.5 * (X - 512), ME = 0.5 * (Y - 512) - 0.5 * (X - 512);
  
  // Atualiza o valor do motor vertical com base na leitura do pino analogico
  
  MV += (Z - 512);
  
  // Restringe os valores de MD, ME e MC para o intervalo [-255, 255]
  
  MD = constrain(MD, -255, 255);
  ME = constrain(ME, -255, 255);
  MV = constrain(MC, -255, 255);
  
  // Aplicacao da acao integrativa
  
  MV += MV * Z * ki;

  // Atenuação para o retorno da ação integrativa para zero
  
  MV = MV * ka;
  
  // Definicao dos pinos digitais de acordo com os sinais de controle do motor
  
  digitalWrite(8, MD > 0); digitalWrite(7, MD <= 0);
  digitalWrite(5, ME > 0); digitalWrite(4, ME <= 0);
  digitalWrite(11, MV > 0); digitalWrite(12, MV <= 0);
  
  // Definicao dos pinos PWM para os motores com base nos valores absolutos dos sinais de controle do motor
  
  analogWrite(9, abs(MD)); analogWrite(3, abs(ME)); analogWrite(10, abs(MV));

  // Imprime os valores PWM dos motores no monitor serial
  
  Serial.print("\tMC: ");
  Serial.println(MV);
  Serial.print("\tMD: ");
  Serial.print(MD);
  Serial.print("\tME: ");
  Serial.println(ME);
}
