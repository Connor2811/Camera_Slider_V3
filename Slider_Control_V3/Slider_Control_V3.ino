//testing github again

//OLED DISPLAY
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
/*
static const unsigned char PROGMEM image_data_logo[] = {
 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0x60, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x6c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x0c, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x0c, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x00, 0xd8, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x00, 0x0c, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xe0, 0x1c, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xf0, 0x38, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xf8, 0x70, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xdc, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xcf, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xcf, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xc7, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xc7, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xcf, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xdc, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xf8, 0x70, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xf0, 0x38, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xe0, 0x1c, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0xe0, 0x1c, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x00, 0x0c, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x00, 0xd8, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x0c, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x6c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0x60, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xf8, 0x20, 0x71, 0xe4, 0x11, 0xc4, 0xf8, 
    0x98, 0x70, 0x81, 0x04, 0x11, 0xc4, 0xc0, 
    0x98, 0x50, 0x81, 0x04, 0x11, 0xa4, 0xc0, 
    0xf8, 0xdc, 0x41, 0xe4, 0x11, 0xa4, 0xf8, 
    0x84, 0x8c, 0x21, 0x04, 0x11, 0x94, 0xc0, 
    0x85, 0xfe, 0x11, 0x04, 0x11, 0x94, 0xc0, 
    0x85, 0x02, 0x91, 0x04, 0x11, 0x8c, 0xc0, 
    0x85, 0x02, 0x91, 0x04, 0x11, 0x8c, 0xc0, 
    0xf9, 0x02, 0x61, 0xe7, 0xd1, 0x8c, 0xf8, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x07, 0x83, 0xc7, 0x90, 0x38, 0x62, 0x00, 
    0x04, 0x42, 0x0e, 0x10, 0x44, 0x62, 0x00, 
    0x04, 0x22, 0x08, 0x10, 0x80, 0x52, 0x00, 
    0x04, 0x23, 0xc6, 0x10, 0x80, 0x52, 0x00, 
    0x04, 0x22, 0x01, 0x10, 0x9c, 0x4a, 0x00, 
    0x04, 0x22, 0x01, 0x10, 0x9c, 0x4a, 0x00, 
    0x04, 0x22, 0x00, 0x90, 0x84, 0x4a, 0x00, 
    0x04, 0x42, 0x08, 0x90, 0x44, 0x46, 0x00, 
    0x07, 0x83, 0xc7, 0x10, 0x38, 0x46, 0x00
};

static const unsigned char PROGMEM image_data_Logosmall[] = {
        0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x33, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x30, 0xcc, 0x00, 0x00, 
    0x00, 0x00, 0x30, 0x0f, 0x00, 0x00, 
    0x00, 0x00, 0x30, 0x01, 0x80, 0x00, 
    0x00, 0x00, 0x37, 0x03, 0x80, 0x00, 
    0x00, 0x00, 0x37, 0x03, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0x86, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0xce, 0x00, 0x00, 
    0x00, 0x00, 0x36, 0xfc, 0x00, 0x00, 
    0x00, 0x00, 0x36, 0x78, 0x00, 0x00, 
    0x00, 0x00, 0x36, 0x78, 0x00, 0x00, 
    0x00, 0x00, 0x36, 0xfc, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0xce, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0x86, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0x03, 0x00, 0x00, 
    0x00, 0x00, 0x37, 0x03, 0x80, 0x00, 
    0x00, 0x00, 0x30, 0x01, 0x80, 0x00, 
    0x00, 0x00, 0x30, 0x0f, 0x00, 0x00, 
    0x00, 0x00, 0x30, 0xcc, 0x00, 0x00, 
    0x00, 0x00, 0x33, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xf0, 0x41, 0x8f, 0x42, 0x21, 0x1c, 
    0x90, 0xe2, 0x48, 0x42, 0x31, 0x10, 
    0x90, 0xa2, 0x08, 0x42, 0x39, 0x10, 
    0xf1, 0xb1, 0x0f, 0x42, 0x29, 0x1c, 
    0x89, 0x10, 0x88, 0x42, 0x25, 0x10, 
    0x8b, 0xf8, 0x48, 0x42, 0x25, 0x10, 
    0x8a, 0x0a, 0x48, 0x42, 0x23, 0x10, 
    0xf2, 0x09, 0x8f, 0x7a, 0x23, 0x1c, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x0f, 0x0f, 0x39, 0x03, 0x08, 0x80, 
    0x08, 0x88, 0x45, 0x04, 0x88, 0x80, 
    0x08, 0x48, 0x41, 0x08, 0x0c, 0x80, 
    0x08, 0x4f, 0x31, 0x08, 0x0c, 0x80, 
    0x08, 0x48, 0x09, 0x0b, 0x8a, 0x80, 
    0x08, 0x48, 0x05, 0x08, 0x8a, 0x80, 
    0x08, 0x88, 0x45, 0x04, 0x89, 0x80, 
    0x0f, 0x0f, 0x39, 0x03, 0x09, 0x80
};
  
*/
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

//SUBMENU LOGIC  
  int subMenu;
  #define tuneSubMenuID 0
  #define speedSubMenuID 1
  #define angleSubMenuID 2
  #define secondsSubMenuID 3
  #define minutesSubMenuID 4
  #define hoursSubMenuID 5
  #define directionSubMenuID 6
  #define runSubMenuID 7
  #define returnSubMenuID 8
  #define mainSubMenuID 9
  #define steppersSubMenuID 10
  #define jogSubMenuID 11
  #define lengthSubMenuID 12
  
  
  
  

//EEPROM CONFIGURE


  //Global EEPROM
  long length_Inches = 30;                  //length of the slider rail in inches
  #define length_Inches_eeAddress  0          //Location of information in eeprom

  long Steps_Per_inch = 2032;
  #define Steps_Per_inch_eeAddress 44

  
  //speedControl EEPROM
  float speedControl_speed = 50.00;             //speed of the horizontal slider while in speedControl Mode in inches per minute
  #define speedControl_speed_eeAddress  4     //Location of information in eeprom

  int speedControl_counter = 10;             //speed of the horizontal slider while in speedControl Mode in inches per minute
  #define speedControl_counter_eeAddress 48    //Location of information in eeprom
  
  long speedControl_rDistance = 0;          //amount in degrees to rotate camera over one slide operation in speed control mode
  #define speedControl_rDistance_eeAddress 8 //Location of information in eeprom


  //timeControl EEPROM 
  unsigned long timeControl_seconds = 30;           //speed of the horizontal slider while in speedControl Mode
  #define timeControl_seconds_eeAddress 28  //Location of information in eeprom

  unsigned long timeControl_minutes = 0;            //speed of the horizontal slider while in speedControl Mode
  #define timeControl_minutes_eeAddress 32  //Location of information in eeprom

  unsigned long timeControl_hours = 0;              //speed of the horizontal slider while in speedControl Mode
  #define timeControl_hours_eeAddress 36    //Location of information in eeprom
  
  long timeControl_rDistance = 0;          //amount in degrees to rotate camera over one slide operation in speed control mode
  #define timeControl_rDistance_eeAddress 40//Location of information in eeprom


  //motionControl EEPROM
  double motionControl_dAway = 4.;          //Distance of object to be tracked tangent to the rail
  #define  motionControl_dAway_eeAddress 12 //Location of information in eeprom

  double motionControl_dDown= 4.;           //distance of the tracked object from theright side and parallel to the rail
  #define  motionControl_dDown_eeAddress 16 //Location of information in eeprom

  long motionControl_speed= 50;            //speed of the shot
  #define  motionControl_speed_eeAddress 20 //Location of information in eeprom

  long motionControl_time= 50;            //time in seconds to traverse
  #define  motionControl_time_eeAddress 24 //Location of information in eeprom

  
// Stored Values
  long LENGTH = length_Inches * Steps_Per_inch;  //converts length into steps
  String movementDirection = "  left ";            //sets direction of travel, this is flopped after each operation
  int changeValue = false;                       //determines whether to configure the operation values or scroll down a menu, this is flipped by clicking encoder while over value
  int changeCounter = 0;                         // if change value is true "changeCounter" will be changed instead of the normal "counter" value
  int runningPath = false;                       //tracks wether or not an operation is curretly running
  unsigned long currentMicros;
  int negative = false;
  String stepperState = " disabled";

  


void setup() {
//   for (int i = 0 ; i < EEPROM.length() ; i++) {
//    EEPROM.write(i, 0);
 // }





  
  Serial.begin(9600);

//OLED DISPLAY  
 // display.clearDisplay();                    //Display Logo
 /*
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
    */                                               // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                       // Don't proceed, loop forever
  }
 // display.clearDisplay();
 // display.drawBitmap(40, 16, image_data_logo, 53, 48, 1);
  //display.display();
  //delay(3000);
   // display.cp437(true);
  
//ENCODER

  pinMode (outputA,INPUT);                          //Sets encoder pins as inputs
  pinMode (outputB,INPUT);
  aLastState = digitalRead(outputA);                //saves encoders current position
  pinMode(encoderButtonInterruptPin, INPUT_PULLUP); //defines encoder button intterupt pin
  attachInterrupt(digitalPinToInterrupt(encoderButtonInterruptPin), clicked, RISING);     //if encoderButtonInterruptPin is rising then stop everything and run clicked()
  attachInterrupt(digitalPinToInterrupt(encodeRotationrInterruptPin), encoder, CHANGE);   //if encodeRotationrInterruptPin has changed stop everything and run encoder()

//STEPPER
  pinMode(horizontalStepPin, OUTPUT);  //defines all the stepper controll pis as outputs
  pinMode(horizontalDirPin, OUTPUT);
  pinMode(rotationStepPin, OUTPUT);
  pinMode(rotationlDirPin, OUTPUT);  
  pinMode(disablePin, OUTPUT);

  digitalWrite(disablePin, HIGH);       //disables all steppers
  
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
