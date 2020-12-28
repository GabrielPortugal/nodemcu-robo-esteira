// bibliotexas
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Servo.h>

//////////////////////////////////////////
// MQTT
//tópico MQTT de escuta (função na mqtt fica escutando)
#define TOPICO_SUBSCRIBE "MODIFICAR_ENVIO"
//tópico MQTT de envio
#define TOPICO_PUBLISH "MODIFICAR_ESCUTA"
//
#define ID_MQTT  "SEU_ID_MQTT"
//URL do broker MQTT que se deseja utilizar
const char* BROKER_MQTT = "broker.hivemq.com";
// Porta do Broker MQTT
int BROKER_PORT = 1883;

//////////////////////////////////////////
// WIFI
const char* ssid = "SUA_REDE_WIFI";
const char* password = "SENHA_WIFI";
WiFiClient espClient;
WiFiClient wifi;

//////////////////////////////////////////
// SERVOS
Servo servo_esteira_dir;
Servo servo_esteira_esq;
Servo servo_cabeca;

//////////////////////////////////////////
// VARIAVEIS
// Instancia o Cliente MQLeituraMqttCallbackTT passando o objeto espClient
PubSubClient MQTT(espClient);

#define pDireita D1
#define pEsquerda D2
#define pCabeca D3
#define buzzer D8

int dir_zero;
int dir_max_antihorario;
int dir_max_horario;
int esq_zero;
int esq_max_antihorario;
int esq_max_horario;
int cab_zero;
int cab_max_esquereda;
int cab_esquerda;

//////////////////////////////////////////
// FUNÇÕES
//Função: verifica o estado das conexões WiFI e ao broker MQTT.
// Em caso de desconexão (qualquer uma das duas), a conexão é
// refeita.
void VerificaConexoesWiFIEMQTT(void) {
  if (!MQTT.connected()) {
    if (ReconnectMQTT()) {
      PlayComunicadorRanger();
    }
  }
  ReconectWiFi();
}

//Função: transforma o playload do MQTT em JSON e trabalho em cima
void LeituraMqttCallback(byte* payload, unsigned int length) {
  // transformar payload em JSON
  StaticJsonDocument<256> doc;
  deserializeJson(doc, payload, length);

  String jsonMusica = doc["musica"];
  String jsonComando = doc["comando"];

  Serial.print("Musica: ");
  Serial.println(jsonMusica);
  Serial.print("CMD: ");
  Serial.println(jsonComando);
  Serial.println("***************************************");

  if (!jsonComando.equals("null")) {
    ComandoAndar(jsonComando);
  }
  if (!jsonMusica.equals("null")) {
    ComandoMusica(jsonMusica);
  }
}

//Função: envia comando para o MQTT
void EnviarMsgMQTT() {
  StaticJsonDocument<512> doc;
  doc["estacao"] = "123";
  char buffer[512];
  serializeJson(doc, buffer);
  Serial.println(buffer);
  if (MQTT.publish(TOPICO_PUBLISH, buffer) == true) {
    Serial.print("Mensagem enviada para: ");
    Serial.println(TOPICO_PUBLISH);
  } else {
    Serial.println("Erro ao enviar msg para mqtt");
  }
  Serial.println("***************************************");
}
//////////////////////////////////////////
void ComandoMusica(String cmd) {
  int index = cmd.toInt();
  switch (index) {
    case 1: PlayComunicadorRanger(); break;
    case 2: PlayCantinaSW(); break;
    case 3: PlayPiratasDoCaribe(); break;
    case 4: PlayMarchaImperial(); break;
    case 5: PlayStarWars(); break;
    case 6: PlayPoderosoChefao(); break;
    case 7: PlaySonic(); break;
    case 8: PlayTetris(); break;
    case 9: PlayPanteraRosa(); break;
    case 10: PlayTakeOnMe(); break;
  }
}
//////////////////////////////////////////
void ComandoAndar(String cmd) {
  Serial.print("COMANDO ANDAR: ");
  int index = cmd.toInt();
  Serial.println(index);
  switch (index) {
    case 1: AndarFrente(); break;
    case 2: VirarEsquerda(); break;
    case 3: MoverCabecaNao(); break;
    case 4: VirarDireita(); break;
    case 5: AndarTras(); break;
    case 6: ParadaTotal(); break;
  }
}
//////////////////////////////////////////
/*
    ARDUINO
*/
//////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);//buzzer
  delay(3000);

  InitWiFi();
  InitMQTT();

  dir_zero = 90;
  dir_max_antihorario = 360;
  dir_max_horario = 0;

  esq_zero = 90;
  esq_max_antihorario = 0;
  esq_max_horario = 180;

  cab_zero = 10;
  cab_max_esquereda = 180;
  cab_esquerda = 45;

  Serial.println("***********************");
  Serial.println("********* D6 **********");
  Serial.println("******* LIGADO ********");
  Serial.println("***********************");

  servo_cabeca.attach(pCabeca);
  servo_cabeca.write(cab_zero);

  PlayComunicadorRanger();
}

//////////////////////////////////////////
// LOOP
void loop()
{
  //garante funcionamento das conexões WiFi e ao broker MQTT
  VerificaConexoesWiFIEMQTT();

  // comandos comuns

  //keep-alive da comunicação com broker MQTT
  MQTT.loop();
}
