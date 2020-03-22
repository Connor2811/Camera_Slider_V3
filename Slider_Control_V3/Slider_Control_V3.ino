#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//char for logo displayed on startup
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



//char for logo displayed on menu screen
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
 #define outputA 3      //first data input pin for the encoder
 #define outputB 4      //second data input pin for the encoder
 int counter = 0;       //tracks how many clicks the encoder has had
 int aState;            //Value to store the current state of the Encoder
 int aLastState;        //Value to store the last state of the Encoder
 const byte encoderButtonInterruptPin = 2;        //inerupt pin attached to the encoders button  
 const byte encodeRotationrInterruptPin = 3;      //interupt pin attached to the encoders rotation

//STEPPER
#define horizontalDirPin 5        //direction pin for horizontal motor       
#define horizontalStepPin 6       //drive pin for horizontal motor  
#define rotationlDirPin 7         //direction pin for rotation motor
#define rotationStepPin 8         //drive pin for rotation motor
#define disablePin 9              //pin to dissable both stepper drivers

//MENU LOGIC
  byte menu = 0;                  //menus are stored as numbers
  #define homeMenuID 0            //numerical ID for all menu options
  #define timeControlID 1        
  #define speedControlID 2
  #define motionControlID 3
  #define loopControlID 4
  #define globalValuesID 5
  #define calculatorID 6
  #define menuTuneID 100
  byte menuOptionCount;           //number of options availible on a given menu
  
  
  
  

//EEPROM CONFIGURE


  //Global EEPROM
  byte length_Inches = 30;                        //length of the slider rail in inches
  #define length_Inches_eeAddress 0               //Location of information in eeprom

  unsigned int Steps_Per_inch = 2032;             //save value to configure steps per-IN on the fly
  #define Steps_Per_inch_eeAddress 4              //Location of information in eeprom
  
  bool moveLeft = true;                           //stores the preferred direction of travel
  #define moveLeft_eeAddress 8                    //Location of information in eeprom

  
  //speedControl EEPROM
  float speedControl_speed = 0 ;                  //speed of the horizontal slider while in speedControl Mode in inches per minute
  #define speedControl_speed_eeAddress 12         //Location of information in eeprom

  unsigned int speedControl_counter = 0;          //enables the use of an exponetial function to tune the speed
  #define speedControl_counter_eeAddress 16       //Location of information in eeprom
  
  int speedControl_rDistance = 0;                 //amount in degrees to rotate camera over one slide operation in speed control mode
  #define speedControl_rDistance_eeAddress 20     //Location of information in eeprom


  //timeControl EEPROM 
  byte timeControl_seconds = 0;                   //speed of the horizontal slider while in timeControl Mode
  #define timeControl_seconds_eeAddress 24        //Location of information in eeprom

  byte timeControl_minutes = 0;                   //time of movement in minutes
  #define timeControl_minutes_eeAddress 28        //Location of information in eeprom

  byte timeControl_hours = 0;                     //time of movement in hours
  #define timeControl_hours_eeAddress 32          //Location of information in eeprom
  
  int timeControl_rDistance = 0;                  //amount in degrees to rotate camera over one slide operation in timeControl mode
  #define timeControl_rDistance_eeAddress 36      //Location of information in eeprom


  //motionControl EEPROM
  byte motionControl_dAway = 0;                   //Distance of object to be tracked tangent to the rail
  #define  motionControl_dAway_eeAddress 40       //Location of information in eeprom

  byte motionControl_dDown= 0;                    //distance of the tracked object from the from the camera and parallel to the rail
  #define  motionControl_dDown_eeAddress 44       //Location of information in eeprom

  byte motionControl_seconds = 30;                //time of movement in seconds
  #define motionControl_seconds_eeAddress 48      //Location of information in eeprom

  byte motionControl_minutes = 0;                 //time of movment in minutes
  #define motionControl_minutes_eeAddress 52      //Location of information in eeprom

  byte motionControl_hours = 0;                   //time of the movement in hours
  #define motionControl_hours_eeAddress 56        //Location of information in eeprom

 
  //loopControl EEPROM
  float loopControl_speed = 0 ;                   //speed of the horizontal slider while in loopControl Mode in inches per minute
  #define loopControl_speed_eeAddress 60          //Location of information in eeprom

  unsigned int loopControl_counter = 0;           //tracks the ticks and saves them enabling an exponetial scroll curve
  #define loopControl_counter_eeAddress 64        //Location of information in eeprom
  
  int loopControl_rDistance = 0;                  //amount in degrees to rotate camera over one slide operation
  #define loopControl_rDistance_eeAddress 68      //Location of information in eeprom


  //CalculatorEEPROM
  byte frameRate = 0;                             //stores the desired framerate value
  #define frameRate_eeAddress 72                  //Location of information in eeprom

  byte timeLapseLength = 0;                       //stores the duration of the timeplase
  #define timeLapseLength_eeAddress 76            //Location of information in eeprom
  
  byte finalVideoLength = 0;                      //stores the desired final video length
  #define finalVideoLength_eeAddress 80           //Location of information in eeprom


  
// Stored Values
  float LENGTH = length_Inches * Steps_Per_inch;  //converts the user set length into usable steps
  bool changeValue = false;                       //determines whether to configure the operation values or scroll down a menu, this is flipped by clicking encoder while over value
  int changeCounter = 0;                          //if change value is true "changeCounter" will be changed instead of the normal "counter" value
  bool runningPath = false;                       //tracks wether or not an operation is curretly running                     
  bool negative = false;                          //determines weather the value being adjusted can go negative
  unsigned int angleTracking;                     //tracks how many steps the rotation motor has gone
  byte cancel;                                    //is set equal to encoder position and if position changes it cancels
  bool stepperEnabled = false;                    //tracks the current power state of the steppers
  int twoTick = 0;                                //is increased or decrease one for every click of the encoder, this makes scroll take two clicks and minimizes mis-spins
  unsigned long previousMillis = 0;

  


void setup() {
/*
  for (int i = 0 ; i < EEPROM.length() ; i++) {  //uncomment to clear eeprom memory
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
  pinMode(13, OUTPUT);

  digitalWrite(disablePin, HIGH);       //disables all steppers   right off the bat

//OLED DISPLAY  
  //check to see if we have enough Sram to run the oled screen
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                       // Don't proceed, loop forever
  }
  
  display.clearDisplay();                                 //clear the screens cache of any information
  display.drawBitmap(40, 16, image_data_logo, 40, 47, 1); //(x, y, image_data_logo, height, width, 1)
  display.display();                                      //write everything to the display and show the BaselineDesign logo
  delay(3000);
  display.cp437(true);                                    //allows for degree symbol to be shown
  
//ENCODER

  pinMode (outputA,INPUT);                          //Sets encoder pins as inputs
  pinMode (outputB,INPUT);
  aLastState = digitalRead(outputA);                //saves encoders current position
  pinMode(encoderButtonInterruptPin, INPUT_PULLUP); //defines encoder button intterupt pin
  attachInterrupt(digitalPinToInterrupt(encoderButtonInterruptPin), clicked, RISING);     //if encoderButtonInterruptPin is rising then stop everything and run clicked()
  attachInterrupt(digitalPinToInterrupt(encodeRotationrInterruptPin), encoder, CHANGE);   //if encodeRotationrInterruptPin has changed stop everything and run encoder()
  
//Menu Initioalization
  menu = homeMenuID;                    //set the current screen to homescreen (this is defined again because it was sensing phantom presses on startup)
}



void loop() {
//MENU ORGANIZATION 
  //sends the program to the correct menu depending on what has been selected 
  if (menu == homeMenuID){
    mainMenu();                     //menu where all sub-menus are selected. This screen also displays a logo in the corner
  }
  else if (menu == timeControlID){
    menuTimeControl();              //define the camera rotation amount, direction and duration of the shot and the slider will run the planned path
    if(runningPath == true){
      timeControl();
    }
  }
  else if (menu == speedControlID){
    menuSpeedControl();             //same as timeControll except instead of setting a duration you set a speed in in/min
    if(runningPath == true){
      speedControl();
    }
  }
  else if (menu == motionControlID){
    menuMotionControl();            //used to do panning tracking shots of objects, plug in the objects location and a duration
    if(runningPath == true){
     motionControl();
    }    
  }
  else if (menu == loopControlID){
    menuLoopControl();              //set a speed and angle and the slider will loop this plan untill the operation is aborted
    if(runningPath == true){
      loopControl();
    }    
  }
  else if (menu == globalValuesID){
    menuGlobalValues();             //allows user to customize any global variables of the slider such as length
  }
  else if (menu == calculatorID){
    calculator();                   //calculates the number of pictures and time between pictures when given framerate, length of shot, and desired length of the final video
  }
  else if (menu > menuTuneID){
    menuTune();                     //from any mode go to this menu to enable steppers and jog the carrige
  }
  
}
