#pragma once

/* Physics definitions */
#define PHYSICS_TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 6.0f
#define POSITION_ITERATIONS 2.0f
#define GRAVITY_CONSTANT -0.25f

/* Level generator definitions */
#define MIN_HEIGHT 50
#define SLICE_MIN_WIDTH 10
#define SLICE_MAX_WIDTH 30
#define SLICE_MIN_HEIGHT 5
#define SLICE_MAX_HEIGHT 50
#define GOAL_MIN_WIDTH 45
#define GOAL_MAX_WIDTH 76 * 2

/* User data */
#define GROUND -1
#define LANDER_CORE 1
#define LANDER_LEGS 2

/* Lander definitions */
#define LANDER_THRUST 300000.0f
#define LANDER_START_X 300
#define LANDER_START_Y 800
#define LANDER_START_ANGLE 0.0f
#define LANDER_HALF_HEIGHT 16.0f
#define LANDER_HALF_WIDTH 16.0f
#define LANDER_DENSITY 1.0f
#define LANDER_RESTITUTION 0
#define LANDER_FRICTION 0.3f
#define LANDER_ROTATION_SPEED 1.0f
#define LANDER_CRASH_THRESHOLD 50.0f
#define LANDER_BREAK_THRESHOLD 60.0f
#define LANDER_START_FUEL 2000.0f
#define LANDER_FUEL_COST 0.1f


/* Particle system definitions */
#define PARTICLE_MAX_AMOUNT 100
#define PARTICLES_PER_SECOND 10
#define PARTICLE_LIFE 0.8f
#define PARTICLE_ANGLE_VARIATION (30 * (M_PI / 180.0f))
#define PARTICLE_MIN_VELOCITY 10
#define PARTICLE_MAX_VELOCITY 30

/* Win conditions */
#define WIN_TIME 2.0f

/* Camera definitions */
#define ZOOM_AMOUNT 1.2f