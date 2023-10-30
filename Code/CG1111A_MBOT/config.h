/* Debug Options ---------------------------------------------------------------- */

#define DEBUG_SERIAL TRUE // Has to be on for all to be on for all debug cases to work
#define DEBUG_DECODER TRUE

/* Pinouts ---------------------------------------------------------------------- */

#define DECA A0
#define DECB A1
#define IR A2
#define LDR A3   //LDR sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed

#define ULTRASONIC 12
// If you are using Port 1 of mCore, the ultrasonic sensor uses digital pin 12
// If you are using Port 2 of mCore, the ultrasonic sensor uses digital pin 10

MeDCMotor leftMotor(M1); // assigning leftMotor to port M1
MeDCMotor rightMotor(M2); // assigning RightMotor to port M2

MeLineFollower lineFinder(PORT_2);

/* Decoder ---------------------------------------------------------------------- */

int COLOUR_DEC_PIN[] = {0, 1, 2}; // R, G, B

/* Colour ----------------------------------------------------------------------- */

// Calibration Metrics
float whiteArray[] = {956, 804, 905}; // {0,0,0};
float blackArray[] = {943, 758, 756}; // {0,0,0};
float greyDiff[] = {13,86,149}; // {0,0,0};

// Define time delay before the next RGB colour turns ON to allow LDR to stabilize
#define RGBWait 200 //in milliseconds 
// Define time delay before taking another LDR reading
#define LDRWait 10 //in milliseconds 

/* Colour Matching --------------------------------------------------------------- */
#define NO_ENUMS 6
#define NO_COLOURS 3 // no. dimensions (eg. R, G, B)

// Enums
#define RED_ENUM 0
#define GREEN_ENUM 1
#define ORANGE_ENUM 2
#define PURPLE_ENUM 3
#define LIGHT_BLUE_ENUM 4
#define WHITE_ENUM 5

#define NULL_ENUM -1

int coloursEnum[NO_ENUMS] = {RED_ENUM, GREEN_ENUM, ORANGE_ENUM, PURPLE_ENUM, LIGHT_BLUE_ENUM, WHITE_ENUM}; 

int colours[NO_ENUMS][NO_COLOURS] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255}
};

int coloursUpperRange[NO_ENUMS][NO_COLOURS] = {
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10}
};

int coloursLowerRange[NO_ENUMS][NO_COLOURS] = {
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10}
};

/* Ultrasonic ------------------------------------------------------------------- */

#define TIMEOUT 2000 // Max microseconds to wait; choose according to max distance of wall
#define SPEED_OF_SOUND 340 // Update according to your own experiment



