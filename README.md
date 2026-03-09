# 🚦 Semáforo Inteligente com Arduino

Sistema de semáforo para pedestres com botão de acionamento, display LCD, servo motor (cancela), buzzer sonoro e LEDs indicadores.

---

## 📸 Diagrama do Circuito

<img width="2019" height="1287" alt="image" src="https://github.com/user-attachments/assets/6df0fc7f-802d-4468-a7c6-a6f37d831272" />


---

## 🧰 Componentes Utilizados

| Componente              | Quantidade | Observação                        |
|-------------------------|------------|-----------------------------------|
| Arduino UNO             | 1          | Microcontrolador principal        |
| Display LCD 16x2 I2C    | 1          | Endereço I2C: `0x27`              |
| Servo Motor             | 1          | Simula cancela de pedestre        |
| Buzzer                  | 1          | Sinal sonoro para deficientes visuais |
| LED Vermelho            | 2          | Carro (pino 12) e pedestre (pino 9) |
| LED Amarelo             | 1          | Carro (pino 11)                   |
| LED Verde               | 2          | Carro (pino 10) e pedestre (pino 8) |
| Botão (push button)     | 1          | Acionamento da travessia          |
| Resistores 220Ω         | 5          | Um para cada LED                  |
| Protoboard              | 1          | —                                 |
| Jumpers                 | Vários     | —                                 |

---

## 📌 Mapeamento de Pinos

| Pino | Função                |
|------|-----------------------|
| 12   | LED vermelho (carro)  |
| 11   | LED amarelo (carro)   |
| 10   | LED verde (carro)     |
| 9    | LED vermelho (pedestre) |
| 8    | LED verde (pedestre)  |
| 5    | Servo motor (cancela) |
| 4    | Buzzer                |
| 2    | Botão de travessia    |
| A4   | SDA (LCD I2C)         |
| A5   | SCL (LCD I2C)         |

---

## 📚 Bibliotecas Necessárias

Instale via **Arduino IDE → Gerenciar Bibliotecas**:

- [`Wire`](https://www.arduino.cc/reference/en/libraries/wire/) *(nativa)*
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C)
- [`Servo`](https://www.arduino.cc/reference/en/libraries/servo/) *(nativa)*

---

## ⚙️ Como Funciona

### Estado inicial
- LED verde do carro aceso → trânsito liberado
- LED vermelho do pedestre aceso → travessia bloqueada
- Servo aberto (0°)
- LCD exibe: `AGUARDE...`

### Fluxo ao pressionar o botão

```
Botão pressionado (com debounce de 5s)
        ↓
LED amarelo do carro (2s)
        ↓
LED vermelho do carro + cancela fecha (servo 90°)
        ↓
LED verde do pedestre
LCD: "TRAVESSIA LIVRE | TEMPO: Xs"
Buzzer: bip a cada segundo (5s no total)
        ↓
Pisca LED verde do pedestre (alerta de fechamento)
LCD: "ATENCAO! | FECHANDO..."
        ↓
LED vermelho do pedestre
LCD: "PARE! | NAO ATRAVESSE"
        ↓
LED amarelo do carro (1s)
        ↓
LED verde do carro + cancela abre (servo 0°)
LCD: "AGUARDE..."
```

---

## 🔌 Como Montar

1. Conecte os LEDs aos pinos indicados com resistores de 220Ω em série.
2. Conecte o servo ao pino 5 (sinal), 5V e GND.
3. Conecte o buzzer ao pino 4 e GND.
4. Conecte o botão entre o pino 2 e 5V *(usando `INPUT` com pull-down externo ou ajuste para `INPUT_PULLUP` no código)*.
5. Conecte o display LCD I2C aos pinos SDA (A4) e SCL (A5), além de 5V e GND.

---

## 🚀 Como Usar

1. Clone ou baixe este repositório.
2. Abra o arquivo `.ino` na Arduino IDE.
3. Instale as bibliotecas listadas acima.
4. Selecione a placa **Arduino UNO** e a porta correta.
5. Faça o upload do código.
6. Pressione o botão na protoboard para acionar a travessia de pedestres.

---

## 📁 Estrutura do Projeto

```
semaforo-arduino/
├── semaforo.ino       # Código principal
├── README.md          # Este arquivo
```

---

## 📝 Observações

- O debounce do botão é feito por software com intervalo mínimo de **5 segundos** entre acionamentos.
- O tempo de travessia padrão é de **5 segundos** (`crossTime = 5000`).
- O endereço I2C do LCD pode variar (`0x27` ou `0x3F`). Use um scanner I2C se o display não inicializar.
- Os textos no LCD estão sem acentuação para compatibilidade com displays padrão.

---

## 🛡️ Licença

Este projeto é de uso livre para fins educacionais.
