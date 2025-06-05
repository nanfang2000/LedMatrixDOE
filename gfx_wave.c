#include "gfx_driver.h"
#include <math.h>
#include "hardware/timer.h"

// Wave effect parameters
#define WAVE_AMPLITUDE 4.0f
#define WAVE_FREQUENCY 0.1f
#define WAVE_SPEED 0.05f
#define NUM_WAVES 3

// Wave colors
static const rgb_t wave_colors[NUM_WAVES] = {
    {255, 0, 0},    // Red
    {0, 255, 0},    // Green
    {0, 0, 255}     // Blue
};

// Wave phase offsets
static float wave_phases[NUM_WAVES] = {0.0f, 2.094f, 4.189f}; // 0, 2π/3, 4π/3

/**
 * @brief Calculate wave height at a given position and time
 * 
 * @param x Horizontal position
 * @param phase Current phase of the wave
 * @return float Wave height
 */
static float calculate_wave_height(int x, float phase) {
    return WAVE_AMPLITUDE * sinf(WAVE_FREQUENCY * x + phase);
}

/**
 * @brief Draw a single frame of the wave effect
 * 
 * @param time Current time value
 */
static void draw_wave_frame(float time) {
    // Clear the display
    gfx_clear();
    
    // Draw each wave
    for (int wave = 0; wave < NUM_WAVES; wave++) {
        float phase = wave_phases[wave] + time * WAVE_SPEED;
        
        // Draw the wave line
        for (int x = 0; x < 32; x++) {
            float height = calculate_wave_height(x, phase);
            int y = (int)(8 + height); // Center the wave vertically
            
            // Ensure y is within bounds
            if (y >= 0 && y < 16) {
                gfx_draw_pixel(x, y, wave_colors[wave]);
            }
        }
    }
}

void gfx_wave_effect(void) {
    float time = 0.0f;
    
    while (1) {
        // Draw the current frame
        draw_wave_frame(time);
        
        // Update display
        gfx_sync_frame();
        
        // Update time
        time += 0.1f;
        if (time > 2 * M_PI) {
            time -= 2 * M_PI;
        }
        
        // Simple delay
        busy_wait_us(100000);  // 100ms = 100000us
    }
} 