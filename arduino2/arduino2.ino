// ***JOYSTICK***
 int VRx = A0;
 int VRy = A1;
 int SW = 11;

 int xPosition = 0;
 int yPosition = 0;
 int SW_state = 0;
 int mapX = 0;
 int mapY = 0;

//***MAGNETIC HALL  SENSOR***
//int Hall_Sensor = A0                  *****NO NEED FOR NOW*****
 int Hall_Sensor_D = 5;
 int tiltValue=0,magnetValue=0; 

//***TILT SENSOR***
 int tiltsensor = 3;

//***ULTRASONIC SENSOR***
 const int trigPin = 8;
 const int echoPin = 9;
 long duration;
 int distance;

 
void setup() {
  Serial.begin(9600); 

// ***JOYSTICK***
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

//***MAGNETIC HALL  SENSOR*** 
  pinMode(Hall_Sensor_D,INPUT); 

//***TILT SENSOR***
  pinMode(tiltsensor, INPUT);

//***ULTRASONIC SENSOR***
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  
xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);


    // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

}

void loop() {


    Read_and_print_sensors ();

 
  if (mapX>30 && mapX<300 && mapY >0 && SW_state == 1){
      Serial.println("JOYSTICK COMPLETE!!!");
  }
  
  if(distance>15 && distance<20){
  Serial.println("ULTRASONIC COMPLETE!!!");
  }

} // end void loop


void Read_and_print_sensors (){

    magnetValue=digitalRead(Hall_Sensor_D);             
    Serial.print("megnetic hall sensor: ");
    Serial.print(magnetValue);

    tiltValue=digitalRead(tiltsensor);
    Serial.print("||tilt sensor: ");
    Serial.print(tiltValue);

    
    Read_ultra_sonic ();
    Read_joystick ();


}

void Read_ultra_sonic (){

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("||Distance: ");
  Serial.print(distance);
}

void Read_joystick (){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("|X: ");
  Serial.print(mapX);
  Serial.print("|Y: ");
  Serial.print(mapY);
  Serial.print("|SW: ");
  Serial.println(SW_state);
}
