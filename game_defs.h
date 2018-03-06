#pragma once

/* Physics definitions */
#define PHYSICS_TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 6.0f
#define POSITION_ITERATIONS 2.0f


/* Lander definitions */
#define LANDER_THRUST 100000.0f
#define LANDER_START_X 100
#define LANDER_START_Y 400
#define LANDER_START_ANGLE 0.0f
#define LANDER_HEIGHT 19.0f
#define LANDER_WIDTH 24.0f
#define LANDER_DENSITY 1.0f
#define LANDER_FRICTION 0.3f
#define LANDER_ROTATION_SPEED 1.0f
#define LANDER_CRASH_THRESHOLD 5.0f


/* Particle system definitions */
#define PARTICLE_MAX_AMOUNT 200
#define PARTICLES_PER_SECOND 30
#define PARTICLE_LIFE 0.8f
#define PARTICLE_LIFE_VARIATION 0.5f
#define PARTICLE_ANGLE_VARIATION 30 * (3.1415 / 180.0f)
#define PARTICLE_MIN_VELOCITY 10
#define PARTICLE_MAX_VELOCITY 30
