/**
 * @file gfx_fireflies.h
 * @brief Header file for the firefly effect implementation
 */

#ifndef GFX_FIREFLIES_H
#define GFX_FIREFLIES_H

/**
 * @brief Runs the firefly effect animation
 * 
 * This function implements a firefly swarm simulation using a combination of
 * particle movement and pheromone-based behavior. The fireflies move around
 * the display while leaving trails of light that influence their movement patterns.
 * 
 * The effect runs indefinitely until interrupted.
 */
void gfx_firefly_effect(void);

#endif /* GFX_FIREFLIES_H */