Control de Pantalla OLED con Raspberry Pi Pico

Este proyecto muestra cómo controlar una pantalla OLED (SSD1306) desde la Raspberry Pi Pico mediante I2C, con un ejemplo que despliega el mensaje "HOLA".

Requisitos

Raspberry Pi Pico
Pantalla OLED I2C (ej. SSD1306)
Conexiones I2C en GPIO 4 (SDA) y GPIO 5 (SCL) de la Pico.
Funcionalidades

Inicialización I2C para comunicación con la OLED.
Secuencia de Inicio: Configura la pantalla.
Limpieza de Pantalla: Borra el contenido de la OLED.
Dibujo de Caracteres: Usa una tabla de 8x8 pixeles para representar letras.
Dibujo de Texto: Permite mostrar palabras o frases.
Ejecución

Compila el código usando el SDK de Raspberry Pi Pico.
Carga el binario en la Pico para ver el mensaje en la pantalla OLED.
Ejemplo de Código

c
Copiar código
int main() {
    stdio_init_all();
    i2c_init_oled();
    oled_init();
    oled_clear();

    uint8_t line1[] = {H, O, L, A};
    oled_draw_text(2, 0, line1, sizeof(line1));
    
    return 0;
}
Este fragmento muestra el texto "HOLA" en la primera línea de la pantalla.
