/*
Autores: 
RENAN DAMPRELLI CARDOSO DA SILVA
MAURICIO SANTOS RODRIGUES
VITOR MANOEL COSME DA SILVA MELO

Componentes:
ESP32/LED/BUZZER/DHT11/MQ-2(SENSOR DE GÁS)

Ferramenta:
BLYNK(Aplicativo)/ARDUINO IDE
*/


//TOKENS DE ACESSO AO BLYNK
#define BLYNK_TEMPLATE_ID "TMPL2TqLehcAr"
#define BLYNK_TEMPLATE_NAME "Monitoramento de Ambiente Controlado"
#define BLYNK_AUTH_TOKEN "Lv7LoBgia7bax-fxUDU2RQsNuMD7oz5t"

#define BLYNK_PRINT Serial

//BIBLIOTECAS UTILIZADAS PARA A REALIZAÇÃO DO PROJETO
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

//VARIAVEIS DE CONEXÃO DE REDE PARA CONECTAR O ESP32
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "RENAN MARCELO FIBRA";
char pass[] = "11/09/2003";

//DEFINIÇÃO DO TIMER DE REQUISIÇÕES DO BLYNK
BlynkTimer timer;

//DECLARAÇÃO DAS VARIAVEIS DE CADA COMPONENTE
#define buzzer 2  //pino do buzzer/piezo
#define led 4  //pino do led
#define DHTPIN 26  //pino do sensor de temperatura/humidade
#define DHTTYPE DHT11 //definindo qual dos dhts está sendo utilizado
#define gas_digital 35 //pino do sensor MQ-2(Sensor de gás)

DHT dht(DHTPIN, DHTTYPE);


//FUNÇÃO PARA MEDIR E ENVIAR DADOS AO BLYNK(APP)
void sendSensor() {

  //DECLARANDO VARIAVEIS DE MEDICAO
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int g = analogRead(gas_digital);

  //ENVIANDO DATASTREAMS AO BLYNK
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, g);

  //CONDIÇÃO PARA O ACIONAMENTO DO ALARME
  if (t > 25 || g < 400) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);

    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);

    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);

    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);

    //ACIONANDO NOTIFICAÇÕES NO APP, CASO ENTRE NA CONDIÇÃO
    Blynk.logEvent("alerta_de_temperatura", "Temperatura acima de 20 graus.");
  } 

  else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }

  //ENVIANDO DADOS AO SERIAL PARA CONFERÊNCIA
  Serial.print("Temperatura : ");
  Serial.print(t);
  Serial.print("    Humidade : ");
  Serial.print(h);
  Serial.print("    Gas : ");
  Serial.println(g);
}

//DEFININDO AS SAÍDAS DOS COMPONENTES UTILIZADOS E INICIANDO A CONEXÃO COM O APP
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  dht.begin();

  //INTERVALO PARA ENVIAR DADOS AO APP E REALIZAR AS REQUISIÇÕES
  timer.setInterval(1000L, sendSensor);
}

void loop() {

  Blynk.run();
  timer.run();
}