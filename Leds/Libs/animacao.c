#include "animacao.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/timer.h"


// Variáveis globais (definidas em animacao.h)
volatile animacao_estado_t estado_animacao = SEM_ANIMACAO;
volatile uint8_t numero_atual = 0;
display_map_t digitos_display;


// Variável para armazenar a estrutura do timer
struct repeating_timer timer;
// Mapeamento dos dígitos para os segmentos do display
const uint8_t digits[1][2] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
};



// Função de callback do timer
bool animacao_callback_timer(struct repeating_timer *t) {
    if (estado_animacao == CONTANDO) {
        animacao_atualizar_display(pio0, 0); // Assumindo pio0 e sm 0. Adapte conforme necessário
    }
    return true;
}


// Função para inicializar a animação
void animacao_init(PIO pio, uint sm) {

  // Inicializa o mapeamento dos dígitos do display
  for(int i = 0; i< 10; i++){
    for(int j = 0; j < NUM_SEGMENTOS; j++){
        digitos_display.numeros[j] = digits[i][j];
    }
  }

    // Inicializar os pinos GPIO do display como saídas
    gpio_init(SEG_A);
    gpio_set_dir(SEG_A, GPIO_OUT);
    gpio_init(SEG_B);
    gpio_set_dir(SEG_B, GPIO_OUT);
    gpio_init(SEG_C);
    gpio_set_dir(SEG_C, GPIO_OUT);
    gpio_init(SEG_D);
    gpio_set_dir(SEG_D, GPIO_OUT);
    gpio_init(SEG_E);
    gpio_set_dir(SEG_E, GPIO_OUT);
    gpio_init(SEG_F);
    gpio_set_dir(SEG_F, GPIO_OUT);
    gpio_init(SEG_G);
    gpio_set_dir(SEG_G, GPIO_OUT);


    // Inicializar o timer de hardware para 100ms (ajuste conforme necessário)
   add_repeating_timer_ms(100, animacao_callback_timer, NULL, &timer);

}


// Função para incrementar o número
void animacao_incrementar_numero() {
    numero_atual = (numero_atual + 1) % 10; // Reinicia a contagem ao atingir 9
     estado_animacao = CONTANDO;
}


// Função para decrementar o número
void animacao_decrementar_numero() {
    numero_atual = (numero_atual == 0) ? 9 : numero_atual - 1; // Vai para 9 se for 0
    estado_animacao = CONTANDO;
}



// Função para atualizar o display de sete segmentos
void animacao_atualizar_display(PIO pio, uint sm) {
  // Desliga todos os segmentos
    gpio_put(SEG_A, 0);
    gpio_put(SEG_B, 0);
    gpio_put(SEG_C, 0);
    gpio_put(SEG_D, 0);
    gpio_put(SEG_E, 0);
    gpio_put(SEG_F, 0);
    gpio_put(SEG_G, 0);

    // Use o valor de numero_atual para acessar o mapeamento correto
    // e acende os segmentos corretos
      gpio_put(SEG_A, digitos_display.numeros);
      gpio_put(SEG_B, digitos_display.numeros[3]);
      gpio_put(SEG_C, digitos_display.numeros[4]);
      gpio_put(SEG_D, digitos_display.numeros[5]);
      gpio_put(SEG_E, digitos_display.numeros[6]);
      gpio_put(SEG_F, digitos_display.numeros[7]);
      gpio_put(SEG_G, digitos_display.numeros[8]);


    estado_animacao = SEM_ANIMACAO; //reseta a animacao após atualizar o display
}