#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//char for logo display
static const unsigned char PROGMEM image_data_logo[] = {
    0x00, 0x07, 0x80, 0x00, 0x00, 
    0x00, 0x07, 0xb0, 0x00, 0x00, 
    0x00, 0x07, 0x36, 0x00, 0x00, 
    0x00, 0x07, 0x06, 0x60, 0x00, 
    0x00, 0x07, 0x00, 0x6c, 0x00, 
    0x00, 0x07, 0x00, 0x0e, 0x00, 
    0x00, 0x07, 0x00, 0x06, 0x00, 
    0x00, 0x07, 0x30, 0x0e, 0x00, 
    0x00, 0x07, 0x38, 0x1c, 0x00, 
    0x00, 0x07, 0x3c, 0x38, 0x00, 
    0x00, 0x07, 0x2e, 0x70, 0x00, 
    0x00, 0x07, 0x27, 0xe0, 0x00, 
    0x00, 0x07, 0x27, 0xe0, 0x00, 
    0x00, 0x07, 0x23, 0xc0, 0x00, 
    0x00, 0x07, 0x23, 0xc0, 0x00, 
    0x00, 0x07, 0x27, 0xe0, 0x00, 
    0x00, 0x07, 0x2e, 0x70, 0x00, 
    0x00, 0x07, 0x3c, 0x38, 0x00, 
    0x00, 0x07, 0x38, 0x1c, 0x00, 
    0x00, 0x07, 0x30, 0x0e, 0x00, 
    0x00, 0x07, 0x00, 0x06, 0x00, 
    0x00, 0x07, 0x00, 0x0e, 0x00, 
    0x00, 0x07, 0x00, 0x6c, 0x00, 
    0x00, 0x07, 0x06, 0x60, 0x00, 
    0x00, 0x07, 0x36, 0x00, 0x00, 
    0x00, 0x07, 0xb0, 0x00, 0x00, 
    0x00, 0x07, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0xf0, 0x20, 0xce, 0x8b, 0x17, 
    0x90, 0x71, 0x28, 0x8b, 0x14, 
    0x90, 0x51, 0x08, 0x8a, 0x94, 
    0xf8, 0xd8, 0x8e, 0x8a, 0x97, 
    0x84, 0x88, 0x48, 0x8a, 0x54, 
    0x85, 0xfc, 0x28, 0x8a, 0x54, 
    0x85, 0x04, 0x28, 0x8a, 0x34, 
    0x85, 0x05, 0x28, 0x8a, 0x34, 
    0xf9, 0x04, 0xce, 0xea, 0x17, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x0f, 0x1c, 0xc8, 0xe6, 0x20, 
    0x08, 0x91, 0x29, 0x16, 0x20, 
    0x08, 0x51, 0x0a, 0x05, 0x20, 
    0x08, 0x5c, 0x8a, 0x05, 0x20, 
    0x08, 0x50, 0x4a, 0x04, 0xa0, 
    0x08, 0x50, 0x2a, 0x74, 0xa0, 
    0x08, 0x50, 0x2a, 0x14, 0xa0, 
    0x08, 0x91, 0x29, 0x14, 0x60, 
    0x0f, 0x1c, 0xc8, 0xe4, 0x60
};

static const unsigned char PROGMEM image_data_Logosmall[] = {
    0x00, 0x1c, 0x00, 0x00, 0x00, 
    0x00, 0x1d, 0x80, 0x00, 0x00, 
    0x00, 0x19, 0xe0, 0x00, 0x00, 
    0x00, 0x18, 0x66, 0x00, 0x00, 
    0x00, 0x18, 0x07, 0x80, 0x00, 
    0x00, 0x18, 0x00, 0xc0, 0x00, 
    0x00, 0x1b, 0x01, 0xc0, 0x00, 
    0x00, 0x1b, 0x81, 0x80, 0x00, 
    0x00, 0x1b, 0xc3, 0x00, 0x00, 
    0x00, 0x1b, 0xe7, 0x00, 0x00, 
    0x00, 0x1b, 0x7e, 0x00, 0x00, 
    0x00, 0x1b, 0x3c, 0x00, 0x00, 
    0x00, 0x1b, 0x3c, 0x00, 0x00, 
    0x00, 0x1b, 0x7e, 0x00, 0x00, 
    0x00, 0x1b, 0xe7, 0x00, 0x00, 
    0x00, 0x1b, 0xc3, 0x00, 0x00, 
    0x00, 0x1b, 0x81, 0x80, 0x00, 
    0x00, 0x1b, 0x01, 0xc0, 0x00, 
    0x00, 0x18, 0x00, 0xc0, 0x00, 
    0x00, 0x18, 0x07, 0x80, 0x00, 
    0x00, 0x18, 0x66, 0x00, 0x00, 
    0x00, 0x19, 0xe0, 0x00, 0x00, 
    0x00, 0x1d, 0x80, 0x00, 0x00, 
    0x00, 0x1c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0xf0, 0x41, 0x9d, 0x14, 0x5c, 
    0x90, 0xe2, 0x51, 0x14, 0x50, 
    0x90, 0xa2, 0x11, 0x16, 0x50, 
    0xf1, 0xb1, 0x1d, 0x16, 0x5c, 
    0x99, 0x10, 0x91, 0x15, 0x50, 
    0x8b, 0xf8, 0x51, 0x15, 0x50, 
    0x8a, 0x0a, 0x51, 0x14, 0xd0, 
    0xfa, 0x09, 0x9d, 0xd4, 0xdc, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x07, 0x1c, 0xc8, 0xc8, 0x80, 
    0x04, 0x91, 0x29, 0x28, 0x80, 
    0x04, 0x51, 0x0a, 0x0c, 0x80, 
    0x04, 0x5c, 0x8a, 0x0c, 0x80, 
    0x04, 0x50, 0x4a, 0xea, 0x80, 
    0x04, 0x50, 0x2a, 0x2a, 0x80, 
    0x04, 0x91, 0x29, 0x29, 0x80, 
    0x07, 0x1c, 0xc8, 0xc9, 0x80
};
  

//ENCODER
 #define outputA 3   //first data input pin for the encoder
 #define outputB 4   //second data input pin for the encoder
 double counter = 0;    //tracks how many clicks the encoder has had
 int aState;         //Value to store the current state of the Encoder
 int aLastState;     //Value to store the last state of the Encoder
 const byte encoderButtonInterruptPin = 2;        //inerupt pin attached to the encoders button  
 const byte encodeRotationrInterruptPin = 3;      //interupt pin attached to the encoders rotation

//STEPPER
#define horizontalDirPin 5        //direction pin for horizontal motor       
#define horizontalStepPin 6       //drive pin for horizontal motor  
#define rotationlDirPin 7         //direction pin for rotation motor
#define rotationStepPin 8         //drive pin for rotation motor
#define disablePin 9              //pin to dissable both stepper drivers

//MENU LOGIC
  int menu = 0;                  //menus are stored as numbers
  #define homeMenuID 0           //numerical ID for all menu options
  #define timeControlID 1
  #define speedControlID 2
  #define motionControlID 3
  #define globalValuesID 4
  #define menuTuneID 100
  int menuOptionCount;           //number of options availible on a given menu
  
  
  
  

//EEPROM CONFIGURE


  //Global EEPROM
  unsigned int length_Inches = 30;                  //length of the slider rail in inches
  #define length_Inches_eeAddress 0          //Location of information in eeprom

  unsigned int Steps_Per_inch = 2032;
  #define Steps_Per_inch_eeAddress 44

  
  //speedControl EEPROM
  float speedControl_speed = 50.00;             //speed of the horizontal slider while in speedControl Mode in inches per minute
  #define speedControl_speed_eeAddress 4    //Location of information in eeprom

  unsigned int speedControl_counter = 10;             //speed of the horizontal slider while in speedControl Mode in inches per minute
  #define speedControl_counter_eeAddress 48     //Location of information in eeprom
  
  unsigned int speedControl_rDistance = 0;          //amount in degrees to rotate camera over one slide operation in speed control mode
  #define speedControl_rDistance_eeAddress 8 //Location of information in eeprom


  //timeControl EEPROM 
  unsigned int timeControl_seconds = 30;           //speed of the horizontal slider while in speedControl Mode
  #define timeControl_seconds_eeAddress 28  //Location of information in eeprom

  unsigned int timeControl_minutes = 0;            //speed of the horizontal slider while in speedControl Mode
  #define timeControl_minutes_eeAddress 32  //Location of information in eeprom

  unsigned int timeControl_hours = 0;              //speed of the horizontal slider while in speedControl Mode
  #define timeControl_hours_eeAddress 36    //Location of information in eeprom
  
  long timeControl_rDistance = 0;          //amount in degrees to rotate camera over one slide operation in speed control mode
  #define timeControl_rDistance_eeAddress 40//Location of information in eeprom


  //motionControl EEPROM
  double motionControl_dAway = 4.;          //Distance of object to be tracked tangent to the rail
  #define  motionControl_dAway_eeAddress 12 //Location of information in eeprom

  double motionControl_dDown= 4.;           //distance of the tracked object from theright side and parallel to the rail
  #define  motionControl_dDown_eeAddress 16 //Location of information in eeprom

  unsigned int motionControl_speed= 50;            //speed of the shot
  #define  motionControl_speed_eeAddress 20 //Location of information in eeprom

  unsigned int motionControl_seconds = 30;           //speed of the horizontal slider while in speedControl Mode
  #define motionControl_seconds_eeAddress 24  //Location of information in eeprom

  unsigned int motionControl_minutes = 0;            //speed of the horizontal slider while in speedControl Mode
  #define motionControl_minutes_eeAddress 52  //Location of information in eeprom

  unsigned int motionControl_hours = 0;              //speed of the horizontal slider while in speedControl Mode
  #define motionControl_hours_eeAddress 56    //Location of information in eeprom

  
// Stored Values
  float LENGTH = length_Inches * Steps_Per_inch;  //converts length into steps
  bool moveLeft = true;
  bool changeValue = false;                       //determines whether to configure the operation values or scroll down a menu, this is flipped by clicking encoder while over value
  int changeCounter = 0;                         // if change value is true "changeCounter" will be changed instead of the normal "counter" value
  bool runningPath = false;                       //tracks wether or not an operation is curretly running
  unsigned long currentMicros;
  bool negative = false;
  float angleTracking;
  unsigned int cancel;
  float angle;
  float pause;
  bool stepperEnabled = false;
  int twoTick = 0;

  


void setup() {
/*
  for (int i = 0 ; i < EEPROM.length() ; i++) {  //uncomment to clear memory
    EEPROM.write(i, 0);
  }
*/
  Serial.begin(9600);

//STEPPER
  pinMode(horizontalStepPin, OUTPUT);  //defines all the stepper controll pis as outputs
  pinMode(horizontalDirPin, OUTPUT);
  pinMode(rotationStepPin, OUTPUT);
  pinMode(rotationlDirPin, OUTPUT);  
  pinMode(disablePin, OUTPUT);

  digitalWrite(disablePin, HIGH);       //disables all steppers  

//OLED DISPLAY  
 // display.clearDisplay();                    //Display Logo                                             // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                       // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.drawBitmap(40, 16, image_data_logo, 40, 47, 1);
  display.display();
  delay(3000);
  display.cp437(true);
  
//ENCODER

  pinMode (outputA,INPUT);                          //Sets encoder pins as inputs
  pinMode (outputB,INPUT);
  aLastState = digitalRead(outputA);                //saves encoders current position
  pinMode(encoderButtonInterruptPin, INPUT_PULLUP); //defines encoder button intterupt pin
  attachInterrupt(digitalPinToInterrupt(encoderButtonInterruptPin), clicked, RISING);     //if encoderButtonInterruptPin is rising then stop everything and run clicked()
  attachInterrupt(digitalPinToInterrupt(encodeRotationrInterruptPin), encoder, CHANGE);   //if encodeRotationrInterruptPin has changed stop everything and run encoder()
  
//Menu Initioalization
  menu = homeMenuID;   //set the current screen to homescreen (this is defined again because it was sensing phantom presses on startup)

  
}

void loop() {
  //Serial.println(menu);
//MENU ORGANIZATION 
  //sends the program to the function that matches the current desired screen
  if (menu == homeMenuID){
    mainMenu();
  }
  if (menu == timeControlID){
    menuTimeControl();
  }
  if (menu == speedControlID){
    menuSpeedControl();
  }
  if (menu == motionControlID){
    menuMotionControl();
  }
  if (menu == globalValuesID){
    menuGlobalValues();
  }
  if (menu > menuTuneID){
    menuTune();
  }
}
