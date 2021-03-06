//Following functions control the actual displaying of the menus




//MAINMENU DISPLAY
void  mainMenu() {               
  menuOptionCount = 5;                        //CHANGE ME: when more options are added
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(2);                     // Normal 1:1 pixel scale   
  display.setCursor(0,0);                     // Start at top-left corner
  display.println(F("Main Menu"));            //write this text


  //the following are the diffrent menus you can select and the logic to highlight them
  display.setTextSize(1.5);
  if(counter == 0){ //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Time Control");

  if(counter == 1){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Speed Control");

  if(counter == 2){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Motion Control");

  if(counter == 3){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Loop Control");    

    if(counter == 4){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println(F("Calculator"));

  if(counter == 5){  //highlight text if the cursor matches its location
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println(F("Global Values"));  
  display.drawBitmap(90, 22, image_data_Logosmall, 38, 42, 1);
  
  display.display();  //displays the configured text

  if(counter > menuOptionCount){                //loop cursor if it is now larger than the number of options
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}

//GLOBAL VALUES DISPLAY
void menuGlobalValues(){      //menu where the global values are set           
  menuOptionCount = 1;
  commonMenu();               //run the logic that most menus have
  display.println(F("Global Values")); 
  display.setTextSize(1.75);

  returnFunction();      //display the return menu and and highlight if on it
  
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); //Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);               // Draw white text
    } 
  display.print("Rail Length");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(length_Inches);       //if we arn't changing anything display the saved value
  }
  display.display();
  
   if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}


//TUNE MENU DISPLAY
void menuTune(){      //here we enable the steppers and jog the carrige
  
  if(counter > menuOptionCount){
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
  menuOptionCount = 2;
  commonMenu();             // Start at top-left corner
  display.println(F("TUNE OPTIONS"));
  display.setTextSize(1.75);

  returnFunction();

  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    } 
  display.print("Steppers:"); 
  if (stepperEnabled == true){
    display.println(" Enabled");
  }
  else{
    display.println(" Disabled");    
  }

  if(counter == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);                // Draw white text
    } 
  display.println("Jog to Start");
  
  display.display();
}



//TIMECONTROLL MENU
void  menuTimeControl() {

  menuOptionCount = 7;               //number of options on the menu
  int16_t i = 9;
 
  commonMenu();    
                  
  display.println(F("Time Control"));
  display.setTextSize(1.75);

  commonMenus();

  //Camera time delay Logic
  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Seconds:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_seconds);       //if we arn't changing anything display the saved value
  }


  if(counter == 4){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Minutes:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 4){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_minutes);       //if we arn't changing anything display the saved value
  }  


  if(counter == 5){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Hours:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 5){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(timeControl_hours);       //if we arn't changing anything display the saved value
  }

  //Camera Angle Display Logic
  if(counter == 6){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Camera Angle:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 6){     //if we are activily changing the angle display change counter
    display.print(changeCounter);
  } 
  else{
    display.print(timeControl_rDistance);     //otherwise change the stored value
  }
  display.println((char)223);
  

  //Start Shot Logic
  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();  //update screen

  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}




//SPEEDCONTROLL MENU DISPLAY
void  menuSpeedControl() {
  menuOptionCount = 5;                   //number of options on the menu
  int16_t i = 9;
  commonMenu();              // Start at top-left corner
  display.println(F("Speed Control"));
  display.setTextSize(1.75);

  commonMenus();
  
  //Camera Speed Logic
  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("speed:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.print( pow(changeCounter,3) * .0006);
  } 
  else{
    display.print(speedControl_speed);       //if we arn't changing anything display the saved value
  }
  display.println(" in/min");

  //Camera Angle Display Logic
  if(counter == 4){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Camera Angle:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 4){     //if we are activily changing the angle display change counter
    display.print(changeCounter);
  } 
  else{
    display.print(speedControl_rDistance);     //otherwise change the stored value
  }
  display.println((char)223);

  //Start Shot Logic
  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  display.display();  //update screen
  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}

//MOTIONCONTROLL MENU
void menuMotionControl() {
  menuOptionCount = 8;
  commonMenu();           // Start at top-left corner
  display.println(F("Motion Control"));
  display.setTextSize(1.75);

  commonMenus();
  
  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("D-Away:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.print(changeCounter);
  } 
  else{
    display.print(motionControl_dAway);       //if we arn't changing anything display the saved value
  }
  display.println("in");
  
  if(counter == 4){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("D-Down:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 4){    //if we are activley changing the value display change counter instead of the saved value
    display.print(changeCounter);
  } 
  else{
    display.print(motionControl_dDown);       //if we arn't changing anything display the saved value
  }
  display.println("in");

  if(counter == 5){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Seconds:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 5){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_seconds);       //if we arn't changing anything display the saved value
  }


  if(counter == 6){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Minutes:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 6){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_minutes);       //if we arn't changing anything display the saved value
  }  


  if(counter == 7){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Hours:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 7){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(motionControl_hours);       //if we arn't changing anything display the saved value
  }
  

  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  
  display.display();

  if(counter > menuOptionCount){
    counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}


//LOOPCONTROLL MENU DISPLAY
void menuLoopControl() {
  menuOptionCount = 5;                   //number of options on the menu
  int16_t i = 9;
  commonMenu();               // Start at top-left corner
  display.println(F("Loop Control"));
  display.setTextSize(1.75);

  commonMenus();

  //Camera Speed Logic
  if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Speed:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){    //if we are activley changing the value display change counter instead of the saved value
    display.print( pow(changeCounter,3) * .0006);
  } 
  else{
    display.print(loopControl_speed);       //if we arn't changing anything display the saved value
  }
  display.println(" in/min");

//Camera Angle Display Logic
  if(counter == 4){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Camera Angle:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 4){     //if we are activily changing the angle display change counter
    display.print(changeCounter);
  } 
  else{
    display.print(loopControl_rDistance);     //otherwise change the stored value
  }
  display.println((char)223);

  //Start Shot Logic
  if(counter == menuOptionCount){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.println("Start Shot");
  
  display.display();  //update screen
  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }
}


void commonMenus(){
  //display all of the options and highlight if they are selected
  if (counter <7){
    
    returnFunction();
  }
    //go to tune Menu
  if (counter <8){
    if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
    else{
      display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
    display.println("TUNE");
  }
  //Camera Direction Logic
  if(counter == 2){
   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
  }
  display.print("Direction:");
  display.setTextColor(SSD1306_WHITE);
  EEPROM.get(moveLeft_eeAddress, moveLeft);
  if (moveLeft == true){
    display.println(" Left");
  }
  else{
    display.println(" Right");
  }
}


void commonMenu(){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
}

void returnFunction(){
  if(counter == 0){
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
        }
      else{
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        }
      display.println("Return");
    }

void calculator(){
  
  menuOptionCount = 3;                   //number of options on the menu
  int16_t i = 9;
  display.clearDisplay();                //clear displau
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setTextSize(1.5);              // Normal 1:1 pixel scale   
  display.setCursor(0,0);                // Start at top-left corner
  display.println(F("Timelapse Calculator"));
  display.setTextSize(1.75);
  returnFunction();
  //Camera Speed Logic
  if(counter == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    } 
  display.print("Framerate:");      
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 1){    //if we are activley changing the value display change counter instead of the saved value
    display.println(changeCounter);
  } 
  else{
    display.println(frameRate);       //if we arn't changing anything display the saved value
  }

//Camera Angle Display Logic
  if(counter == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Shot Duration:");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  
  
  if (changeValue == true && counter == 2){     //if we are activily changing the angle display change counter
    if(changeCounter>=12){
      display.print(changeCounter/12);
      display.print(":");
     if(((changeCounter - (changeCounter/12)*12)) <= 1) {
      display.print("0");
     }
      display.println((changeCounter - (changeCounter/12)*12)*5);  
    }
    else{ 
      display.print("0");
      display.print(":");
      if(changeCounter <=1){
        display.print("0");
      }
      display.println(changeCounter * 5);
    }
    }
   
  else{
     if(timeLapseLength>=12){
        display.print(timeLapseLength/12);
        display.print(":");
        if(((timeLapseLength - (timeLapseLength/12)*12)) <= 1) {
          display.print("0");
        }
        display.println((timeLapseLength - (timeLapseLength/12)*12)*5);  
    }
    else{ 
        display.print("0");
        display.print(":");
        if(timeLapseLength <=1){
        display.print("0");
      }
        display.println(timeLapseLength * 5);
    }
  }

    if(counter == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    }
  else{
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    }
  display.print("Video Length(sec):");
  display.setTextColor(SSD1306_WHITE); 
  display.print(" ");
  if (changeValue == true && counter == 3){     //if we are activily changing the angle display change counter
    display.println(changeCounter);
  } 
  else{
    display.println(finalVideoLength);     //otherwise change the stored value
  }

  display.println(F("*********************"));
  display.print(F("Shot Count: "));
  display.println(finalVideoLength*frameRate);
  display.print(F("Shot Timing(s): "));
  display.println(timeLapseLength*5*60/(finalVideoLength*frameRate));




  
  display.display();  //update screen
  if(counter > menuOptionCount){  //loop cursor if it is greater than the number of options
   counter = menuOptionCount;
  }
  if (counter < 0){
    counter = 0;
  }

}

//screen for displaying current status of the path (not working)
/*void runScreen(){
   menuOptionCount = 5;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1.5);             // Normal 1:1 pixel scale   
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("!Shot In Progress!"));
  display.setTextSize(1.75);
  display.println("Scroll to Exit");
  display.display();
}*/
