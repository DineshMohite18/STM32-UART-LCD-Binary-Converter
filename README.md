# STM32-UART-LCD-Binary-Converter
STM32 project to convert decimal input from UART into binary and display on 16x2 LCD
# STM32 Number to Binary Converter using LCD

## About this project

This project is a small embedded system where I can enter a number from my laptop (using UART), and the STM32 converts it into binary and shows it on a 16x2 LCD.

I built this after learning basic LCD interfacing, to understand how input, processing, and output work together in embedded systems.

---

## How it works

* I type a number in serial terminal (PuTTY)
* STM32 receives it using UART
* The input string is converted into an integer
* The number is converted into binary
* The result is displayed on the LCD

---

## Example

Input:
25

Output on LCD:

Num:25
Bin:11001

---

## What I learned

* UART communication with STM32
* Handling strings in embedded C
* Using functions like `atoi()`
* Converting decimal to binary
* Displaying dynamic data on LCD

---

## Hardware used

* STM32F446RE (Nucleo board)
* 16x2 LCD (8-bit mode)
* USB cable (UART via ST-Link)
* Breadboard and jumper wires

---

## LCD connections

### Data pins

D0 → PA10
D1 → PB3
D2 → PB5
D3 → PB4
D4 → PB10
D5 → PA8
D6 → PA9
D7 → PC7

### Control pins

RS → PB6
RW → PA7
EN → PA6

---

## Project structure

Core/ → main code
Drivers/ → HAL drivers

---

## Future improvements

* Add HEX and OCTAL conversion
* Display input while typing
* Use UART interrupt instead of polling
* Convert to I2C LCD

---

## Author

Dinesh Mohite
