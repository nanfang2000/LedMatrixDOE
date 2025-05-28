/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _PIO_MBI_H
#define _PIO_MBI_H

#include "hardware/pio.h"
#include "mbi.pio.h"

typedef struct pio_mbi_inst {
    PIO pio;
    uint sm;
    uint offset;
} pio_mbi_inst_t;

void pio_mbi_init(pio_mbi_inst_t *mbi, uint baud, uint pin_dclk, uint pin_sdi, uint pin_le);

void pio_mbi_data_latch(const pio_mbi_inst_t *mbi, const uint16_t *src, size_t chips);

void pio_mbi_vsync(const pio_mbi_inst_t *mbi);

void pio_mbi_pre_active(const pio_mbi_inst_t *mbi);

void pio_mbi_write_config1(const pio_mbi_inst_t *mbi, const uint16_t *src,  size_t chips);

void pio_mbi_soft_reset(const pio_mbi_inst_t *mbi);

void pio_mbi_set_enabled(pio_mbi_inst_t *mbi, bool enable);

void pio_mbi_graphic_init(pio_mbi_inst_t *mbi, uint freq, uint pin_gclk, uint pin_lines);

void pio_mbi_graphic_restart(pio_mbi_inst_t *mbi);



#endif