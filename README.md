# Controle de Servomotor com PWM na Raspberry Pi Pico W

## Descrição
Este projeto implementa o controle de um servomotor utilizando o módulo PWM do microcontrolador RP2040 da Raspberry Pi Pico W. Além disso, o código integra o LED RGB da ferramenta educacional BitDogLab, utilizando a GPIO 12 para indicar a posição do servo.

## Configuração do PWM
- **Frequência do PWM**: 50Hz**:
   - Ciclo ativo: 2400µs**:
   - Ciclo ativo: 1470µs**:
   - Ciclo ativo: 500µs
- Após a movimentação inicial, o servo oscila entre 0° e 180°
- O ciclo ativo é alterado em incrementos de ±5µs
- A cada ajuste, há um atraso de 10ms para suavizar o movimento

## LED RGB na GPIO 12 – Experimento com BitDogLab
- O LED acende para ângulos altos do servo (acima de 2000µs)
- O LED apaga para ângulos baixos do servo (abaixo de 2000µs)
- **Observação**: O comportamento do LED permite visualizar a posição do servo sem necessidade de um monitor serial ou osciloscópio.

## Como Executar
1. **Compilar o código** utilizando o Pico SDK
2. **Fazer upload do binário** para a Raspberry Pi Pico W
3. **Executar no simulador Wokwi** ou conectar os componentes reais

## Dependências
- **Pico SDK**
- **Simulador Wokwi** (opcional)

## Vídeo demonstrativo:

https://drive.google.com/file/d/1eqvxE_3QjpgXLYOC9KLCK1v6J8PQmUzD/view?usp=sharing

