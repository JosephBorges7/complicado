#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pio_matrix.pio.h"
#include "Leds.h"
#include "Buttons.h"
#include "animacao.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

#define BOTAO_INCREMENTA 14
#define BOTAO_DECREMENTA 15

// Variável para controlar o estado do LED vermelho
bool led_vermelho_on = false;

// Variável para armazenar o timer
struct repeating_timer timer_led_vermelho;

// Função de callback para piscar o LED vermelho
bool piscar_led_vermelho_callback(struct repeating_timer *t) {
    led_vermelho_on = !led_vermelho_on; // Inverte o estado do LED
    gpio_put(LED_VERMELHO, led_vermelho_on); // Define o pino do LED com o novo estado
    return true; // Continua o timer
}

int main() {
    // Inicialização padrão do stdio
    stdio_init_all();

    // Inicializa os LEDs
    leds_init(LED_VERMELHO, LED_AMARELO, LED_VERDE);

    // Inicializa os botões
    buttons_init(BOTAO_INCREMENTA, BOTAO_DECREMENTA);

    // Inicializa o display de 7 segmentos e o timer
    animacao_init(pio0, 0); // Assumindo pio0 e sm 0. Adapte conforme necessário

    // Configurações da PIO
    PIO pio = pio0; // Use pio0 ou pio1 conforme necessário
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_VERMELHO); // Corrigido

    // Configura o timer para piscar o LED vermelho a cada 200ms (5 vezes por segundo)
    add_repeating_timer_ms(200, piscar_led_vermelho_callback, NULL, &timer_led_vermelho);

    // Loop principal
    while (true) {
        // Verifica se o botão de incrementar foi pressionado
        if (button_is_pressed(BOTAO_INCREMENTA)) {
            sleep_ms(50); // Pequeno debounce
            animacao_incrementar_numero();
        }

        // Verifica se o botão de decrementar foi pressionado
        if (button_is_pressed(BOTAO_DECREMENTA)) {
            sleep_ms(50); // Pequeno debounce
            animacao_decrementar_numero();
        }

        // Adiciona um pequeno delay para evitar leituras excessivas
        sleep_ms(10);
    }

    return 0;
}
