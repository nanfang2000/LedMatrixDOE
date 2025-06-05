#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/divider.h"
#include "pio_mbi.h"

#define PIN_DCLK 18
#define PIN_SDI  19
#define PIN_GCLK 22
#define PIN_LE   26

#define PIN_LINE0 0
#define PIN_LINE1 1
#define PIN_LINE2 2
#define PIN_LINE3 3
#define PIN_LINE4 4
#define PIN_LINE5 5
#define PIN_LINE6 6
#define PIN_LINE7 7
#define PIN_LINE8 8
#define PIN_LINE9 9
#define PIN_LINE10 10
#define PIN_LINE11 11
#define PIN_LINE12 12
#define PIN_LINE13 13
#define PIN_LINE14 14
#define PIN_LINE15 15

typedef struct {
    pio_mbi_inst_t pio_mbi;
    pio_mbi_inst_t pio_mbi_graphic;
    uint32_t chips;
    uint32_t scan_lines;
    uint32_t channels;
} mbi5252_t;

static mbi5252_t g_context;
static uint slice_num = 0;

int32_t pwm_set_freq_duty(uint32_t slice_num, uint32_t chan, uint32_t freq, 
                          int duty_cycle)
{

    uint8_t clk_divider = 0;
    uint32_t wrap = 0;
    uint32_t clock_div = 0;
    uint32_t clock = clock_get_hz(clk_sys);

    if(freq < 8 || freq > clock) {
       /* This is the frequency range of generating a PWM 
       in RP2040 at 125MHz */
        return -1;
    }

    for(clk_divider = 1; clk_divider < UINT8_MAX; clk_divider++)
    {
        /* Find clock_division to fit current frequency */
        clock_div = div_u32u32( clock, clk_divider );
        wrap = div_u32u32(clock_div, freq);
        if (div_u32u32 (clock_div, UINT16_MAX) <= freq && wrap <= UINT16_MAX)
        {
            break;
        }
    }
    if(clk_divider < UINT8_MAX)
    {
        /* Only considering whole number division */
        pwm_set_clkdiv_int_frac(slice_num, clk_divider, 0);
        pwm_set_enabled(slice_num, true);
        pwm_set_wrap(slice_num, (uint16_t) wrap);
        pwm_set_chan_level(slice_num, chan, 
                          (uint16_t) div_u32u32((((uint16_t)(duty_cycle == 100? 
                          (wrap + 1) : wrap)) * duty_cycle), 100));
    }
    else
        return -2;

    return 1;
}

int32_t mbi5252_init(uint32_t chips, uint32_t scan_lines, uint32_t channels) {

    memset(&g_context, 0, sizeof(g_context));
    g_context.chips = chips;
    g_context.scan_lines = scan_lines;
    g_context.channels = channels;
    g_context.pio_mbi.pio = pio0;
    g_context.pio_mbi.sm = 1;

    g_context.pio_mbi_graphic.pio = pio0;
    g_context.pio_mbi_graphic.sm = 2;

    pio_mbi_init(&g_context.pio_mbi, 16000000, PIN_DCLK, PIN_SDI, PIN_LE);
    pio_mbi_pre_active(&g_context.pio_mbi);
    uint16_t configures[6] = {0xCF1B, 0xCF1B, 0xCF1B, 0xCF1B, 0xCF1B, 0xCF1B}; //default: 0x32B
    pio_mbi_write_config1(&g_context.pio_mbi, configures, 6); //16 lines
    // pio_mbi_soft_reset(&g_context.pio_mbi);

    pio_mbi_graphic_init(&g_context.pio_mbi_graphic, 16000000, PIN_GCLK, PIN_LINE0);

}

int32_t mbi5252_send_frame(uint16_t framebuf[16][16][48], uint32_t len) {
    int32_t chips = g_context.chips;
    int32_t scan_lines = g_context.scan_lines;
    int32_t channels = g_context.channels;
    for (int line = 0; line < scan_lines; line ++){
        for (int ch = 0; ch < channels; ch ++){
            pio_mbi_data_latch(&g_context.pio_mbi, framebuf[line][ch], chips);
        }
    }
    busy_wait_us(50);
    pio_mbi_set_enabled(&g_context.pio_mbi_graphic, false);
    pio_mbi_vsync(&g_context.pio_mbi);
    busy_wait_us(5);
    pio_mbi_graphic_restart(&g_context.pio_mbi_graphic);
}

