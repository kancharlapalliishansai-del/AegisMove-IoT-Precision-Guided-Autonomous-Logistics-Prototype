#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// ==========================================
// PIN CONFIGURATION
// ==========================================

// 5-Channel IR Line Sensor Array (Digital Inputs)
const int IR_PINS[5] = {34, 35, 32, 33, 25}; // Leftmost to Rightmost

// HC-SR04 Ultrasonic Sensor
#define PIN_TRIG 26
#define PIN_ECHO 27

// BTS7960 Heavy Duty Motor Driver Pins
// Left Motor Group
#define MOTOR_L_RPWM 12  // Forward PWM
#define MOTOR_L_LPWM 14  // Reverse PWM
#define MOTOR_L_LEN  21  // Left Enable (Tie L_EN and R_EN together to this pin)
#define MOTOR_L_REN  21

// Right Motor Group
#define MOTOR_R_RPWM 13  // Forward PWM
#define MOTOR_R_LPWM 15  // Reverse PWM
#define MOTOR_R_LEN  22  // Right Enable (Tie L_EN and R_EN together to this pin)
#define MOTOR_R_REN  22

// MAX7219 Dot Matrix Display (SPI)
#define PIN_CS    5   
// Note: Hardware SPI on ESP32 uses GPIO 23 (MOSI/DIN) and GPIO 18 (CLK) by default.

// ==========================================
// SYSTEM CONSTANTS & VARIABLES
// ==========================================

// PID Tuning Parameters
const float Kp = 45.0;   // Proportional Gain (Handles immediate error)
const float Ki = 0.05;   // Integral Gain (Corrects accumulation over time)
const float Kd = 25.0;   // Derivative Gain (Prevents overshooting/wobble)

const int BASE_SPEED = 160;  // Default cruising speed (0 - 255)
const int MAX_SPEED = 230;   // Safe maximum upper limit
const int MIN_SPEED = 0;     // Safe lowest limit

float error = 0, lastError = 0, integral = 0, derivative = 0;

// Safety Configuration
const int SAFETY_STOP_DISTANCE_CM = 20; 
volatile bool isObstacleDetected = false;

// Dot Matrix Layout Settings
Max72xxPanel matrix = Max72xxPanel(PIN_CS, 4, 1); // 4 displays side-by-side
String displayMessage = "SHAAN - SNITP RUNNING ";
int spacer =

