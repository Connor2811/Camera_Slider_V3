//following functions controll the actual planned operation 



//OPERATION LOGIC FOR TIME CONTROLL
void timeControl(){
  
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == "  right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //moveright
    digitalWrite(rotationlDirPin, HIGH);   //move anticlockwise
    if (timeControl_rDistance < 0){       //rotate camera opposite direction if degree value is negative
      digitalWrite(rotationlDirPin, LOW);
    }
  }
    
    if (movementDirection == "  left "){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, LOW);
    if (timeControl_rDistance < 0){
      digitalWrite(rotationlDirPin, HIGH);
   }
  }

  angle = (timeControl_rDistance * 35.5552); //calculate angle from user configured values to 360degree scale
  unsigned long pause =(((timeControl_seconds - 3) * 1000000L) + (timeControl_minutes * 60000000L) + (timeControl_hours * 3600000000L))/LENGTH;       
  cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce

  angleTracking = 1;
  for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    
    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
    }
    
   if ( i  > angleTracking*(LENGTH/angle)) {            //step the camera angle motor a percentage of the time so it goes a percent of the total distace
     digitalWrite(rotationStepPin, HIGH); 
     digitalWrite(horizontalStepPin,HIGH);
     digitalWrite(horizontalStepPin, LOW);  
      digitalWrite(rotationStepPin, LOW);
      angleTracking ++; 
    }
    else { 
      digitalWrite( horizontalStepPin ,HIGH);  
      digitalWrite(horizontalStepPin , LOW);    
    }
    for(long i=0; i < pause/8; i++){
      delayMicroseconds(8);
    }    
  }
  returnToStart();
    
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
  delay(500);
}

//OPERATION LOGIC FOR SPEED CONTROLL
void speedControl(){
  
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == "  right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //move right
    digitalWrite(rotationlDirPin, HIGH);   //move anticlockwise
    if (speedControl_rDistance < 0){       //rotate camera opposite direction if degree value is negative
      digitalWrite(rotationlDirPin, LOW);
    }
  }
    
    if (movementDirection == "  left "){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, LOW);
    if (speedControl_rDistance < 0){
      digitalWrite(rotationlDirPin, HIGH);
   }
  }

  //inches per minute to steps per microsecond
  angle = (speedControl_rDistance * 35.5552); //calculate angle from user configured values to 360degree scale
  float pause =(((((length_Inches/speedControl_speed)*60)) * 1000000L) )/LENGTH;

  cancel = counter;                                                  //set cancel equal to the current counter value
  delay (1000);                                                          //wait a sec to debounce
  
  angleTracking = 1;
  for (long i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    
    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
    }
    
   if ( i  > angleTracking*(LENGTH/angle)) {            //step the camera angle motor a percentage of the time so it goes a percent of the total distace
     digitalWrite(rotationStepPin, HIGH); 
     digitalWrite(horizontalStepPin,HIGH);
     digitalWrite(horizontalStepPin, LOW);  
      digitalWrite(rotationStepPin, LOW);
      angleTracking ++; 
    }
    else { 
      digitalWrite( horizontalStepPin ,HIGH);  
      digitalWrite(horizontalStepPin , LOW); 
     }
     
    for(long i=0; i < pause/8; i++){
      delayMicroseconds(8);
    }
    
  } 

  returnToStart();
  
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
  delay(500);
}




//OPERATION LOGIC FOR MOTION CONTROLL
void motionControl(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == "  right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, HIGH);  //move right
    digitalWrite(rotationlDirPin, LOW);   //move anticlockwise
  }
    
    if (movementDirection == "  left "){
    digitalWrite(horizontalDirPin, LOW);
    digitalWrite(rotationlDirPin, HIGH);
  }

  float startAngle = atan(motionControl_dAway/motionControl_dDown)*(180/ M_PI);
  float calculatedAngle;
  float currentAngle = startAngle;
  float angleStepsTaken = 0;
  int flip = true;
  float dTravled = 0;
  int x = true;
 float pause =(((((length_Inches/speedControl_speed)*60)) * 1000000L) )/LENGTH;
  cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  
  for (float i = 0; i < LENGTH; i++){           //this for loop controls all the actual motor controll
    if (dTravled < motionControl_dDown){
     // Serial.println(currentAngle );
      //Serial.println(calculatedAngle);
     // Serial.println(calculatedAngle - currentAngle);
      
    //  Serial.println("");
      
      if (((atan(motionControl_dAway/(motionControl_dDown - dTravled))*(180/ M_PI))- currentAngle)*4 > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
        //for(i=0; i<4,i++){
        digitalWrite(rotationStepPin, HIGH);
        digitalWrite(horizontalStepPin,HIGH);
        digitalWrite(rotationStepPin, LOW);
        digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle = atan(motionControl_dAway/(motionControl_dDown - dTravled))*(180/ M_PI);
        //}   
      }
      else {
        digitalWrite(horizontalStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);   
      } 
      for(long i=0; i < pause/8; i++){
        delayMicroseconds(8);
      }                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
  
      dTravled = (i/2032);
      calculatedAngle = atan(motionControl_dAway/(motionControl_dDown - dTravled))*(180/ M_PI);

      
      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      }    
    }  

    //here we are past the 90 degree point and the math needs to change, otherwise we would be calculating negatives
    else { 
      if(x == true){
        x = false;
        currentAngle = 90;
      }
       
     // Serial.println(atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI));//after the camera has reached 90 degrees to the object the angles are flipped 
      //Serial.println(calculatedAngle);//after the camera has reached 90 degrees to the object the angles are flipped
       
     // Serial.println(" ");//after the camera has reached 90 degrees to the object the angles are flipped 

      
      if ((currentAngle - (atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI)))*4 > .1125){   //if the angle diffrence between the ideal current degree and the actual degree is greator than the size of a single step, than take a step.
        //for(i=0; i<4,i++){
        digitalWrite(rotationStepPin, HIGH);
        digitalWrite(horizontalStepPin,HIGH);
        digitalWrite(rotationStepPin, LOW);
        digitalWrite(horizontalStepPin, LOW);
        angleStepsTaken ++;
        currentAngle = atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI);
        //}   
      }
      else {
        digitalWrite(horizontalStepPin, HIGH);
        digitalWrite(horizontalStepPin, LOW);   
      } 
      for(long i=0; i < pause/8; i++){
        delayMicroseconds(8);
      }                //velocity delay controls how fast the camera moves, small value is fast and large value is slow
  
      dTravled = (i/2032);
      calculatedAngle = atan(motionControl_dAway/(dTravled - motionControl_dDown))*(180/ M_PI);

      
      encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
      if (cancel != counter){
      i = LENGTH;
      }

          
    }
  }  

  returnToStart();
  
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
}


void runReset(){
  runningPath = true;                       //tell they system we are running an operation
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  
  if (movementDirection == "  right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, LOW);  //moveright
  }
    
    if (movementDirection == "  left "){
    digitalWrite(horizontalDirPin, HIGH);
  }
 
  cancel = counter;                        //set cancel equal to the current counter value
  delay (1000);                                //wait a sec to debounce
  for (long i = 0; i < LENGTH;){           //this for loop controls all the actual motor controll
    
    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
    }
      digitalWrite( horizontalStepPin ,HIGH);  
      digitalWrite(horizontalStepPin , LOW); 
      delayMicroseconds(80);       
  }
  digitalWrite(disablePin, HIGH);    //turn everything off and set the running path to false.
  runningPath = false;
  delay(500);
}





void enableSteppers(){
  if (stepperState == " disabled"){
  digitalWrite(disablePin, HIGH);            //enable stepper drivers
  }

    if (stepperState == " enabled "){
  digitalWrite(disablePin, LOW);            //enable stepper drivers
  }
}



void returnToStart(){
    //reverse movement and reset to original location
    if (movementDirection == "  right"){ //check desired camera direction and flip the horizontal and rotation direction if needed
    digitalWrite(horizontalDirPin, LOW);  //moveright
    digitalWrite(rotationlDirPin, LOW);   //move anticlockwise
    if (timeControl_rDistance < 0){       //rotate camera opposite direction if degree value is negative
      digitalWrite(rotationlDirPin, HIGH);
    }
  }
    
    if (movementDirection == "  left "){
    digitalWrite(horizontalDirPin, HIGH);
    digitalWrite(rotationlDirPin, HIGH);
    if (timeControl_rDistance < 0){
      digitalWrite(rotationlDirPin, LOW);
   }
  }
  angleTracking = 1;
  for (long i = 0; i < LENGTH; i++){
        
    encoder();                                  //check if the encoder has changed direction and if it has exit the for loop
    if (cancel != counter){
      i = LENGTH;
    }
    
   if ( i  > angleTracking*(LENGTH/angle)) {            //step the camera angle motor a percentage of the time so it goes a percent of the total distace
     digitalWrite(rotationStepPin, HIGH); 
     digitalWrite(horizontalStepPin,HIGH);
     digitalWrite(horizontalStepPin, LOW);  
      digitalWrite(rotationStepPin, LOW);
      angleTracking ++; 
    }
    else { 
      digitalWrite( horizontalStepPin ,HIGH);  
      digitalWrite(horizontalStepPin , LOW);    
    }  
      delayMicroseconds(50);
  }
}
