#pragma once

/* Physics definitions */
#define PHYSICS_TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 6.0f
#define POSITION_ITERATIONS 2.0f


/* Lander definitions */
#define LANDER_THRUST 300000.0f
#define LANDER_START_X 300
#define LANDER_START_Y 400
#define LANDER_START_ANGLE 0.0f
#define LANDER_HALF_HEIGHT 16.0f
#define LANDER_HALF_WIDTH 16.0f
#define LANDER_DENSITY 1.0f
#define LANDER_RESTITUTION 0.1f
#define LANDER_FRICTION 0.3f
#define LANDER_ROTATION_SPEED 1.0f
#define LANDER_CRASH_THRESHOLD 100.0f
#define LANDER_BREAK_THRESHOLD 100.0f


/* Particle system definitions */
#define PARTICLE_MAX_AMOUNT 100
#define PARTICLES_PER_SECOND 10
#define PARTICLE_LIFE 0.8f
#define PARTICLE_ANGLE_VARIATION (30 * (M_PI / 180.0f))
#define PARTICLE_MIN_VELOCITY 10
#define PARTICLE_MAX_VELOCITY 30
