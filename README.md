# Sprint 4 - Challenge Hospital Sabará - Brinquedo com Painel Infantil de Atendimento com ESP32-C3 SuperMini e Display OLED usando FIWARE

## Mestre: 
- Professor Fábio Cabrini

## Membros do Grupo - **Moskitto**:
- [**Ana Luiza**](https://github.com/anarand) - RM561194
- [**Gabriel Couto**](https://github.com/rouri404) - RM559579
- [**Gabriel Kato**](https://github.com/kato8088) - RM560000
- [**João Vitor**](https://github.com/joaomatosq) - RM559246

## Objetivo
O projeto é composto por um brinquedo interativo impresso em 3D no formato de gatinho, equipado com um ESP32-C3 SuperMini e um display OLED. O brinquedo é entregue à criança junto com o responsável e exibe a senha de atendimento da criança, informando quando chegar o atendimento, tudo de forma lúdica e acolhedora. Na altura atual do projeto, serve como modelo de estilo e comportamento para o gatinho virtual, como se fosse um _digital twin_.

## Componentes Utilizados:
- ESP32-C3 SuperMini
- Display OLED - SSD1306 - Resolução de 128x64 pixels

## Tecnologias Utilizadas:
- FIWARE
  - MQTT (IoT Agent e Broker)
  - Orion Context Broker
  - MongoDB
  - STH-Comet
- Microsoft Azure
  - Máquina Virtual rodando o FIWARE (Debian/Linux)
  - Interface de Rede (IP Público)
- Linguagem de programação C++
- Docker (Containers FIWARE)

## Diagrama da Arquitetura
![Diagrama da Arquitetura](arquitetura_sprint4.png)

## Arquitetura da Solução

A solução é baseada em uma arquitetura de 3 camadas:

1. **IoT (Dispositivo Físico):**

Brinquedo em forma de gatinho, com:

- ESP32-C3 SuperMini
- Display OLED SSD1306 (128x64 pixels)

Realiza requisição HTTP GET para o Orion Context Broker a cada 20 segundos.

Atualiza o texto exibido conforme o valor do atributo text da entidade Display001.

2. **Back-End (FIWARE hosteado no Microsoft Azure)**

Componente/Container Orion Context Broker na porta 1026.

Armazena e disponibiliza a entidade Display001 com o atributo text, do tipo String.

Interface REST API via NGSIv2.

3. **Aplicação**

Painel web / aplicativo de gestão mobile que envia atualizações para o Context Broker via requisições HTTP (Postman por enquanto).

Comunicação via HTTP na porta 1026 com cabeçalhos Fiware-Service e Fiware-ServicePath.

## Link para a Simulação no Wokwi
<!-- ![Simulação](wokwi-simulação.png) -->
_2do_
<!-- Wokwi: https://wokwi.com/projects/428687533684130817 -->

<!-- ## :smile_cat: Explicação da Arquitetura
![Youtube](video-simulacao-youtube.png)

Youtube: https://youtu.be/tfh6tKAZBYQ

## :smile_cat: Video do Pitch
![Youtube](Gatinho-Sabará-youtube.png)

Youtube: https://www.youtube.com/watch?v=nGFiCgAD6WQ -->