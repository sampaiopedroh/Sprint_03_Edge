#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// -------------------- CONFIGURAÇÕES -------------------- //
// --- Credenciais Wi-Fi ---
const char* ssid = "";
const char* password = "";

// --- Credenciais MQTT ---
const char* mqttServer = "IP_server"; 
const int mqttPort = 1883;
const char* mqttUser = ""; // Se necessário
const char* mqttPassword = ""; // Se necessário

// --- Tópicos MQTT ---
const char* topicPrefix = "device001"; 
const char* topicSubscribe = "TEF/device001/cmd";
const char* topicPublishStatus = "TEF/device001/attrs";
const char* topicPublishDistance = "TEF/device001/attrs/distance";
const char* topicPublishPressure = "TEF/device001/attrs/pressure";
const char* topicPublishTemperature = "TEF/device001/attrs/temperature";
const char* topicPublishRPM = "TEF/device001/attrs/rpm";

// --- ID do dispositivo MQTT ---
const char* clientId = "fiware_001";

// --- Pinos GPIO ---
const int pinLed = 2;
const int pinTrigger = 18; 
const int pinEcho = 19;
const int pinPotentiometerPressure = 34; 
const int pinDHT = 4;  
const int pinPotentiometerRPM = 35; 

// --- Configurações DHT22 ---
#define DHTTYPE DHT22 
DHT dht(pinDHT, DHTTYPE);

// --- Variáveis Globais ---
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// -------------------- FUNÇÕES AUXILIARES -------------------- //

void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao Wi-Fi..");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT Broker... ");
    if (client.connect(clientId, mqttUser, mqttPassword)) { 
      Serial.println("Conectado!");
      client.subscribe(topicSubscribe); 
    } else {
      Serial.print("Falha! ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Implemente a lógica para lidar com comandos recebidos
  Serial.print("Mensagem recebida em: ");
  Serial.println(topic);
  Serial.print("Mensagem: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// -------------------- FUNÇÕES DOS SENSORES -------------------- //

float readDistance() {
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  long duration = pulseIn(pinEcho, HIGH);
  return (duration * 0.0343) / 2; 
}

int readPressure() {
  int sensorValue = analogRead(pinPotentiometerPressure);
  // Mapeie o valor do sensor (0-4095) para a faixa de pressão desejada
  int pressure = map(sensorValue, 0, 4095, 0, 100);  
  return pressure;
}

float readTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Falha na leitura do DHT22!");
    return -1.0;
  }
  return t;
}

int readRPM() {
  int sensorValue = analogRead(pinPotentiometerRPM);
  // Mapeie o valor do sensor (0-4095) para a faixa de RPM desejada
  int rpm = map(sensorValue, 0, 4095, 0, 1000); 
  return rpm;
}

// -------------------- SETUP -------------------- //

void setup() {
  Serial.begin(115200);

  // Inicializa o sensor de distância
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  // Inicializa o LED
  pinMode(pinLed, OUTPUT);

  // Inicializa o DHT22
  dht.begin();

  // Inicializa o Wi-Fi
  setup_wifi();

  // Inicializa o MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

// -------------------- LOOP PRINCIPAL -------------------- //

void loop() {
  if (!client.connected()) {
    reconnect(); 
  }
  client.loop(); 

  long now = millis();
  if (now - lastMsg > 2000) { // Publica a cada 2 segundos
    lastMsg = now;

    // Lê os valores dos sensores
    float distance = readDistance();
    int pressure = readPressure();
    float temperature = readTemperature();
    int rpm = readRPM();

    // Publica status "on"
    client.publish(topicPublishStatus, "s|on"); 

    // Publica as leituras dos sensores
    snprintf(msg, 50, "%.2f", distance);
    client.publish(topicPublishDistance, msg);

    snprintf(msg, 50, "%d", pressure);
    client.publish(topicPublishPressure, msg);

    snprintf(msg, 50, "%.2f", temperature);
    client.publish(topicPublishTemperature, msg);

    snprintf(msg, 50, "%d", rpm);
    client.publish(topicPublishRPM, msg);
  }
}
