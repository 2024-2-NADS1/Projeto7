//Infelizmente no site WOKWI não tem o sensor de gás (MQ-2) e nem o DHT11
// Optamos em substituir o MQ-2 pelo Potenciômetro, e DHT11 pelo DHT22.

#include <DHT.h> // Biblioteca para controlar o sensor DHT22 (temperatura e umidade)

// Definições dos pinos onde os componentes estão conectados no ESP32
#define DHTPIN 21     // Pino onde o DHT22 (sensor de temperatura e umidade) está conectado
#define DHTYPE DHT22  // Tipo do sensor DHT que estamos utilizando (DHT22)
#define BUZZER_PIN 22 // Pino onde o buzzer (alarme sonoro) está conectado
#define LED_PIN 23    // Pino onde o LED está conectado
#define POT_PIN 34    // Pino onde o potenciômetro (simulando o sensor MQ-2) está conectado

// Criando o objeto dht para controlar o sensor de temperatura e umidade
DHT dht(DHTPIN, DHTYPE);

void setup()
{
  // Inicializa a comunicação serial para enviar os dados para o Serial Monitor
  Serial.begin(115200);
  
  // Inicia o sensor DHT22
  dht.begin();
  
  // Configura os pinos do buzzer e do LED como saídas
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // Lê a umidade e a temperatura do sensor DHT22
  float h = dht.readHumidity();    // Lê a umidade
  float t = dht.readTemperature(); // Lê a temperatura
  
  // Lê o valor do potenciômetro (que está simulando o sensor MQ-2)
  int potValue = analogRead(POT_PIN); // Lê o valor analógico do potenciômetro

  // Exibe os valores lidos no Serial Monitor (útil para acompanhar os dados)
  Serial.print("Umidade: ");
  Serial.print(h);        // Exibe a umidade
  Serial.print("% Temperatura: ");
  Serial.print(t);        // Exibe a temperatura
  Serial.print("°C Potenciômetro: ");
  Serial.println(potValue); // Exibe o valor do potenciômetro

  // Condições para acionar o LED e o buzzer
  if (h > 70 || t > 40 || potValue > 650) // Se a umidade for maior que 70, a temperatura maior que 40°C ou o potenciômetro maior que 650
  {
    // Liga o LED e o buzzer enquanto as condições forem atendidas
    digitalWrite(LED_PIN, HIGH);  // Acende o LED
    tone(BUZZER_PIN, 1000);       // Emite um som no buzzer a 1kHz
    
    delay(500);                   // Aguarda 500ms (LED fica aceso por esse tempo)
    digitalWrite(LED_PIN, LOW);   // Apaga o LED
    delay(100);                   // Aguarda 100ms (LED fica apagado por esse tempo)
  }
  else
  {
    // Quando as condições não são mais atendidas, desliga o LED e o buzzer
    digitalWrite(LED_PIN, LOW);   // Apaga o LED
    noTone(BUZZER_PIN);           // Desliga o som do buzzer
  }

  // Espera 1 segundos antes de ler os sensores novamente
  delay(1000); // Aguarda 1 segundos
}