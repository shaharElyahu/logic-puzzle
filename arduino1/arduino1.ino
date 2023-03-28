int ENB = 3;
int in1 = 4;
int in2 = 5;
int ENB2 = 8;
int in12 = 7;
int in22 = 6;
int digitalPin = 2;
int analogPin = A0;
int digitalVal; // digital readings
int analogVal; //analog readings

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(ENB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  pinMode(ENB2, OUTPUT);
  pinMode(in12, OUTPUT);
  pinMode(in22, OUTPUT);

  digitalWrite(ENB2, LOW);
  digitalWrite(in12, LOW);
  digitalWrite(in22, LOW);

  pinMode(analogPin, INPUT);
  Serial.begin(9600);


  digitalWrite(in12, HIGH);
  digitalWrite(in22, LOW);
  analogWrite(ENB2, 255);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

}

void loop() {

  // digitalVal = digitalRead(digitalPin);
  analogVal = analogRead(A0);

  Serial.println(analogVal); // print analog value to serial


  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(A0);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(1);        // delay in between reads for stability

  if (analogVal < 200) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ENB, 255);

    analogVal = analogRead(analogPin);

    Serial.println(analogVal); // print analog value to serial

  }

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ENB, 0);

}
