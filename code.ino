#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
const int trigPin = 32;
const int echoPin = 33;

long duracao;
float distancia;

int distanciaBase = 400;  
int tolerancia = 50;      

int placarTimeA = 0;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const char* ssid = "Wokwi-GUEST"; // Rede Wi-Fi
const char* password = ""; // Senha da rede Wi-Fi
const char* apiKey = "TSKLIWRHNWLVAHXU"; // Write API Key
String server = "http://api.thingspeak.com/update?api_key=TSKLIWRHNWLVAHXU";

WiFiClient client;
HTTPClient http;

void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(ssid);
    Serial.println("Aguarde");
    reconectWiFi();

}

void setup() {
  Serial.begin(115200);
  lcd.init();       
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print("Bem vindo ao placar");
  initWiFi();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(5000);

}

void loop() {
  distancia = medirDistancia();

  String serverPath = server + "&field1=" + String(distancia);

  http.begin(client, serverPath.c_str());

  int httpResponseCode = http.GET();

    if(httpResponseCode > 0){
      Serial.print("Código HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else{
      Serial.print("Código de erro: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  if (distancia < (distanciaBase - tolerancia)) {
      placarTimeA++;
      lcd.setCursor(0,0);
      lcd.print("GOL! Placar Time A: ");
      lcd.setCursor(0,1);
      lcd.print(placarTimeA);
     
  }
}



int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
 
  return duracao * 0.034 / 2;
}


void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(ssid);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

