#ifndef ANIMACAO_H
#define ANIMACAO_H

#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição do número de segmentos do display
#define NUM_SEGMENTOS 7

// Definição dos pinos dos segmentos
// Adapte para seus pinos
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6

// Tipo para representar o display
typedef uint8_t display_t;

// Tipo para representar o estado da animação
typedef enum {
    SEM_ANIMACAO,
    CONTANDO
} animacao_estado_t;

// Tipo para mapear dígitos para segmentos do display
typedef struct {
    uint8_t numeros[5][NUM_SEGMENTOS];
} display_map_t;

// Variáveis globais
extern volatile animacao_estado_t estado_animacao;
extern volatile uint8_t numero_atual;
extern display_map_t digitos_display;


// Protótipos das funções
void animacao_init(PIO pio, uint sm);
void animacao_incrementar_numero();
void animacao_decrementar_numero();
void animacao_atualizar_display(PIO pio, uint sm);
void animacao_callback_timer();

#endif