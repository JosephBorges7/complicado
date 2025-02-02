# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importação do SDK da Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Definir nome do projeto
project(Leds C CXX ASM)

# Inicializa o SDK da Pico
pico_sdk_init()

# Adicionar executável
add_executable(Leds 
    src/main.c 
    src/Leds.c 
    src/Buttons.c
)

# Define nome e versão do programa
pico_set_program_name(Leds "Leds")
pico_set_program_version(Leds "0.1")

# Gerar cabeçalho do programa PIO
pico_generate_pio_header(Leds ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# Habilita comunicação via USB/UART
pico_enable_stdio_uart(Leds 1)
pico_enable_stdio_usb(Leds 1)

# Adicionar bibliotecas padrão e de hardware
target_link_libraries(Leds 
    pico_stdlib 
    hardware_pio 
    hardware_gpio
)

# Incluir diretórios necessários
target_include_directories(Leds PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# Gera arquivos de saída extras (.uf2, .bin, .hex)
pico_add_extra_outputs(Leds)
