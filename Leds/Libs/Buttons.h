#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

// Definição dos pinos dos botões
#define BOTAO_A_PIN  // Defina o pino GPIO do Botão A
#define BOTAO_B_PIN // Defina o pino GPIO do Botão B

// Estados dos botões
typedef enum {
    BOTAO_LIBERADO,
    BOTAO_PRESSIONADO
} botao_estado_t;

// Variáveis globais para os estados dos botões (se necessário)
extern volatile botao_estado_t estado_botao_A;
extern volatile botao_estado_t estado_botao_B;
extern volatile bool flag_botao_A;
extern volatile bool flag_botao_B;


// Protótipos das funções
void botao_init();
void gpio_irq_handler(uint gpio, uint32_t events);


#endif