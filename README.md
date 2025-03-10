OLED Display Control with Raspberry Pi Pico

This project demonstrates how to control an OLED display (SSD1306) using the Raspberry Pi Pico via I2C, with an example that displays the message "HOLA".

Requirements

Raspberry Pi Pico
I2C OLED Display (e.g., SSD1306)
I2C connections on GPIO 4 (SDA) and GPIO 5 (SCL) of the Pico.
Features

I2C Initialization for OLED communication.
Startup Sequence: Configures the OLED display.
Screen Clearing: Clears the OLED content.
Character Rendering: Uses an 8x8 pixel table to display letters.
Text Rendering: Displays words or phrases on the OLED.
