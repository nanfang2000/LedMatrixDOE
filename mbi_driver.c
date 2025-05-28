#include <stdio.h>
#include <string.h>
#include "mbi_driver.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/divider.h"

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

#define SPI_PORT spi0
#define PIN_SCK  18
#define PIN_MOSI 19

#define SDI_ON() gpio_put(PIN_SDI,  1);
#define SDI_OFF() gpio_put(PIN_SDI,  0);
#define DCLK_ONOFF() gpio_put(PIN_DCLK,  1);sleep_us(5);gpio_put(PIN_DCLK,  0);sleep_us(5);
#define LE_ON() gpio_put(PIN_LE,  1);
#define LE_OFF() gpio_put(PIN_LE,  0);
#define GCLK_ONOFF() gpio_put(PIN_GCLK,  1);sleep_us(10);gpio_put(PIN_GCLK,  0);sleep_us(10);

uint slice_num = 0;


#include "pico/divider.h"

/**
 *  @brief Set frequency and duty cycle for any PWM slice and channel
 *  @param[in] slice_num  The slice number the GPIO is associated to
 *  @param[in] chan       The channel number the GPIO is associated to
 *  @param[in] freq       The required frequency to be set
 *  @param[in] duty_cycle The required duty cycle in percentage 1->100
 *
 *  @return 1: Success; <0: Error
 */
int32_t pwm_set_freq_duty(uint32_t slice_num, uint32_t chan, uint32_t freq,
                          int duty_cycle);

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

int32_t mbi_init(void) {
    gpio_set_function(PIN_DCLK, GPIO_FUNC_SIO);
    gpio_set_function(PIN_SDI,  GPIO_FUNC_SIO);
    // gpio_set_function(PIN_GCLK, GPIO_FUNC_SIO);
    gpio_set_function(PIN_LE,   GPIO_FUNC_SIO);
    gpio_set_dir(PIN_DCLK, GPIO_OUT);
    gpio_set_dir(PIN_SDI,  GPIO_OUT);
    // gpio_set_dir(PIN_GCLK, GPIO_OUT);
    gpio_set_dir(PIN_LE,   GPIO_OUT);
    gpio_put(PIN_DCLK, 0);
    gpio_put(PIN_SDI,  0);
    // gpio_put(PIN_GCLK, 0);
    gpio_put(PIN_LE,   0);

    gpio_set_function(PIN_LINE0,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE1,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE2,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE3,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE4,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE5,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE6,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE7,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE8,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE9,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE10,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE11,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE12,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE13,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE14,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_LINE15,  GPIO_FUNC_SIO);
    gpio_set_dir(PIN_LINE0, GPIO_OUT);
    gpio_set_dir(PIN_LINE1, GPIO_OUT);
    gpio_set_dir(PIN_LINE2, GPIO_OUT);
    gpio_set_dir(PIN_LINE3, GPIO_OUT);
    gpio_set_dir(PIN_LINE4, GPIO_OUT);
    gpio_set_dir(PIN_LINE5, GPIO_OUT);
    gpio_set_dir(PIN_LINE6, GPIO_OUT);
    gpio_set_dir(PIN_LINE7, GPIO_OUT);
    gpio_set_dir(PIN_LINE8, GPIO_OUT);
    gpio_set_dir(PIN_LINE9, GPIO_OUT);
    gpio_set_dir(PIN_LINE10, GPIO_OUT);
    gpio_set_dir(PIN_LINE11, GPIO_OUT);
    gpio_set_dir(PIN_LINE12, GPIO_OUT);
    gpio_set_dir(PIN_LINE13, GPIO_OUT);
    gpio_set_dir(PIN_LINE14, GPIO_OUT);
    gpio_set_dir(PIN_LINE15, GPIO_OUT);


    gpio_put(PIN_LINE0, 1);
    gpio_put(PIN_LINE1, 1);
    gpio_put(PIN_LINE2, 1);
    gpio_put(PIN_LINE3, 1);
    gpio_put(PIN_LINE4, 1);
    gpio_put(PIN_LINE5, 1);
    gpio_put(PIN_LINE6, 1);
    gpio_put(PIN_LINE7, 1);
    gpio_put(PIN_LINE8, 1);
    gpio_put(PIN_LINE9, 1);
    gpio_put(PIN_LINE10, 1);
    gpio_put(PIN_LINE11, 1);
    gpio_put(PIN_LINE12, 1);
    gpio_put(PIN_LINE13, 1);
    gpio_put(PIN_LINE14, 1);
    gpio_put(PIN_LINE15, 0);

    gpio_set_function(PIN_GCLK, GPIO_FUNC_PWM); // 设置GPIO为PWM功能，PIN_BASE是PWM引脚的基础编号，例如0, 1, 2等。

    slice_num = pwm_gpio_to_slice_num(PIN_GCLK);

    // // Set period of 4 cycles (0 to 3 inclusive)
    // pwm_set_wrap(slice_num, 255);
    // // Set channel A output high for one cycle before dropping
    // pwm_set_chan_level(slice_num, PWM_CHAN_A, 128);
    // // Set initial B output high for three cycles before dropping
    // // pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
    // // Set the PWM running
    // pwm_set_enabled(slice_num, true);

    pwm_set_freq_duty(slice_num, PWM_CHAN_A, 16000000, 50);

    // spi_init(SPI_PORT, 10*1000*1000);
    // gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    // gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
}

int32_t mbi_data_latch(uint16_t *buf, uint32_t len) {
    uint32_t i, w;
    uint16_t i_data = *buf;
    for ( w = 0; w < len - 1; w++) {
        for (i = 0; i < 16; i++) {
            if (i_data & 0x8000) {
                SDI_ON(); // 输出1bit 1
            } else {
                SDI_OFF(); // 输出1bit 0
            }
            DCLK_ONOFF();
            i_data = i_data << 1;
        }
        buf++;
        i_data = *buf;
    }
    for (i = 0; i < 15; i++) {
        if (i_data & 0x8000) {
            SDI_ON(); // 输出1bit 1
        } else {
            SDI_OFF(); // 输出1bit 0
        }
        DCLK_ONOFF();
        i_data = i_data << 1;
    }
    LE_ON();
    if (i_data & 0x8000) {
        SDI_ON(); // 输出1bit 1
    } else {
        SDI_OFF(); // 输出1bit 0
    }
    DCLK_ONOFF();
    LE_OFF();
}

int32_t mbi_vsync(void) {
    sleep_us(150);
    pwm_set_enabled(slice_num, false);
    DCLK_ONOFF();
    LE_ON();
    DCLK_ONOFF();
    DCLK_ONOFF();
    LE_OFF();
    DCLK_ONOFF();
    sleep_us(20);
    pwm_set_enabled(slice_num, true);
}

int32_t mbi_gclk(int32_t num) {
    for (int i = 0; i < num; i++) {
        GCLK_ONOFF();
    }
}

int32_t mbi_pre_active(void) {

}

int32_t mbi_write_config(void) {

}

int32_t mbi_read_config(void) {

}

int32_t mbi_soft_reset(void) {

}

int32_t mbi_deinit(void) {

}
