//following functions controll the actual planned operation 



//OPERATION LOGIC FOR TIME CONTROLL
void timeControl(){
 
  float angle = (float(timeControl_rDistance) * 35.5552); //calculate angle from user configured values to 360degree scale
  float pause =((float(timeControl_seconds) * 1000000L) + (float(timeControl_minutes) * 60000000L) + (float(timeControl_hours) * 3600000000L))/float(LENGTH);       
  runningPath = true;
    determineDirection(angle);
    runStandardOp(pause, angle);
    returnToStart(angle);
    finishOp();
}

//OPERATION LOGIC FOR SPEED CONTROLL
void speedControl(){
  
  float angle = (float(speedControl_rDistance) * 35.5552); //calculate angle from user configured values to 360degree scale
  float pause =(((((float(length_Inches)/speedControl_speed)*60)) * 1000000L))/float(LENGTH);
  runningPath = true;
    determineDirection(angle);
    runStandardOp(pause, angle);
    returnToStart(angle);
    finishOp();
}

//OPERATION LOGIC FOR MOTION CONTROLL
void motionControl(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  stepperEnabled = true;
  float angle = ((atan(motionControl_dAway/motionControl_dDown)*(180/ M_PI))/.1125)*8; 
  determineDirection(angle);

  float calculatedAngle;
  float currentAngle = atan(motionControl_dAway/motionControl_dDown)*(180/ M_PI);
  angleTracking = 0;
  bool flip = true;
  float dTravled = 0;
  float pause =((float(motionControl_seconds) * 1000000L) + (float(motionControl_minutes) * 60000000L) + (float(motionControl_hours) * 3600000000L))/float(LENGTH);
  float myPause = (pause - ((25 * 1000000L)/float(LENGTH)))/8;
  cancel = counter;                             //set cancel equal to the current counter value
  
  for (float i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
         
    if ( abs(calculatedAngle - currentAngle)*4 >= .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
      digitalWrite(rotationStepPin, HIGH);   
      digitalWrite(horizontalStepPin,HIGH);   
      digitalWrite(rotationStepPin, LOW);   
      digitalWrite(horizontalStepPin, LOW);
      angleTracking ++;
      currentAngle = calculatedAngle;
    }
    else {
      digitalWrite(horizontalStepPin, HIGH);
      digitalWrite(horizontalStepPin, LOW);   
    } 
    for(long i=0; i <= myPause; i++){
      delayMicroseconds(8);
    }                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
  
    dTravled = (i/2032);
    if (dTravled < motionControl_dDown){
      calculatedAngle = atan(motionControl_dAway/(motionControl_dDown - dTravled))*(180/ M_PI);
    }
    else{
      calculatedAngle = atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI);
    }
    if(flip == true && dTravled >= motionControl_dDown){
      flip = false;
    }
    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
      runningPath = false;
    }      
  }  
  returnToStart(angle);
  finishOp();
}

//OPERATION LOGIC FOR LOOP CONTROLL
void loopControl(){
  
  float angle = (float(loopControl_rDistance) * 35.5552); //calculate angle from user configured values to 360degree scale
  float pause =(((((float(length_Inches)/float(loopControl_speed))*60)) * 1000000L))/float(LENGTH);
  runningPath = true;
  while(runningPath == true){
    determineDirection(angle);
    runStandardOp(pause, angle);
    if(runningPath == true){
      moveLeft = !moveLeft;
      EEPROM.put(moveLeft_eeAddress, moveLeft);
      delay(50);
    }
  }
  finishOp();
}

//DETERMINEDIRECTION LOGIC
void determineDirection(float angle){
    EEPROM.get(moveLeft_eeAddress, moveLeft);
    if (moveLeft == true){
      digitalWrite(horizontalDirPin, HIGH);
      digitalWrite(rotationlDirPin, HIGH);
      if (angle < 0){
        digitalWrite(rotationlDirPin, LOW);
      }
    } 
    else { //check desired camera direction and flip the horizontal and rotation direction if needed
      digitalWrite(horizontalDirPin, LOW);  //moveright
      digitalWrite(rotationlDirPin, LOW);   //move anticlockwise
      if (angle < 0){       //rotate camera opposite direction if degree value is negative
        digitalWrite(rotationlDirPin, HIGH);
        
      }
    }    
}

//RUNSTANDARDOP LOGIC
void runStandardOp(float &pause, float &angle){
  runScreen();
  if (runningPath == true){
    digitalWrite(disablePin, LOW);               //enable stepper drivers
    stepperEnabled = true;
    cancel = counter;                            //set cancel equal to the current counter value
    angleTracking = 0;
    float myAngle = float(LENGTH)/abs(angle);
    float myPause = pause/14;
    
    for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
      encoder();                                 //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
        i = LENGTH;
        runningPath = false;
      }
  
     if ( i  > (angleTracking * myAngle)) {       //step the camera angle motor a percentage of the time so it goes a percent of the total distace
        digitalWrite(rotationStepPin, HIGH);   
        digitalWrite(horizontalStepPin, HIGH);   
        digitalWrite(rotationStepPin, LOW);   
        digitalWrite(horizontalStepPin, LOW);
        angleTracking ++; 
     }
      
      else { 
        digitalWrite( horizontalStepPin, HIGH);  
        digitalWrite(horizontalStepPin, LOW);    
      }
      for(long i=0; i < myPause; i++){
        delayMicroseconds(8);
        }    
    }
  }
}

//RETURNTOSTART LOGIC
void returnToStart(float angle){
    //reverse movement and reset to original location
  EEPROM.get(moveLeft_eeAddress, moveLeft);
  moveLeft = !moveLeft;
  EEPROM.put(moveLeft_eeAddress, moveLeft);
  determineDirection(angle);  
  moveLeft = !moveLeft;
  EEPROM.put(moveLeft_eeAddress, moveLeft);
  float pause = 64;              //delay time of return speed (divide by 8 to get delay in microseconds)
  runStandardOp(pause,angle);
}

//FINISH OPERATION LOGIC
void finishOp(){   
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  stepperEnabled = false;
  runningPath = false;
  delay(500);
}

//ENABLESTEPPER LOGIC
void enableSteppers(){
  if (stepperEnabled == true){
    digitalWrite(disablePin, LOW);            //enable stepper drivers
  }
  else{
    digitalWrite(disablePin, HIGH);            //disable stepper drivers
  }
}

//JOG LOGIC
void runReset(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  stepperEnabled = true;
  EEPROM.get(moveLeft_eeAddress, moveLeft);
  
  if (moveLeft == true){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //moveright
  }
  else{
    digitalWrite(horizontalDirPin, LOW);
  }
 
  cancel = counter;                        //set cancel equal to the current counter value
  for (long i = 0; i < LENGTH;){           //this for loop controls all the actual motor controll
    
    encoder();                             //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
      runningPath = false;
    }
    digitalWrite( horizontalStepPin ,HIGH);  
    digitalWrite(horizontalStepPin , LOW); 
    delayMicroseconds(80);       
  }
  finishOp();  
}
