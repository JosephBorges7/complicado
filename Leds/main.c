#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "pio_matrix.pio.h"
#include "Leds.h"
#include "Buttons.h"
#include "animacao.h"

#define LED_MATRIX_PIN 7
#define BOTAO_A_PIN 14 // Pino do Botão A
#define BOTAO_B_PIN 15 // Pino do Botão B


int main() {
    stdio_init_all();

    // Inicialização dos botões
    botao_init();
    
    // Inicialização da animação do display
    animacao_init(pio0, 0); // Inicializa o display de 7 segmentos

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);

    pio_matrix_program_init(pio, sm, offset, LED_MATRIX_PIN);
    pio_gpio_init(pio, LED_MATRIX_PIN);
    pio_sm_set_consecutive_pindirs(pio, sm, LED_MATRIX_PIN, 1, true); // Configura o pino como saída

    pixel leds[PIXELS]; // Declara um array de pixels
    float intensity = 0.5; // Define a intensidade dos LEDs
    int led_pattern = 0; // Variável para controlar o padrão dos LEDs

    while (true) {
        
        // Verifica se o botão A foi pressionado
        if (flag_botao_A) {
            flag_botao_A = false; // Reseta a flag
           if (estado_botao_A == BOTAO_PRESSIONADO){
               led_pattern = (led_pattern + 1) % 3; // Altera o padrão de LEDs
               animacao_incrementar_numero(); // Incrementa o número do display
           }
        }
        
        // Verifica se o botão B foi pressionado
         if (flag_botao_B) {
            flag_botao_B = false; // Reseta a flag
           if (estado_botao_B == BOTAO_PRESSIONADO){
             led_pattern = (led_pattern == 0) ? 2: led_pattern -1; // Altera o padrão de LEDs para trás
             animacao_decrementar_numero();// Decrementa o número do display
           }
        }
        
        // Define o padrão dos LEDs
          switch (led_pattern) {
            case 0: // Padrão 1: LEDs vermelhos
               for (int i = 0; i < PIXELS; i++) {
                 leds[i].red = 255;
                 leds[i].green = 0;
                 leds[i].blue = 0;
               }
                break;
             case 1: // Padrão 2: LEDs verdes
                for (int i = 0; i < PIXELS; i++) {
                    leds[i].red = 0;
                    leds[i].green = 255;
                    leds[i].blue = 0;
                }
                  break;
             case 2: // Padrão 3: LEDs azuis
                 for (int i = 0; i < PIXELS; i++) {
                    leds[i].red = 0;
                    leds[i].green = 0;
                   leds[i].blue = 255;
                }
                break;
         }

        draw_pio(leds, pio, sm, intensity); // Envia os dados para a matriz de LEDs
        
    }
    return 0;
}