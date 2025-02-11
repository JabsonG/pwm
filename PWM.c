#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

#define SERVO_PIN 22  // GPIO para controle do servo
#define PWM_FREQ 50   // Frequência do PWM (50Hz - período de 20ms)

volatile uint16_t current_pulse = 500; // Valor inicial para 0 graus
volatile int step = 5;                // Passo de incremento/decremento
volatile bool initial_pause_done = false; // Flag para indicar que as pausas iniciais foram concluídas

void pwm_wrap_isr() {
    pwm_clear_irq(pwm_gpio_to_slice_num(SERVO_PIN));
    pwm_set_gpio_level(SERVO_PIN, current_pulse);

    if (initial_pause_done) {
        if (current_pulse >= 2400 || current_pulse <= 500) {
            step = -step; // Inverte a direção ao atingir os limites
        }
        current_pulse += step; // Atualiza o pulso
    }
}

void set_servo_angle(uint16_t pulse_width) {
    current_pulse = pulse_width;
}

int main() {
    stdio_init_all();
    
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    
    // Configuração do PWM para frequência de 50Hz (20ms de período)
    pwm_set_wrap(slice_num, 20000);  // Período do PWM (20ms)
    pwm_set_clkdiv(slice_num, 125.0); // Reduz a frequência do clock para ajustar o PWM
    pwm_set_enabled(slice_num, true);
    
    // Configuração da interrupção do PWM
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_wrap_isr);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    
    // Pausas iniciais de 5 segundos em cada posição
    set_servo_angle(500);  // 0 graus
    sleep_ms(5000);
    set_servo_angle(1470); // 90 graus
    sleep_ms(5000);
    set_servo_angle(2400); // 180 graus
    sleep_ms(5000);

    // Após as pausas iniciais, inicia a movimentação suave contínua
    initial_pause_done = true;

    while (1) {
        // A movimentação suave é controlada pela interrupção do PWM
        // Nada mais precisa ser feito aqui
    }
}