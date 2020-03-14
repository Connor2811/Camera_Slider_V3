//following functions controll the actual planned operation 



//OPERATION LOGIC FOR TIME CONTROLL
void timeControl(){
 
  angle = (timeControl_rDistance * 35.5552); //calculate angle from user configured values to 360degree scale
  pause =(((timeControl_seconds) * 1000000L) + (timeControl_minutes * 60000000L) + (timeControl_hours * 3600000000L))/LENGTH;       
  runningPath = true;
    determineDirection();
    runStandardOp();
    returnToStart();
    finishOp();
}

//OPERATION LOGIC FOR SPEED CONTROLL
void speedControl(){
  
  angle = (speedControl_rDistance * 35.5552); //calculate angle from user configured values to 360degree scale
  pause =(((((length_Inches/speedControl_speed)*60)) * 1000000L) )/LENGTH;
  runningPath = true;
    determineDirection();
    runStandardOp();
    returnToStart();
    finishOp();
}

//OPERATION LOGIC FOR MOTION CONTROLL
void motionControl(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  stepperEnabled = true;
  angle = 1; 
  determineDirection();

  float startAngle = atan(motionControl_dAway/motionControl_dDown)*(180/ M_PI);
  float calculatedAngle;
  float currentAngle = startAngle;
  float angleStepsTaken = 0;
  int flip = true;
  float dTravled = 0;
  int x = true;
  pause =(((motionControl_seconds) * 1000000L) + (motionControl_minutes * 60000000L) + (motionControl_hours * 3600000000L))/LENGTH;
  float myPause = (pause - ((25 * 1000000L)/LENGTH))/8;
  //pause/55;
  cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  
  for (float i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    if (dTravled < motionControl_dDown){
      
      if (( calculatedAngle - currentAngle)*4 > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
          digitalWrite(rotationStepPin, HIGH);   
          digitalWrite(horizontalStepPin,HIGH);   
          digitalWrite(rotationStepPin, LOW);   
          digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle =  calculatedAngle;
      }
      else {
        digitalWrite(horizontalStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);   
      } 
      for(long i=0; i < myPause; i++){
        delayMicroseconds(8);
      }                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
  
      dTravled = (i/2032);
      calculatedAngle = atan(motionControl_dAway/(motionControl_dDown - dTravled))*(180/ M_PI);

      
      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      runningPath = false;
      }    
    }  

    //here we are past the 90 degree point and the math needs to change, otherwise we would be calculating negatives
    else { 
      if(x == true){
        x = false;
        currentAngle = 90;
      }
      
      if ((currentAngle -  calculatedAngle) * 4 > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
          digitalWrite(rotationStepPin, HIGH);   
          digitalWrite(horizontalStepPin,HIGH);   
          digitalWrite(rotationStepPin, LOW);   
          digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle =  calculatedAngle;  
      }
      else {
        digitalWrite(horizontalStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);   
      } 
      for(long i=0; i < myPause; i++){
        delayMicroseconds(8);
      }                
  
      dTravled = (i/2032);
      calculatedAngle = atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI);

      
      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      runningPath = false;
      }   
    }
  }  
  returnToStart();
  finishOp();
}


void runReset(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  stepperEnabled = true;
  
  if (moveLeft == true){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //moveright
  }
  else{
    digitalWrite(horizontalDirPin, LOW);
  }
 
  cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  for (long i = 0; i < LENGTH;){           //this for loop controls all the actual motor controll
    
  encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
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

void enableSteppers(){
  if (stepperEnabled == true){
    digitalWrite(disablePin, HIGH);            //enable stepper drivers
  }

  else{
    digitalWrite(disablePin, LOW);            //enable stepper drivers
  }
}



void returnToStart(){
    //reverse movement and reset to original location

  moveLeft = !moveLeft;
  determineDirection();  
  moveLeft = !moveLeft;
  pause = 64;              //delay time of return speed (divide by 8 to get delay in microseconds)
  runStandardOp();
}

void runStandardOp(){
  if (runningPath == true){
    digitalWrite(disablePin, LOW);               //enable stepper drivers
    stepperEnabled = true;
    cancel = counter;                            //set cancel equal to the current counter value
    delay (1000);                                //wait a sec to debounce
    angleTracking = 1;
    float myAngle = LENGTH/angle;
    float myPause = pause/14;
    
    for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
      encoder();                                 //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
        i = LENGTH;
        runningPath = false;
      }
  
     if ( i  > angleTracking * myAngle) {       //step the camera angle motor a percentage of the time so it goes a percent of the total distace
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

void determineDirection(){
    if (moveLeft == true){
      digitalWrite(horizontalDirPin, LOW);
      digitalWrite(rotationlDirPin, HIGH);
      if (angle < 0){
        angle = abs(angle);
        digitalWrite(rotationlDirPin, LOW);
      }
    } 
    else { //check desired camera direction and flip the horizontal and rotation direction if needed
      digitalWrite(horizontalDirPin, HIGH);  //moveright
      digitalWrite(rotationlDirPin, LOW);   //move anticlockwise
      if (angle < 0){       //rotate camera opposite direction if degree value is negative
        digitalWrite(rotationlDirPin, HIGH);
        angle = abs(angle);
      }
    }    
}


void finishOp(){
    
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  stepperEnabled = false;
  runningPath = false;
  delay(500);
}
