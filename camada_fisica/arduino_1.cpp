const int pinoSaida = 9;
const int periodoBit = 20000;

unsigned int mensagens[4] = {
  0b0111010001110101,  
  0b0110010001101111,  
  0b0010000001100010,  
  0b0110010101101101  
};

int indiceMensagem = 0;

void enviarBitManchester(bool bit) {
  if (bit) {
    digitalWrite(pinoSaida, LOW);
    delayMicroseconds(periodoBit / 2);
    digitalWrite(pinoSaida, HIGH);
    delayMicroseconds(periodoBit / 2);
  } else {
    digitalWrite(pinoSaida, HIGH);
    delayMicroseconds(periodoBit / 2);
    digitalWrite(pinoSaida, LOW);
    delayMicroseconds(periodoBit / 2);
  }
}

void enviarPreambulo() {
  for (int i = 0; i < 6; i++) {  
    enviarBitManchester(i % 2);
  }
}

void enviar16BitsManchester(unsigned int dado) {
  enviarPreambulo();

  for (int i = 15; i >= 0; i--) {
    bool bit = (dado >> i) & 0x01;
    enviarBitManchester(bit);
  }

  delay(500);  
}

void setup() {
  pinMode(pinoSaida, OUTPUT);
}

void loop() {
  enviar16BitsManchester(mensagens[indiceMensagem]); 
  indiceMensagem = (indiceMensagem + 1) % 4;  
  delay(500);
}
