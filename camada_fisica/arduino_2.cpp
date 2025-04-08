const int pinoEntrada = 2;
const int tamanhoMensagem = 16;
volatile unsigned long ultimoTempo = 0;
volatile unsigned long tempos[6];
volatile int indiceTempo = 0;
volatile unsigned long periodoBitCalculado = 0;
volatile bool clockConfigurado = false;
unsigned int dadoRecebido = 0;

void medirClock() {
  unsigned long tempoAtual = micros();
  if (ultimoTempo != 0 && indiceTempo < 6) {
    tempos[indiceTempo++] = tempoAtual - ultimoTempo;
    if (indiceTempo == 6) {
      periodoBitCalculado = (tempos[0] + tempos[1] + tempos[2] + tempos[3] + tempos[4] + tempos[5]) / 6;
      clockConfigurado = true;
    }
  }
  ultimoTempo = tempoAtual;
}

void setup() {
  pinMode(pinoEntrada, INPUT);
  Serial.begin(9600);
  Serial.println("Receptor Manchester iniciado");
  attachInterrupt(digitalPinToInterrupt(pinoEntrada), medirClock, CHANGE);
}

void esperarBordaDeSubida() {
  while (digitalRead(pinoEntrada) == LOW);
  while (digitalRead(pinoEntrada) == HIGH);
}

void loop() {
  if (!clockConfigurado) {
    return;
  }

  dadoRecebido = 0;
  esperarBordaDeSubida();
  delayMicroseconds(periodoBitCalculado / 2);

  for (int i = 0; i < tamanhoMensagem; i++) {
    int primeiraMetade = digitalRead(pinoEntrada);
    delayMicroseconds(periodoBitCalculado / 2);
    int segundaMetade = digitalRead(pinoEntrada);

    bool bit;

    if (primeiraMetade == LOW && segundaMetade == HIGH) {
      bit = 1;
    } else if (primeiraMetade == HIGH && segundaMetade == LOW) {
      bit = 0;
    } else {
      Serial.println("Erro de sincronizacao!");
      return;
    }

    dadoRecebido = (dadoRecebido << 1) | bit;
    delayMicroseconds(periodoBitCalculado / 2);
  }

  Serial.print("Mensagem Recebida: ");
  Serial.println(dadoRecebido, BIN);

  delay(500);
}
