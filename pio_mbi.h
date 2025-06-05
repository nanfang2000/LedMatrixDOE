/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _PIO_MBI_H
#define _PIO_MBI_H

#include "hardware/pio.h"
#include "mbi.pio.h"

/**
 * Defines the structure for a pio_mbi_inst instance.
 */
typedef struct pio_mbi_inst {
    PIO pio;      ///< Pointer to the PIO instance
    uint sm;      ///< State machine number
    uint offset;  ///< Offset address of the PIO program
} pio_mbi_inst_t;

/**
 * Initializes the MBI protocol.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 * @param baud Baud rate
 * @param pin_dclk Data clock pin
 * @param pin_sdi Serial data input pin
 * @param pin_le Latch enable pin
 */
void pio_mbi_init(pio_mbi_inst_t *mbi, uint baud, uint pin_dclk, uint pin_sdi, uint pin_le);

/**
 * Latches the data to the MBI chips.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 * @param src Pointer to the source data
 * @param chips Number of chips
 */
void pio_mbi_data_latch(const pio_mbi_inst_t *mbi, const uint16_t *src, size_t chips);

/**
 * Sends a vsync signal.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 */
void pio_mbi_vsync(const pio_mbi_inst_t *mbi);

/**
 * Pre-active signal for MBI protocol.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 */
void pio_mbi_pre_active(const pio_mbi_inst_t *mbi);

/**
 * Writes configuration data 1 to the MBI chips.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 * @param src Pointer to the configuration data
 * @param chips Number of chips
 */
void pio_mbi_write_config1(const pio_mbi_inst_t *mbi, const uint16_t *src,  size_t chips);

/**
 * Performs a software reset on the MBI chips.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 */
void pio_mbi_soft_reset(const pio_mbi_inst_t *mbi);

/**
 * Sets the enable state of the MBI protocol.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 * @param enable Enable state, true to enable, false to disable
 */
void pio_mbi_set_enabled(pio_mbi_inst_t *mbi, bool enable);

/**
 * Initializes the graphic mode of the MBI protocol.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 * @param freq Graphics mode frequency
 * @param pin_gclk Graphics clock pin
 * @param pin_lines Number of lines
 */
void pio_mbi_graphic_init(pio_mbi_inst_t *mbi, uint freq, uint pin_gclk, uint pin_lines);

/**
 * Restarts the graphic mode of the MBI protocol.
 * 
 * @param mbi Pointer to the pio_mbi_inst instance
 */
void pio_mbi_graphic_restart(pio_mbi_inst_t *mbi);

#endif