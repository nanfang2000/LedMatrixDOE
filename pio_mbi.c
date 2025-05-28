/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 #include "pio_mbi.h"
 #include "hardware/timer.h"

void pio_mbi_init(pio_mbi_inst_t *mbi, uint baud, uint pin_dclk, uint pin_sdi, uint pin_le) {
    mbi->offset = pio_add_program(mbi->pio, &mbi_program);
    pio_mbi_program_init(mbi->pio, mbi->sm, mbi->offset, baud, pin_dclk, pin_sdi, pin_le);
}
 // Just 8 bit functions provided here. The PIO program supports any frame size
 // 1...32, but the software to do the necessary FIFO shuffling is left as an
 // exercise for the reader :)
 //
 // Likewise we only provide MSB-first here. To do LSB-first, you need to
 // - Do shifts when reading from the FIFO, for general case n != 8, 16, 32
 // - Do a narrow read at a one halfword or 3 byte offset for n == 16, 8
 // in order to get the read data correctly justified. 
 
void __time_critical_func(pio_mbi_write16_blocking)(const pio_mbi_inst_t *mbi, const uint16_t *src, size_t len) {
    size_t tx_remain = len;
    // Do 8 bit accesses on FIFO, so that write data is byte-replicated. This
    // gets us the left-justification for free (for MSB-first shift-out)
    io_rw_16 *txfifo = (io_rw_16 *) &mbi->pio->txf[mbi->sm];
    while (tx_remain) {
        if (tx_remain && !pio_sm_is_tx_fifo_full(mbi->pio, mbi->sm)) {
            *txfifo = *src++;
            --tx_remain;
        }
    }
}

void pio_mbi_data_latch(const pio_mbi_inst_t *mbi, const uint16_t *src, size_t chips) {
    pio_sm_put_blocking(mbi->pio, mbi->sm, ((chips * 16 - 2) << 20) | (0 << 16)); //LE=1, nbits - LE - 1, LE - 1
    pio_mbi_write16_blocking(mbi, src, chips);
}

void pio_mbi_vsync(const pio_mbi_inst_t *mbi) {
    pio_sm_put_blocking(mbi->pio, mbi->sm, (13 << 20) | (1 << 16)); //LE=2
    pio_sm_put_blocking(mbi->pio, mbi->sm, (0x0000 << 16) | 0); //dummy data
}

void pio_mbi_pre_active(const pio_mbi_inst_t *mbi) {
    pio_sm_put_blocking(mbi->pio, mbi->sm, (1 << 20) | (13 << 16)); //PreActive, LE=14
    pio_sm_put_blocking(mbi->pio, mbi->sm, (0x0000 << 16) | 0); //dummy data
}

void pio_mbi_write_config1(const pio_mbi_inst_t *mbi, const uint16_t *src,  size_t chips) {
    pio_sm_put_blocking(mbi->pio, mbi->sm, ((chips * 16 - 4 - 1) << 20) | (3 << 16)); //Write Configure1, LE = 4, nbits - LE - 1, LE - 1
    pio_mbi_write16_blocking(mbi, src, chips); //Config data
}

void pio_mbi_soft_reset(const pio_mbi_inst_t *mbi) {
    pio_sm_put_blocking(mbi->pio, mbi->sm, (5 << 20) | (9 << 16)); //SoftReset, LE=10
    pio_sm_put_blocking(mbi->pio, mbi->sm, (0x0000 << 16) | 0); //dummy data
}

void pio_mbi_set_enabled(pio_mbi_inst_t *mbi, bool enabled) {
    pio_sm_set_enabled(mbi->pio, mbi->sm, enabled);
}


void pio_mbi_graphic_init(pio_mbi_inst_t *mbi, uint freq, uint pin_gclk, uint pin_lines) {
    mbi->offset = pio_add_program(mbi->pio, &mbi_graph_program);

    pio_mbi_graph_program_init(mbi->pio, mbi->sm, mbi->offset, freq, pin_gclk, pin_lines);
    pio_sm_put_blocking(mbi->pio, mbi->sm, (512 << 16) | 0);
    pio_sm_put_blocking(mbi->pio, mbi->sm, (0xFFFF<< 16) | 0);
}

void pio_mbi_graphic_restart(pio_mbi_inst_t *mbi) {
    // pio_sm_set_enabled(mbi->pio, mbi->sm, false);  // 停止状态机
    // pio_interrupt_clear(mbi->pio, mbi->sm);
    // irq_set_enabled(PIO0_IRQ_0, false);
    // pio_sm_restart(mbi->pio, mbi->sm);             // 复位寄存器和FIFO
    // pio_sm_clear_fifos(mbi->pio, mbi->sm);         // 手动清空FIFO缓冲区
    // glck_count = 1;
    // pio_sm_restart(mbi->pio, mbi->sm);
    // pio_sm_clkdiv_restart(mbi->pio, mbi->sm);
    // pio_sm_set_enabled(mbi->pio, mbi->sm, true);
    // pio_sm_exec(mbi->pio, mbi->sm, pio_encode_jmp(mbi->offset));
    restart_glck(mbi->pio, mbi->sm, mbi->offset, 16000000, 22, 0);

    pio_sm_put_blocking(mbi->pio, mbi->sm, (512 << 16) | 0);
    pio_sm_put_blocking(mbi->pio, mbi->sm, (0xFFF< 16) | 0);
}
