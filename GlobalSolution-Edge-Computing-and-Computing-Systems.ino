#include <LiquidCrystal.h>

// Inicializa o LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define os pinos dos LEDs
const int ledVermelho = 3;
const int ledAmarelo = 4;
const int ledVerde = 5;

// Define o pino do potenciômetro
const int potenciometroPin = A1;

// Define o pino do sensor de temperatura TMP36
const int sensorTempPin = A0;

void setup() {
  // Configura os pinos dos LEDs como saída
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Inicia o LCD
  lcd.begin(16, 2);

  // Configura a comunicação serial (para debug)
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do potenciômetro (0 a 1023)
  int valorPot = analogRead(potenciometroPin);
  
  // Mapeia o valor para o intervalo de temperaturas desejado
  float temperaturaDeReferencia = map(valorPot, 2, 1023, 2, 50); // Mapeia para a faixa de temperatura desejada
  
  // Lê a tensão do sensor TMP36
  float voltage = analogRead(sensorTempPin) * 5.0 / 1024.0;
  
  // Converte a tensão para temperatura em Celsius
  float temperatureC = (voltage - 0.5) * 100;

  // Imprime a temperatura atual e a temperatura de referência no Serial Monitor e no LCD
  Serial.print("Temperatura Atual: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  Serial.print("Temperatura de Referencia: ");
  Serial.print(temperaturaDeReferencia);
  Serial.println(" C");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Atual: ");
  lcd.print(temperatureC);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Ref: ");
  lcd.print(temperaturaDeReferencia);
  lcd.print(" C");

  // Desliga todos os LEDs
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

  // Defina as faixas de temperatura em torno da temperatura de referência
  float faixaBaixa = temperaturaDeReferencia - 2; // 2 graus abaixo da referência
  float faixaAlta = temperaturaDeReferencia + 2; // 2 graus acima da referência

  // Lógica para os LEDs de acordo com a temperatura
  if (temperatureC < faixaBaixa) {
    // Se a temperatura estiver abaixo da faixa baixa, liga LED vermelho
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
  	digitalWrite(ledVerde, LOW);
  } else if (temperatureC > faixaAlta) {
    // Se a temperatura estiver acima da faixa alta, liga LED amarelo
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledAmarelo, LOW);
  	digitalWrite(ledVerde, LOW);
  } else {
    // Se a temperatura estiver dentro da faixa, liga LED verde
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
  	digitalWrite(ledAmarelo, LOW);
  }

  // Pausa antes da próxima leitura
  delay(1000);
}
