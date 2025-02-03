#include "Buttons.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"


// Variáveis globais para os estados dos botões
volatile botao_estado_t estado_botao_A = BOTAO_LIBERADO;
volatile botao_estado_t estado_botao_B = BOTAO_LIBERADO;
volatile bool flag_botao_A = false;
volatile bool flag_botao_B = false;

// Função de inicialização dos botões
void botao_init() {
  // Inicializa o GPIO para os botões A e B como entrada com resistor de pull-up
  gpio_init(BOTAO_A_PIN);
  gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
  gpio_pull_up(BOTAO_A_PIN);

  gpio_init(BOTAO_B_PIN);
  gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
  gpio_pull_up(BOTAO_B_PIN);

  // Configura as interrupções para os botões A e B
  gpio_set_irq_enabled_with_callback(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  gpio_set_irq_enabled_with_callback(BOTAO_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}


void gpio_irq_handler(uint gpio, uint32_t events) {
    if (gpio == BOTAO_A_PIN) {
          // Atualiza o estado do botão A e seta a flag
        estado_botao_A = (gpio_get(BOTAO_A_PIN) == 0) ? BOTAO_PRESSIONADO : BOTAO_LIBERADO;
         flag_botao_A = true;
    } else if (gpio == BOTAO_B_PIN) {
        // Atualiza o estado do botão B e seta a flag
        estado_botao_B = (gpio_get(BOTAO_B_PIN) == 0) ? BOTAO_PRESSIONADO : BOTAO_LIBERADO;
        flag_botao_B = true;
    }
}