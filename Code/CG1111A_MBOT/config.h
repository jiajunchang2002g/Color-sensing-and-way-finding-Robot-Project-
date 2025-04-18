/* Debug Options ---------------------------------------------------------------- */

#define DEBUG_SERIAL TRUE // Has to be on for all to be on for all debug cases to work
#define DEBUG_DECODER FALSE
#define DEBUG_KNN_COLOUR_ENUM FALSE // KNN Logic Debugging
#define DEBUG_COLOUR_ENUM TRUE
#define DEBUG_LOOP_LOGIC FALSE

/* Pinouts ---------------------------------------------------------------------- */

#define DECA A0
#define DECB A1
#define IR A2
#define LDR A3  

#define ULTRASONIC 12
// If you are using Port 1 of mCore, the ultrasonic sensor uses digital pin 12
// If you are using Port 2 of mCore, the ultrasonic sensor uses digital pin 10

MeDCMotor leftMotor(M1);
MeDCMotor rightMotor(M2);

MeRGBLed led(0,30); // Based on hardware connections on mCore; cannot change
MeUltrasonicSensor ultraSensor(PORT_2); // Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.
MeLineFollower lineFinder(PORT_1);
MeBuzzer buzzer; // create the buzzer object

/* Decoder ---------------------------------------------------------------------- */

int COLOUR_DEC_PIN[] = {0, 1, 2}; // R, G, B

/* Colour ----------------------------------------------------------------------- */

// Calibration Metrics
float whiteArray[] = {989.00, 891.00, 959.00};
float blackArray[] = {971.00, 630.00, 801.00};
float greyDiff[] = {18.00, 261.00, 158.00};

// Define time delay before the next RGB colour turns ON to allow LDR to stabilize
#define RGB_WAIT 500 //in milliseconds 
// Define time delay before taking another LDR reading
#define LDR_WAIT 10 //in milliseconds 

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

/* Ultrasonic ------------------------------------------------------------------- */

#define TIMEOUT 2000 // Max microseconds to wait; choose according to max distance of wall
#define SPEED_OF_SOUND 340 // Update according to your own experiment



