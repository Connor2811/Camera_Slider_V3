

//the following functions are attached to interupts and run depending on if the encoder button was pressed or if the encoder changed position


void encoder(){
   aState = digitalRead(outputA);          // Reads the "current" state of the outputA
                                           // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){              // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise                           
     if (digitalRead(outputB) != aState) { //check to see if its spinning clockwise 
       if (changeValue == false){          //if we are not trying to change a value increase check too see if we've done two clicks in that direction
        if (twoTick >= 1){                 //twoTick has been incremented by one already add one to counter (kind of a rotary debounce)
          counter ++;                      //trackes encoder spins
          twoTick = 0;       
        }
        else{                              //if we havent spun the encoder already go ahead and add one
          twoTick ++;            
        }
       }
       else if (changeValue == true){      //if we are in fact tyring to change a value increase "ChangeCounter" instead with each click being one adition
        changeCounter ++;
       } 
     } 
     else{                                //if we are spinning anticlockwise run this
      if (changeValue == false){          //if we not are trying to change a value decrease "counter" 
        if (twoTick <= -1){
          counter --;
          twoTick = 0;       
        }
        else{
          twoTick --;            
        }
      }
      else if (changeValue == true && changeCounter > 0 && negative == false){   //if we have already increased a value and it cant be negative then we can subtract
        changeCounter --;
      }
      else if (changeValue == true && negative == true){   //if we are trying to change a value that can be negative then go ahead and substract past 0
        changeCounter --;
      }
     }   
   } 
   aLastState = aState;                  // Updates the previous state of the outputA with the current state
}

void clicked() {                        //if the button on the encoder was clicked this function will run
    delay(1000);   //wait a bit to debounce click

  if (menu == homeMenuID){              //if we detected a click while on homemenu go to selected menu and load the eeprom data for that menu
    if (counter == 0){
      menu = timeControlID;
      EEPROM.get(moveLeft_eeAddress, moveLeft);                              //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_seconds_eeAddress, timeControl_seconds);        //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_minutes_eeAddress, timeControl_minutes);        //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_hours_eeAddress, timeControl_hours);            //load in EEPROM value for this modes settings
      EEPROM.get(timeControl_rDistance_eeAddress, timeControl_rDistance);    //load in EEPROM value for this modes settings
    }
    else if (counter == 1){
       menu = speedControlID;
       EEPROM.get(moveLeft_eeAddress, moveLeft); 
       EEPROM.get(speedControl_speed_eeAddress, speedControl_speed);           //load in EEPROM value for this modes settings
       EEPROM.get(speedControl_rDistance_eeAddress, speedControl_rDistance);   //load in EEPROM value for this modes settings
       EEPROM.get(speedControl_counter_eeAddress, speedControl_counter);       //load in EEPROM value for this modes settings
    }
    else if (counter == 2){
       menu = motionControlID;
       EEPROM.get(moveLeft_eeAddress, moveLeft); 
       EEPROM.get(motionControl_dAway_eeAddress, motionControl_dAway);           //load in EEPROM value for this modes settings
       EEPROM.get(motionControl_dDown_eeAddress, motionControl_dDown);           //load in EEPROM value for this modes settings
       EEPROM.get(motionControl_seconds_eeAddress, motionControl_seconds);       //load in EEPROM value for this modes settings
       EEPROM.get(motionControl_minutes_eeAddress, motionControl_minutes);       //load in EEPROM value for this modes settings
       EEPROM.get(motionControl_hours_eeAddress, motionControl_hours);           //load in EEPROM value for this modes settings
          
    }
    else if (counter == 3){
       menu = loopControlID;
       EEPROM.get(moveLeft_eeAddress, moveLeft); 
       EEPROM.get(loopControl_speed_eeAddress, loopControl_speed);           //load in EEPROM value for this modes settings
       EEPROM.get(loopControl_rDistance_eeAddress, loopControl_rDistance);   //load in EEPROM value for this modes settings
       EEPROM.get(loopControl_counter_eeAddress, loopControl_counter);       //load in EEPROM value for this modes settings  
    }  
    else if (counter == 4){
       menu = calculatorID;
       EEPROM.get(frameRate_eeAddress, frameRate);         
       EEPROM.get(timeLapseLength_eeAddress, timeLapseLength); 
       EEPROM.get(finalVideoLength_eeAddress,finalVideoLength); 
    }
    else if (counter == 5){
       menu = globalValuesID;
       EEPROM.get(length_Inches_eeAddress, length_Inches);           //load in EEPROM value for this modes settings
    }
    counter = 0;                   //reset the counter so that the cursor is at the top of the new screen
  }

  
  //timeControlMenu Logic
  else if (menu == timeControlID){      
    commonClick();                                                   //run function that controls the first 3 options of every mode
    
    if (counter == 3 && changeValue == false){                       //put controller in mode to edit seconds value
      changeValue = true;
      changeCounter = timeControl_seconds;                           //the encoder changeCounter value is now equal to timeControl_seconds and will be increased by the encoder function
    }
    else if (counter == 3 && changeValue == true){                       //exit edit seconds mode
       timeControl_seconds = changeCounter;                              //update the seconds with the tracked value
       EEPROM.put(timeControl_seconds_eeAddress, timeControl_seconds);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 4 && changeValue == false){         //put controller in mode to edit value
      changeValue = true;
      changeCounter = timeControl_minutes;                  //the change counter is now set to the value and is incremented by encoder()
    }
    else if (counter == 4 && changeValue == true){                       //exit edit mode
       timeControl_minutes = changeCounter;                              //update the value
       EEPROM.put(timeControl_minutes_eeAddress, timeControl_minutes);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 5 && changeValue == false){          //put controller in mode to edi value
      changeValue = true;
      changeCounter = timeControl_hours;                     //the change counter is now set to the value and is incremented by encoder()
    }
    else if (counter == 5 && changeValue == true){                     //exit edit s mode
       timeControl_hours = changeCounter;                              //update the value
       EEPROM.put(timeControl_hours_eeAddress, timeControl_hours);     //send value to eeprom
       changeCounter = 0;                                              //reset change counter to zero for next time
       changeValue = false;                                            //termiate edit mode
    }

    else if (counter == 6 && changeValue == false){           //put controller in mode to edit speed value
      changeValue = true;                                     //allow variable to be negative
      negative = true;
      changeCounter = timeControl_rDistance;                  //speed is now loaded speed plus the counted encoder ticks
    }
    else if (counter == 6 && changeValue == true){                         //exit edit mode
      negative = false;
       timeControl_rDistance = changeCounter;                              //update the value
       EEPROM.put(timeControl_rDistance_eeAddress, timeControl_rDistance); //send value to eeprom
       changeCounter = 0;                                                  //reset change counter to zero for next time
       changeValue = false;                                                //termiate edit mode
    }
    
    else if (counter == 7){                     //if clicked on Run then run the configured operation
      timeControl();                            //run the operation
    }
  }


  //speedControlMenu Logic
  else if (menu == speedControlID){
    
   commonClick();
      
    if (counter == 3 && changeValue == false){                            //put controller in edit mode
      changeValue = true;
      changeCounter = speedControl_counter;                               //speed is now loaded speed plus the counted encoder ticks
    }
    else if( counter == 3 && changeValue == true){                        //exit edit mode
      speedControl_speed = pow(changeCounter,3) * .0006;                  //update the value
      speedControl_counter = changeCounter;
      EEPROM.put(speedControl_speed_eeAddress, speedControl_speed);       //send value to eeprom
      EEPROM.put(speedControl_counter_eeAddress, speedControl_counter);   //send value to eeprom
      changeCounter = 0;                                                  //reset change counter to zero for next time
      changeValue = false;                                                //termiate edit mode
    }

    else if (counter == 4 && changeValue == false){                       //put controller in edit mode
      changeValue = true;                                              
      negative = true;
      changeCounter = speedControl_rDistance;                             //angle is now loaded angle plus the counted encoder ticks
    }    
    else if (counter == 4 && changeValue == true){                          //exit edit angle mode
      negative = false;
      speedControl_rDistance = changeCounter;                               //update the stored angle
      EEPROM.put(speedControl_rDistance_eeAddress, speedControl_rDistance); //send new angle to eeprom
      changeCounter = 0;                                                    //reset change counter to zero for next time 
      changeValue = false;                                                  //termiate edit mode
    }
    
    else if (counter == 5){                     //if clicked on Run then run the configured operation
      speedControl();                           //run the operation
    }
  }

  //motionControlMenu Logic
  else if (menu == motionControlID){                                     //if in motion control mode run this     
    
    commonClick();

    if (counter == 3 && changeValue == false){                           //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_dAway;                               //changeCounter is set to old value so it can be incremented by encoder()
    }
    else if (counter == 3 && changeValue == true){                       //exit edit mode
       motionControl_dAway = changeCounter;                              //update the value
       EEPROM.put(motionControl_dAway_eeAddress, motionControl_dAway);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 4 && changeValue == false){         //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_dDown;                  //value is now loaded value the counted encoder ticks
    }
    else if (counter == 4 && changeValue == true){                       //exit edit mode
       motionControl_dDown = changeCounter;                              //update the value
       EEPROM.put(motionControl_dDown_eeAddress, motionControl_dDown);   //send value to eeprom
       changeCounter = 0;                                                //reset change counter to zero for next time
       changeValue = false;                                              //termiate edit mode
    }

    else if (counter == 5 && changeValue == false){           //put controller in mode to edit seconds value
      changeValue = true;
      changeCounter = motionControl_seconds;                  //the encoder changeCounter value is now equal to timeControl_seconds and will be increased by the encoder function
    }
    else if (counter == 5 && changeValue == true){                          //exit edit seconds mode
       motionControl_seconds = changeCounter;                               //update the seconds with the tracked value
       EEPROM.put(motionControl_seconds_eeAddress, motionControl_seconds);  //send value to eeprom
       changeCounter = 0;                                                   //reset change counter to zero for next time
       changeValue = false;                                                 //termiate edit mode
    }

    else if (counter == 6 && changeValue == false){                         //put controller in mode to edit value
      changeValue = true;
      changeCounter = motionControl_minutes;                                //the change counter is now set to the value and is incremented by encoder()
    }
    else if (counter == 6 && changeValue == true){                          //exit edit mode
       motionControl_minutes = changeCounter;                               //update the value
       EEPROM.put(motionControl_minutes_eeAddress, motionControl_minutes);  //send value to eeprom
       changeCounter = 0;                                                   //reset change counter to zero for next time
       changeValue = false;                                                 //termiate edit mode
    }

    else if (counter == 7 && changeValue == false){                         //put controller in mode to edi value
      changeValue = true;
      changeCounter = motionControl_hours;                                  //the change counter is now set to the value and is incremented by encoder()
    }
    else if (counter == 7 && changeValue == true){                          //exit edit s mode
       motionControl_hours = changeCounter;                                 //update the value
       EEPROM.put(motionControl_hours_eeAddress, motionControl_hours);      //send value to eeprom
       changeCounter = 0;                                                   //reset change counter to zero for next time
       changeValue = false;                                                 //termiate edit mode
    }
    
    else if (counter == 8){                     //if clicked on Run then run the configured operation
      delay (10000);                            //give it a second to debounce the button
      motionControl();                          //run the operation
    }
  }


  //loopControlMenu Logic
  else if (menu == loopControlID){

    commonClick();   
      
    if (counter == 3 && changeValue == false){                         //put controller in edit mode
      changeValue = true;
      changeCounter = loopControl_counter;                            //speed is now loaded speed plus the counted encoder ticks
    }
    else if( counter == 3 && changeValue == true){                         //exit edit mode
      loopControl_speed = pow(changeCounter,3) * .0006;                    //update the value
      loopControl_counter = changeCounter;
      EEPROM.put(loopControl_speed_eeAddress, loopControl_speed);          //send value to eeprom
      EEPROM.put(loopControl_counter_eeAddress, loopControl_counter);      //send value to eeprom
      changeCounter = 0;                                                   //reset change counter to zero for next time
      changeValue = false;                                                 //termiate edit mode
    }

    else if (counter == 4 && changeValue == false){                        //put controller in edit mode
      negative = true;
      changeValue = true;                                              
      changeCounter = loopControl_rDistance;                                //angle is now loaded angle plus the counted encoder ticks
    }    
    else if (counter == 4 && changeValue == true){                          //exit edit angle mode
      negative = false;
      loopControl_rDistance = changeCounter;                                //update the stored angle
      EEPROM.put(loopControl_rDistance_eeAddress, loopControl_rDistance);   //send new angle to eeprom
      changeCounter = 0;                                                    //reset change counter to zero for next time 
      changeValue = false;                                                  //termiate edit mode
    }
    
    else if (counter == 5){                     //if clicked on Run then run the configured operation
      loopControl();                           //run the operation
    }
  }

  //TimeLapse Calculator Logic
  else if (menu == calculatorID){
    if (counter == 0){                                        //if we click on return, send us back to the home menu
      menu = homeMenuID;
    }   
    else if (counter == 1 && changeValue == false){           //put the controller into value adjust mode and set the change counter equal to framrate         
      changeValue = true;
      changeCounter = frameRate;                            
    }
    else if (counter == 1 && changeValue == true){           //if clicked again exit edit more
       frameRate = changeCounter;                            //set the framerate equal to the change counter
       EEPROM.put(frameRate_eeAddress, frameRate);           //send value to eeprom
       changeCounter = 0;                                    //reset change counter to zero for next time
       changeValue = false;                                  //termiate edit mode
    }

    else if (counter == 2 && changeValue == false){          //put controller in mode to edit value
      changeValue = true;
      changeCounter = timeLapseLength;                       //the encoder changeCounter value is now equal to the timeplaselength value
    }
    else if (counter == 2 && changeValue == true){                  //exit edit mode
       timeLapseLength = changeCounter;                             //update the timelapse length with the tracked value
       EEPROM.put(timeLapseLength_eeAddress, timeLapseLength);      //send value to eeprom
       changeCounter = 0;                                           //reset change counter to zero for next time
       changeValue = false;                                         //termiate edit mode
    }

    else if (counter == 3 && changeValue == false){                //put controller in mode to edit seconds value
      changeValue = true;
      changeCounter = finalVideoLength;                            //the encoder changeCounter value is now equal to saved video length value
    }
    else if (counter == 3 && changeValue == true){                  //exit edit mode
       finalVideoLength = changeCounter;                            //update the finalvideolength value with the tracked value
       EEPROM.put(finalVideoLength_eeAddress, finalVideoLength);    //send value to eeprom
       changeCounter = 0;                                           //reset change counter to zero for next time
       changeValue = false;                                         //termiate edit mode
    }  
  }



  //global values adjustment logic
  else if (menu == globalValuesID){
    
    if (counter == 0){    //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

    
    else if (counter == 1 && changeValue == false){         //put controller in mode to edit the length of the rails
      changeValue = true;
      changeCounter = length_Inches;                        //set the change counter equal to the eeprom value for length
    }
    else if (counter == 1 && changeValue == true){          //exit edit mode
       length_Inches = changeCounter;                       //update the length value
       EEPROM.put(length_Inches_eeAddress, length_Inches);  //send value to eeprom
       LENGTH = length_Inches * Steps_Per_inch;             //converts length into steps and save
       changeCounter = 0;                                   //reset change counter to zero for next time
       changeValue = false;                                 //termiate edit mode
    }
  }


    //TUNE menu adjustment logic
    else if (menu > menuTuneID){
    
      if (counter == 0){                        //if we click on return send us back to the home menu
        menu = menu - menuTuneID;
      }
      else if (counter == 1){                  //if this option is clicked enable the stepper motors
        stepperEnabled = !stepperEnabled;
        enableSteppers();               
      }
  
      else if (counter == 2){                  //if this option is clicked jog the carrige in the oppposite direction of the shot
        runReset();
      }
    }
}


void commonClick(){
      if (counter == 0){                             //if we click on return send us back to the home menu
      menu = homeMenuID;
    }

        else if (counter == 1){                     //if clicked on Run then run the configured operation
        menu = menuTuneID + menu;
        counter = 0;
      } 

    else if (counter == 2){                         //if clicked on direction -> FLIP the direction of travel
      moveLeft = !moveLeft;
      EEPROM.put(moveLeft_eeAddress, moveLeft);     //send value to eeprom   
    }
}
