# ⚽ Sprint3-Edge

Este projeto implementa um **placar eletrônico automatizado** utilizando **ESP32**, um **sensor ultrassônico** e um **display LCD I2C**.  
A cada vez que a bola atravessa a área configurada, o placar é atualizado em tempo real no display e os dados também são enviados para a nuvem via **ThingSpeak**.  

---

## 📌 Funcionamento  

1. O **sensor ultrassônico (HC-SR04)** mede a distância em frente ao gol.  
2. Quando a distância detectada é menor que o limite definido (`distanciaBase - tolerancia`), considera-se que houve um **gol**.  
3. O **placar do Time A** é atualizado e exibido no LCD.  
4. O ESP32 envia os dados para a plataforma **ThingSpeak**, permitindo monitoramento remoto.  

---

## ⚙️ Tecnologias Utilizadas  

- **ESP32** (processamento e conexão Wi-Fi)  
- **Sensor Ultrassônico HC-SR04** (medição de distância)  
- **Display LCD I2C (16x2)**  
- **ThingSpeak** (coleta e visualização dos dados)  

---

## 📊 Estrutura Lógica do Código  

- **Função `medirDistancia()`**: calcula a distância com base no tempo do pulso ultrassônico.  
- **Loop principal (`loop`)**:  
  - Mede a distância.  
  - Envia o valor para o ThingSpeak.  
  - Atualiza o placar quando a bola passa pela linha do gol.  
- **Função `initWiFi()`** e `reconectWiFi()`: estabelecem e monitoram a conexão com a rede.  

---

## 🚨 Limitações do Sensor Ultrassônico  

Apesar de funcionar para o protótipo, o **sensor ultrassônico apresenta limitações em um cenário real de jogo**:  

- ❌ **Interferência**: o som pode se dispersar ou ser bloqueado por outros objetos além da bola.  
- ❌ **Ângulo limitado**: a bola pode passar pelo canto e não ser detectada corretamente.  
- ❌ **Sensibilidade ao ambiente**: barulho, vento e superfícies irregulares podem gerar leituras falsas.  
- ❌ **Velocidade da bola**: o tempo de resposta do ultrassônico pode não acompanhar uma bola em movimento rápido.  

---

## ✅ Por que usar um Sensor Infravermelho (IR) é melhor?  

O **sensor infravermelho** é mais adequado para detecção de gols, pois:  

- 🔹 **Maior precisão**: detecta a interrupção do feixe de luz de forma imediata, sem depender de cálculos de tempo.  
- 🔹 **Resposta instantânea**: consegue identificar bolas passando em alta velocidade.  
- 🔹 **Menos interferência**: não sofre com barulho, vento ou superfícies reflexivas.  
- 🔹 **Cobertura total**: pode ser instalado como uma barreira no gol, garantindo que qualquer bola que cruze a linha seja detectada.  

---

## 🚀 Melhorias Futuras  

- Substituir o **sensor ultrassônico** por **sensores IR** dispostos em linha na trave do gol.  
- Implementar **placar para os dois times**.  
- Adicionar **servidor web local** para visualização do placar em tempo real.  
- Usar **buzzer ou LEDs** para indicar gol com efeitos visuais/sonoros.  

---

## 👨‍💻 Autores  

- Beatriz Cortez - RM561431
 
- Bruno Alves - RM563986
 
- Gabriel Augusto - RM564126
 
- Gustavo Moura - RM566190
 
- Pedro Henrique - RM563281