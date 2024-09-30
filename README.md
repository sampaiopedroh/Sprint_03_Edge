# Fórmula E: Coleta e Transmissão de Dados em Tempo Real com Edge Computing
-> Descrição do Projeto:

  Este projeto explora os benefícios da Edge Computing na Fórmula E, a categoria de automobilismo totalmente elétrica, para coletar e transmitir dados em tempo real, proporcionando insights valiosos para equipes e fãs.
  A aplicação IoT desenvolvida visa coletar dados relevantes sobre o desempenho dos carros durante a corrida, incluindo:
  - Distância entre carros: Através de sensores ultrassônicos, monitora a distância entre o carro e seus competidores, permitindo análises estratégicas de ultrapassagem e posicionamento na pista.
  - Temperatura em pontos estratégicos: Sensores de temperatura instalados em pontos críticos, como pneus e freios, monitoram o aquecimento, auxiliando na prevenção de falhas e otimização do desempenho.
  - Pressão dos pneus: Sensores instalados nos pneus monitoram a pressão em tempo real, permitindo ajustes precisos para maximizar a aderência e a vida útil dos pneus.
  - Rotação dos pneus (RPM): Sensores medem a rotação dos pneus, fornecendo informações importantes sobre a velocidade, aceleração e comportamento do carro em curvas.

Os dados coletados são processados em um dispositivo ESP32 e transmitidos para um servidor em nuvem (AWS) via MQTT, possibilitando o monitoramento e análise em tempo real por equipes e fãs.

-> Arquitetura da Solução:

  O projeto utiliza uma arquitetura de Edge Computing, com os seguintes componentes:
- Dispositivos IoT:
  + ESP32: Microcontrolador responsável por coletar dados dos sensores, processá-los e transmiti-los para o servidor na nuvem.
  + Sensores Ultrassônicos: Medem a distância entre carros.
  + Sensores de Temperatura: Monitoram a temperatura em pontos estratégicos.
  + Potenciômetro para Pressão: Simula sensores de pressão nos pneus (para fins de demonstração).
  + Potenciômetro para RPM: Simula sensores de rotação dos pneus (para fins de demonstração).

- Back-end:
  + Servidor MQTT (AWS): Recebe e processa os dados enviados pelos dispositivos IoT.
  + Banco de Dados: Armazena os dados para análise posterior.

- Front-end:
  + Dashboards: Interface web para visualização dos dados em tempo real, permitindo acompanhamento do desempenho do carro e tomada de decisões estratégicas.

-> Recursos Necessários:

- Hardware:
  + Placa ESP32
  + Sensores Ultrassônicos
  + Sensores de Temperatura (DHT22)
  + Potenciômetros (para simulação de pressão e RPM)
  + Cabos Jumper

- Software:
  + Arduino IDE
  + Bibliotecas para ESP32: WiFi.h, PubSubClient.h, DHT.h
  + Plataforma de Nuvem AWS
  + Insomnia (ou similar) para testes de API REST

-> Instruções de Uso:
- Configurar o ambiente de desenvolvimento: Instalar o Arduino IDE e as bibliotecas necessárias para ESP32.
- Configurar a placa ESP32: Conectar os sensores e configurar o código com as credenciais de WiFi e MQTT.
- Criar instância na AWS: Configurar uma instância EC2 com Ubuntu Server e instalar o broker MQTT (Mosquitto).
- Desenvolver o back-end: Implementar a lógica para receber, processar e armazenar os dados enviados pelo ESP32.
- Desenvolver o front-end: Criar dashboards interativos para visualização dos dados.

-> Requisitos:
 - Conhecimento básico de programação em C++
  - Familiaridade com o ecossistema Arduino
  - Noções de IoT e Edge Computing
  - Conhecimento básico de AWS

-> Dependências:
  - Bibliotecas Arduino para ESP32: WiFi.h, PubSubClient.h, DHT.h

-> Informações Adicionais:
  - O código fonte completo do projeto está disponível neste repositório.
  - O projeto pode ser expandido com a adição de novos sensores e funcionalidades.
  - A visualização dos dados pode ser aprimorada com o uso de ferramentas de análise e dashboards customizados.

-> Contato:
  - Nome do Grupo: InnotechHub
  - Membros:
  + Davi Vieira (556798) 
  + Felipe Alamino (558819) 
  + Luca Monteiro (556906) 
  + Pedro Sampaio (555613) 

-> Agradecimentos:
  Tech Mahindra pela oportunidade de desenvolver este projeto inovador e contribuir para o futuro da Fórmula E.
