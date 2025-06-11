# LED Matrix DOE Project

This project implements various visual effects on an LED matrix using the Raspberry Pi Pico (RP2040). It features firefly simulation with flocking behavior and wave effects, controlled through a custom MBI5252 LED driver implementation.

## Features

- **Firefly Simulation**: Implements a flocking algorithm where fireflies move as a cohesive group, exhibiting natural collective behavior
- **Wave Effect**: Dynamic wave patterns that ripple across the LED matrix
- **Custom LED Driver**: Implementation of the MBI5252 LED driver using PIO (Programmable I/O) for efficient control

## Hardware Setup

### Pin Configuration
```
RP2040 Pin maps:
- Control Pins:
  - PIN_DCLK: 18 (Data Clock)
  - PIN_SDI:  19 (Serial Data Input)
  - PIN_GCLK: 22 (Global Clock)
  - PIN_LE:   26 (Latch Enable)

- Line Selection Pins (16 lines):
  - PIN_LINE0  - PIN_LINE15: 0-15
```

### LED Driver Configuration
- MBI5252 Configuration: 0xCF1B

## Building and Running

1. Clone the repository
2. Set up the Pico SDK environment
3. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Flash the resulting .uf2 file to your Raspberry Pi Pico

## Project Structure

- `main.c`: Main program entry point
- `gfx_fireflies.c/h`: Firefly simulation implementation
- `gfx_wave.c/h`: Wave effect implementation
- `mbi5252.c/h`: LED driver implementation
- `mbi.pio`: PIO program for LED control
- `gfx_driver.c/h`: Graphics driver interface

## Dependencies

- Raspberry Pi Pico SDK
- CMake (version 3.13 or higher)

## License

This project is open source and available under the MIT License.
