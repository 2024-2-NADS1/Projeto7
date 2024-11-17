#include <DHT.h> // Infelizmente aqui no site WOKWI não tem o sensor de gás (MQ-2) e nem o DHT11
 // Optamos em substituir o MQ-2 pelo Potenciômetro, e DHT11 pelo DHT22 (Não muda muita coisa)

#define DHTPIN 21 // Pino onde o DHT22 está conectado
#define DHTYPE DHT22 // Definindo o tipo de sensor
#define BUZZER_PIN 22 // Pino do buzzer
#define LED_PIN 23 // Pino do LED
#define POT_PIN 34 // Pino do potenciômetro

DHT dht(DHTPIN, DHTYPE);

void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
  // Leitura da temperatura e umidade
{
  float h = dht.readHumidity();
  float t = dht. readTemperature();

  // Leitura do potenciômetro (simulando o sensor MQ-2)
  int potValue = analogRead(POT_PIN);

  // Exibir os valores no Serial Monitor
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print("% Temperature: ");
  Serial.print(t);
  Serial.print("°C Potenciômetro; ");
  Serial.println(potValue);

  // Lógica para ativar buzzer e LED
  if (h > 50 || potValue > 500) // Condições de alerta
  {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  delay(2000); // Espera 2 segundo antes da próxima leitura 
}