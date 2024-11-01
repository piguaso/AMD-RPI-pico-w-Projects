#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define OLED_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_CMD 0x00
#define OLED_DATA 0x40

// Caracteres comunes en formato 8x8
uint8_t characters[][8] = {
    {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // H
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // O
    {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00}, // L
    {0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // A
    {0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, // P
    {0x7C, 0x66, 0x66, 0x7C, 0x70, 0x68, 0x66, 0x00}, // R
    {0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00}, // E
    {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00}, // B
    {0x3E, 0x60, 0x60, 0x3C, 0x06, 0x06, 0x7C, 0x00}, // S
    {0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00}, // F
};

// Índices para encontrar caracteres en la tabla
enum {H = 0, O, L, A, P, R, E, B, S, F};

// Inicializar I2C para el OLED
void i2c_init_oled() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
}

// Enviar comando al OLED
void oled_send_command(uint8_t cmd) {
    uint8_t data[2] = {OLED_CMD, cmd};
    i2c_write_blocking(I2C_PORT, OLED_ADDR, data, 2, false);
}

// Inicializar OLED
void oled_init() {
    uint8_t init_sequence[] = {0xAE, 0x20, 0x00, 0xB0, 0xC8, 0x00, 0x10, 0x40, 0x81, 0xFF, 
                               0xA1, 0xA6, 0xA8, 0x3F, 0xA4, 0xD3, 0x00, 0xD5, 0xF0, 0xD9, 
                               0x22, 0xDA, 0x12, 0xDB, 0x20, 0x8D, 0x14, 0xAF};
    for (int i = 0; i < sizeof(init_sequence); i++) {
        oled_send_command(init_sequence[i]);
    }
}

// Limpiar pantalla
void oled_clear() {
    for (int page = 0; page < 8; page++) {
        oled_send_command(0xB0 + page);
        oled_send_command(0x00);
        oled_send_command(0x10);
        for (int col = 0; col < OLED_WIDTH; col++) {
            uint8_t data[2] = {OLED_DATA, 0x00};
            i2c_write_blocking(I2C_PORT, OLED_ADDR, data, 2, false);
        }
    }
}

// Dibujar carácter en una posición dada
void oled_draw_char(uint8_t page, uint8_t col, uint8_t char_index) {
    oled_send_command(0xB0 + page);
    oled_send_command(0x00 + (col & 0x0F));
    oled_send_command(0x10 + (col >> 4));
    for (int i = 0; i < 8; i++) {
        uint8_t data[2] = {OLED_DATA, characters[char_index][i]};
        i2c_write_blocking(I2C_PORT, OLED_ADDR, data, 2, false);
    }
}

// Dibujar texto a partir de una serie de índices de caracteres en una posición dada
void oled_draw_text(uint8_t page, uint8_t start_col, uint8_t text[], int length) {
    for (int i = 0; i < length; i++) {
        oled_draw_char(page, start_col + (i * 8), text[i]);
    }
}

int main() {
    stdio_init_all();
    i2c_init_oled();
    oled_init();
    oled_clear();

    // Texto "HOLA PROFE" en la primera línea
    uint8_t line1[] = {H, O, L, A};
    oled_draw_text(2, 0, line1, sizeof(line1));
    
    return 0;
}
