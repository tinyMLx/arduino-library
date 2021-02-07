#ifndef MAGIC_WAND_IMU_PROVIDER_H
#define MAGIC_WAND_IMU_PROVIDER_H

#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>

constexpr int stroke_transmit_stride = 2;
constexpr int stroke_transmit_max_length = 160;
constexpr int stroke_max_length = stroke_transmit_max_length * stroke_transmit_stride;
constexpr int stroke_points_byte_count = 2 * sizeof(int8_t) * stroke_transmit_max_length;
constexpr int stroke_struct_byte_count = (2 * sizeof(int32_t)) + stroke_points_byte_count;
constexpr int moving_sample_count = 50;

static float current_velocity[3] = {0.0f, 0.0f, 0.0f};
static float current_position[3] = {0.0f, 0.0f, 0.0f};
static float current_gravity[3] = {0.0f, 0.0f, 0.0f};
static float current_gyroscope_drift[3] = {0.0f, 0.0f, 0.0f};

static int32_t stroke_length = 0;
static uint8_t stroke_struct_buffer[stroke_struct_byte_count] = {};
static int32_t* stroke_state = reinterpret_cast<int32_t*>(stroke_struct_buffer);
static int32_t* stroke_transmit_length = reinterpret_cast<int32_t*>(stroke_struct_buffer + sizeof(int32_t));
static int8_t* stroke_points = reinterpret_cast<int8_t*>(stroke_struct_buffer + (sizeof(int32_t) * 2));


void SetupIMU();

void ReadAccelerometerAndGyroscope(int* new_accelerometer_samples, int* new_gyroscope_samples);

int ReadGyroscope();

float VectorMagnitude(const float* vec);

void NormalizeVector(const float* in_vec, float* out_vec);

float DotProduct(const float* a, const float* b);

void EstimateGravityDirection(float* gravity);

void UpdateVelocity(int new_samples, float* gravity);

void EstimateGyroscopeDrift(float* drift);

void UpdateOrientation(int new_samples, float* gravity, float* drift);

bool IsMoving(int samples_before);

void UpdateStroke(int new_samples, bool* done_just_triggered);

#endif   // MAGIC_WAND_IMU_PROVIDER_H
