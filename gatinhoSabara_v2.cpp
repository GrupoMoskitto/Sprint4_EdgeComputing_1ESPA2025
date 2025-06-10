// Grupo Moskitto - FIAP 1ESPA
// Autores: Gabriel Kato, João Vitor de Matos, Gabriel Couto, Ana Luiza

#include <Wire.h>
#include <Adafruit_GFX.h>
#define SSD1306_NO_SPLASH 1
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>


#define SCREEN_WIDTH 128 // Largura do display OLED em pixels
#define SCREEN_HEIGHT 64 // Altura do display OLED em pixels
#define OLED_RESET -1    // Pino de reset (ou -1 se não usado)
#define OLED_ADDRESS 0x3C // Endereço I2C do OLED (0x3C ou 0x3D)

// Inicializa o display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// init lib zoinho
#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// URL direta para o atributo 'text' da entidade Display001
const char* serverName = "http://20.197.240.85:1026/v2/entities/Display001/attrs/text";

String textoAtual = "Esperando...";

void requisitarTexto(bool usarCabecalho = true) {
  HTTPClient http;
  http.begin(serverName);

  if (usarCabecalho) {
    http.addHeader("Fiware-Service", "default");
    http.addHeader("Fiware-ServicePath", "/");
  }

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("Código HTTP: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println("Resposta: " + payload);

    // Extrai valor do JSON no formato: {"value":"Texto Atual","type":"String"}
    int startIndex = payload.indexOf("\"value\":\"") + 9;
    int endIndex = payload.indexOf("\"", startIndex);

    if (startIndex > 8 && endIndex > startIndex) {
      textoAtual = payload.substring(startIndex, endIndex);
    } else {
      textoAtual = "Erro JSON";
    }

  } else {
    Serial.print("Erro HTTP: ");
    Serial.println(httpResponseCode);
    textoAtual = "Erro na conexão";
  }

  http.end();

  display.clearDisplay();
  display.setTextSize(1.5); // Tamanho do texto
  display.setTextColor(SSD1306_WHITE); // Cor do texto
// display.setCursor(eixo x, eixo y) em pixels;
  display.setCursor(0, 32); // Posição inicial do cursor
  display.print(textoAtual); // Imprime o texto

  display.display(); // Atualiza o display com o texto
}

void setup() {
  Serial.begin(115200);
  // init i2c
  Wire.begin(); 

  // conectando na rede wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado!");

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("Falha ao inicializar o display OLED"));
    for (;;); // Loop infinito se falhar
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // 100 = max framerate

  // Modo de operação automatico
  roboEyes.setAutoblinker(ON, 3, 2);
  roboEyes.setIdleMode(ON, 2, 2);
  

  display.display(); // Exibe buffer inicial vazio
  delay(1000); // Pausa para permitir que o display inicialize
  display.clearDisplay(); // Limpa o display
}

void loop() {
  // Executa a animação dos olhos por 2 segundos
  for (int i = 0; i < 280; i++) {
    roboEyes.update();
    delay(20); // 100 * 20 ms = 2 segundos
  }
  
  requisitarTexto();
  // Exibe o texto por 3 segundos
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 32);
  display.print(textoAtual);
  display.display();
  delay(7000);

  // Faz a requisição HTTP
  // removido pra nao dupar o ultimo frame
  //requisitarTexto();
}
