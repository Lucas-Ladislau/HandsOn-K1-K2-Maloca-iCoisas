#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

//INSTALE A BIBLIOTECA URLENCODE
const char* ssid = "SSID";
const char* password = "SENHA";

#define botao 21
#define led1 23
#define led2 2

bool flag = 1;

String phoneNumber = "+(NUM PAÍS+DD+NUMERO)";
String apiKey = "apikey1";
String phoneNumber2 = "+(NUM PAÍS+DD+NUMERO)";
String apiKey2 = "apikey2";
String phoneNumber3 = "+(NUM PAÍS+DD+NUMERO)";
String apiKey3 = "apikey3";

void sendMessage(String phoneNumber, String apiKey, String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber +  "&text=" + urlEncode(message) +"&apikey=" + apiKey ;
  HTTPClient http;
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.println("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

//A melhoria é a de poder obter a localização baseada no IP
String obterLocalizacaoPorIP() {
  HTTPClient http;
  http.begin("http://ip-api.com/json/"); 
  int httpCode = http.GET();
  String resposta;

  if (httpCode > 0) {
    resposta = http.getString(); 
  } else {
    resposta = "Erro ao obter localização: " + String(httpCode);
  }

  http.end();
  return resposta;
}

void setup() {
  Serial.begin(115200);

  pinMode(botao, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);

  WiFi.begin(ssid, password);
  Serial.println("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(led2,!digitalRead(led2));
  }

  Serial.println("");
  Serial.print("Conectado ao WiFi neste IP ");  
  digitalWrite(led2,HIGH);
  Serial.println(WiFi.localIP());
}

void loop() {

  int estado_botao = digitalRead(botao);

  if (estado_botao == 0) {
    Serial.println("Botão Pressionado, enviando mensagem....");
    digitalWrite(led1,HIGH);
    if (flag) {
      String localizacao = obterLocalizacaoPorIP();
      sendMessage(phoneNumber, apiKey,"Preciso de Ajuda Minha localização: "+localizacao);
      sendMessage(phoneNumber2, apiKey2,"HELPPP");
      sendMessage(phoneNumber3, apiKey3,"ME AJUDAAAA");
      flag = 0;
    }
  } else {
    flag = 1;
    digitalWrite(led1, LOW);
  }
}