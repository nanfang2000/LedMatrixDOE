#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "mbi5252.h"
#include "gfx_driver.h"
#include "gfx_wave.h"
#include "gfx_fireflies.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#include "blink.pio.h"
#include "mbi.pio.h"
#include "pio_mbi.h"

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    pio->txf[sm] = (125000000 / (2 * freq)) - 3;
}

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    printf("Timeout!\n");
    add_alarm_in_ms(2000, alarm_callback, NULL, false);
    return 0;
}


// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

volatile uint8_t irq_flags = 0;
volatile uint32_t irq_count = 0;

void simple_irq_handler() {
    // Check the interrupt source and set the flag accordingly
    // This method can handle multiple simultaneous interrupts from the PIO
    // since it checks all the irq flags. The advantage to this is that the
    // ISR would execute only once when simultaneous interrupts happen instead
    // of being executed for each interrupt individually.
    // For other applications, make sure to check the correct pio (pio0/pio1)
    irq_flags = pio0_hw->irq;
    // Clear the flags since we've saved them to check later.
    printf("simple_irq_handler %d\n", irq_count++);
    hw_clear_bits(&pio0_hw->irq, irq_flags);

    // alternatively you could use pio_interrupt_get(pio0, #) to check a specific
    // irq flag.
}

/**
 * Lets the pico know that we want it to notify us of the PIO ISRs.
 * @note in simple_irq.pio we enable irq0. This tells the state machine
 *       to send the ISRs to the core, we still need to tell the core
 *       to send them to our program.
 */
void enable_pio_irqs() {
    // Set the function that will be called when the PIO IRQ comes in.
    irq_set_exclusive_handler(PIO0_IRQ_0, simple_irq_handler);
    // pio_set_irq0_source_enabled(pio0, pis_interrupt2, true);

    // Once that function is set, we can go ahead and allow the interrupts
    // to come in. You want to set the function before enabling the interrupt
    // just in case. The docs say if an IRQ comes in and there's no handler
    // then it will work like a breakpoint, which seems bad.
    irq_set_enabled(PIO0_IRQ_0, true);
}

void gfx_test(void)
{
    rgb_t black = {0, 0, 0};
    rgb_t red = {128, 0, 0};
    rgb_t green = {0, 128, 0};
    rgb_t blue = {0, 0, 128};

    int w = 1;
    int h = 1;
    int idx = 0;
    rgb_t frame_color_list[] = {red, green, blue};
    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(100);
        gfx_fill(0, 0, w, h, frame_color_list[idx % 3]);
        gfx_sync_frame();
        // gfx_clear();
        // gfx_fill(0, 0, w, h, black);
        w += 2;
        h++;
        if (w == 33)
        {
            idx++;
            w = 1;
        }
        if (h == 17)
        {
            h = 1;
        }
    }
}

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    // spi_init(SPI_PORT, 1000*1000);
    // gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    // gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    // gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    // gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // // Chip select is active-low, so we'll initialise it to a driven-high state
    // gpio_set_dir(PIN_CS, GPIO_OUT);
    // gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // PIO Blinking example
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d\n", offset);
    
    // enable_pio_irqs();

    #ifdef PICO_DEFAULT_LED_PIN
    blink_pin_forever(pio, 0, offset, PICO_DEFAULT_LED_PIN, 3);
    #else
    blink_pin_forever(pio, 0, offset, 6, 3);
    #endif
    
    // For more pio examples see https://github.com/raspberrypi/pico-examples/tree/master/pio

    // Timer example code - This example fires off the callback after 2000ms
    // add_alarm_in_ms(2000, alarm_callback, NULL, false);
    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

    printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

    // // Set up our UART
    // uart_init(UART_ID, BAUD_RATE);
    // // Set the TX and RX pins by using the function select on the GPIO
    // // Set datasheet for more information on function select
    // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // // Use some the various UART functions to send out data
    // // In a default system, printf will also output via the default UART
    
    // // Send out a string, with CR/LF conversions
    // uart_puts(UART_ID, " Hello, UART!\n");

    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    gfx_init();

    // gfx_test();
    // gfx_wave_effect();
    gfx_firefly_effect();
}

