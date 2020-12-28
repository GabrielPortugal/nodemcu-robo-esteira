//Função: inicializa parâmetros de conexão MQTT(endereço do broker, 
// porta e seta função de callback)
void InitMQTT() {
  //informa qual broker e porta deve ser conectado
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
  MQTT.setCallback(mqtt_callback);
}

//Função: função de callback esta função é chamada toda vez que uma
// informação de um dos tópicos subescritos chega
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  LeituraMqttCallback(payload, length);
}

//Função: reconecta-se ao broker MQTT (caso ainda não esteja
// conectado ou em caso de a conexão cair) em caso de sucesso na
// conexão ou reconexão, o subscribe dos tópicos é refeito.
bool ReconnectMQTT()
{
  while (!MQTT.connected())
  {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT))
    {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPICO_SUBSCRIBE);
      Serial.println("***************************************");
      return true;
    }
    else
    {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Havera nova tentatica de conexao em 2s");
      Serial.println("***************************************");
      return false;
      delay(2000);
    }
  }
}
