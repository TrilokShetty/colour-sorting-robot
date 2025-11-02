#include <Servo.h>
Servo myservo;

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int ldrPin = A2;

int Tred, Tgreen, Tblue;
int mode = -1;
bool running = true;

int bip = 255;
int rip = 22;
int gip = 119;

int RCal,Gcal,Bcal;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  mainMenu();
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    
    if (input == '1') {
      manualCalibrate();
    }
    else if (input == '2') {
      autoCalibrate();
    }
    else if (input == '3') {
      colourSensing();
    }
        else if (input == '4') {
      pickAndDrop();
    }
    else if (input == '0') {
      Serial.println("Exiting...");
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);

      mainMenu();
    }


  }
}

void mainMenu() {
  Serial.println("\nWelcome to Mechatronics Project Group 24");
  Serial.println("What do you want to do?");
  Serial.println("1. Manual Calibrate");
  Serial.println("2. Auto Calibrate");
  Serial.println("3. Colour Sensing");
  Serial.println("4. Pick Up and Drop");
  Serial.println("0. Exit");
}

void manualCalibrate() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(500);
  Tred = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  delay(500);
  Tgreen = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  delay(500);
  Tblue = analogRead(ldrPin);

  int Tmax= max( max(Tred,Tblue),Tgreen );

  Serial.print("Tred : ");Serial.println(Tred);
  Serial.print("Tgreen : ");Serial.println(Tgreen);
  Serial.print("Tblue : ");Serial.println(Tblue);
  Serial.print("Tmax : ");Serial.println(Tmax);

  Serial.println("Manual Calibration Started...");
  Serial.println("Enter:");
  Serial.println("1 - Calibrate RED");
  Serial.println("2 - Calibrate GREEN");
  Serial.println("3 - Calibrate BLUE");
  Serial.println("4 - Exit Calibration");
  
  

  while (true) {
    if (Serial.available()) {
    char input = Serial.read();
    Tmax = 0;

    if (input == '1') {
      Serial.println("Red LED ON - Calibrate using pot. Press 0 to exit.");
      mode = 1;
    }
    else if (input == '2') {
      Serial.println("Green LED ON - Calibrate using pot. Press 0 to exit.");
      mode = 2;
    }
    else if (input == '3') {
      Serial.println("Blue LED ON - Calibrate using pot. Press 0 to exit.");
      mode = 3;
    }
    else if (input == '4') {
      mode = 4;
      Serial.println("Calibration Completed.");
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);

      mainMenu();

    }
    else if(input== '0'){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);

      mode=0;
      return;
    }
  }

  if (mode == 1 || mode == 2 || mode == 3) {
    // Set LED based on mode
    if (mode == 1) {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }
    else if (mode == 2) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
    }
    else if (mode == 3) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
    }

    int ldrVal = analogRead(ldrPin);
    if (ldrVal > Tmax) {
      Tmax = ldrVal;
    }

    Serial.print("LDR: ");
    Serial.print(ldrVal);
    Serial.print(" | Tblue: ");
    Serial.println(Tblue);

    delay(100);
  }
  }

  gip=255;
  rip=255;
  bip=255;

  
}

void autoCalibrate() {

  while (Serial.available()) Serial.read();
  Serial.println("Auto Calibration Started...");

  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(5000);
  Tred = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
  delay(5000);
  Tgreen = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  delay(5000);
  Tblue = analogRead(ldrPin);

  // Step 2: Find maximum brightness
  int Tmax = max(Tred, max(Tgreen, Tblue));
  Serial.print("Maximum : ");Serial.println(Tmax);
  Serial.print("Tred : ");Serial.println(Tred);
  Serial.print("Tgreen : ");Serial.println(Tgreen);
  Serial.print("Tblue : ");Serial.println(Tblue);
  // Step 3: Calibrate Red
  if (Tred < Tmax) {
    for (int i = 255; i >= 0; i--) {
      analogWrite(redPin, i);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      delay(100);
      int val = analogRead(ldrPin);
      if (abs(val - Tmax) < 5) {
        rip = i;
        break;
      }
    }
  } else {
    rip = 255;
  }

  // Step 4: Calibrate Green
  if (Tgreen < Tmax) {
    for (int i = 255; i >= 0; i--) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, i);
      analogWrite(bluePin, 0);

      delay(100);
      int val = analogRead(ldrPin);
      if (abs(val - Tmax) < 5) {
        gip = i;
        break;
      }
    }
  } else {
    gip = 255;
  }

  // Step 5: Calibrate Blue
  if (Tblue < Tmax) {
    for (int i = 255; i >= 0; i--) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, i);
      delay(100);
      int val = analogRead(ldrPin);
      if (abs(val - Tmax) < 5) {
        bip = i;
        break;
      }
    }
  } else {
    bip = 255;
  }

  // Print Calibrated Values
  Serial.println("Calibrated PWM values:");
  Serial.print("Red: "); Serial.println(rip);
  Serial.print("Green: "); Serial.println(gip);
  Serial.print("Blue: "); Serial.println(bip);


  Serial.println("Auto Calibration Completed.");
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
    Serial.println("Press any key to return to main menu...");

    // Wait for any key press before returning
    while (!Serial.available()) {
      // Wait
    }
    Serial.read(); 


  
}

void colourSensing() {
  int mode = 0;

  Serial.println("Enter 1 if Auto Calibration done, else 2 for Manual Mode:");
  while (mode != 1 && mode != 2) {
    while (!Serial.available()); // Wait for user input
    mode = Serial.parseInt();
    Serial.read();
  }

  if (mode == 1) {
    Serial.println("Enter Red shining intensity (0-255): ");
    while (!Serial.available());
    rip = Serial.parseInt();
    Serial.println(rip);
    Serial.read();

    Serial.println("Enter Green shining intensity (0-255): ");
    while (!Serial.available());
    gip = Serial.parseInt();
    Serial.println(gip);
    Serial.read();

    Serial.println("Enter Blue shining intensity (0-255): ");
    while (!Serial.available());
    bip = Serial.parseInt();
    Serial.println(bip);
    Serial.read();

  } else {
    rip = 255;
    gip = 255;
    bip = 255;
  }

  Serial.print("Red: "); Serial.println(rip);
  Serial.print("Green: "); Serial.println(gip);
  Serial.print("Blue: "); Serial.println(bip);


  analogWrite(redPin, rip);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(2000);
  Tred = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, gip);
  analogWrite(bluePin, 0);
  delay(2000);
  Tgreen = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, bip);
  delay(2000);
  Tblue = analogRead(ldrPin);

  Serial.print("Tred: ");
  Serial.println(Tred);
  Serial.print("Tgreen: ");
  Serial.println(Tgreen);
  Serial.print("Tblue: ");
  Serial.println(Tblue);

  int avg = (Tred + Tgreen + Tblue) / 3;

  if (abs(Tred - Tgreen) < 35 && abs(Tgreen - Tblue) < 35 && abs(Tred - Tblue) < 35) {
    if (avg < 260) {
      Serial.println("White Colour");
    } else {
      Serial.println("Black Colour");
    }
  } else {
    int Tmin = min(Tred, min(Tgreen, Tblue));
    if (Tred == Tmin) {
      Serial.println("Red Colour");
    } else if (Tgreen == Tmin) {
      Serial.println("Green Colour");
    } else if (Tblue == Tmin) {
      Serial.println("Blue Colour");
    }
  }

  // analogWrite(redPin, rip);
  // analogWrite(greenPin, gip);
  // analogWrite(bluePin, bip);
  delay(1000);
  analogWrite(redPin, rip);
  analogWrite(greenPin, gip);
  analogWrite(bluePin, bip);
  gip=0;
  rip=0;
  bip=0;
}




void pickAndDrop() {
  Serial.println("Pick and Drop Mode");
  Serial.println("Enter Pickup Location (1-Red, 2-Green, 3-Blue, 4-White, 5-Black):");

  int pickupCode = 0;
  while (pickupCode == 0) {
    while (Serial.available()) {
      // Wait for input
      pickupCode = Serial.parseInt(); 
      Serial.read();
    }
    
  }
  Serial.print("Pickup Code Entered: ");
    Serial.println(pickupCode);  

  Serial.println("Enter Drop Location (1-Red, 2-Green, 3-Blue, 4-White, 5-Black):");
  int dropCode = 0;
  while (dropCode == 0) {
    while (Serial.available()) {
      // Wait for input
      dropCode = Serial.parseInt(); 
      Serial.read();
    }
    
  }
  Serial.print("Drop Code Entered: ");
  Serial.println(dropCode);  


  

  const char* colors[] = {"Invalid", "Red", "Green", "Blue", "White", "Black"};

  myservo.attach(5);  // Attach servo to pin 5 (adjust as needed)

  gip = 255; rip = 255; bip = 255;  // Set LED color values

  for (int angle = 0; angle <= 180; angle += 5) {
    myservo.write(angle);
    delay(1000);

    analogWrite(redPin, rip);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(1000);
    int tempRed = analogRead(ldrPin);

    analogWrite(redPin, 0);
    analogWrite(greenPin, gip);
    analogWrite(bluePin, 0);
    delay(1000);
    int tempGreen = analogRead(ldrPin);

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, bip);
    delay(1000);
    int tempBlue = analogRead(ldrPin);

    Serial.print("Tred: ");
    Serial.println(tempRed);
    Serial.print("Tgreen: ");
    Serial.println(tempGreen);
    Serial.print("Tblue: ");
    Serial.println(tempBlue);

    int avg = (tempRed + tempGreen + tempBlue) / 3;

    int detectedCode = 0;

    // Detect color based on LDR readings
    if (abs(tempRed - tempGreen) < 25 && abs(tempGreen - tempBlue) < 25 && abs(tempRed - tempBlue) < 25) {
      if (avg < 260)
        detectedCode = 4;  // White
      else
        detectedCode = 5;  // Black
    } else {
      int Tmin = min(tempRed, min(tempGreen, tempBlue));
      if (tempRed == Tmin) detectedCode = 1;
      else if (tempGreen == Tmin) detectedCode = 2;
      else if (tempBlue == Tmin) detectedCode = 3;
    }

    Serial.print("Detected Code: ");
    Serial.println(detectedCode);
    Serial.print("Pickup Code: ");
    Serial.println(pickupCode);

    if (detectedCode == pickupCode) {
      Serial.print("Pickup Location Detected: ");
      Serial.println(colors[pickupCode]);
      // pickObject();
      break;  // Exit the loop if pickup location is detected
    }
  }

  // Moving the servo back and checking drop location
  for (int angle = 180; angle >= 0; angle -= 5) {
    myservo.write(angle);
    delay(500);

    analogWrite(redPin, rip);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(500);
    int tempRed = analogRead(ldrPin);

    analogWrite(redPin, 0);
    analogWrite(greenPin, gip);
    analogWrite(bluePin, 0);
    delay(500);
    int tempGreen = analogRead(ldrPin);

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, bip);
    delay(500);
    int tempBlue = analogRead(ldrPin);

    int avg = (tempRed + tempGreen + tempBlue) / 3;

    int detectedCode = 0;

    // Detect color based on LDR readings
    if (abs(tempRed - tempGreen) < 40 && abs(tempGreen - tempBlue) < 40 && abs(tempRed - tempBlue) < 40) {
      if (avg < 260)
        detectedCode = 4;  // White
      else
        detectedCode = 5;  // Black
    } else {
      int Tmin = min(tempRed, min(tempGreen, tempBlue));
      if (tempRed == Tmin) detectedCode = 1;
      else if (tempGreen == Tmin) detectedCode = 2;
      else if (tempBlue == Tmin) detectedCode = 3;
    }

    if (detectedCode == dropCode) {
      Serial.print("Drop Location Detected: ");
      Serial.println(colors[dropCode]);
      // dropObject();
      break;  // Exit the loop if drop location is detected
    }
  }

  // Final cleanup
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  myservo.detach();
  Serial.println("Pick and Drop Complete.");
  Serial.println("Press any key to return to main menu...");
  while (!Serial.available());
  Serial.read();  // Wait for any key to return
}


void pickObject() {
  const int pickupServoPin = 6;
  const int objectSensorPin = 7;  // Change based on your wiring
  Servo pickupServo;

  pinMode(objectSensorPin, INPUT);
  pickupServo.attach(pickupServoPin);

  Serial.println("Rotating arm to pick the object...");
  for (int angle = 0; angle <= 90; angle += 5) {
    pickupServo.write(angle);
    delay(100);
  }

  Serial.println("Waiting for object detection...");
  while (digitalRead(objectSensorPin) == HIGH) {  // Change to LOW if your sensor logic is reversed
    delay(100);
  }

  Serial.println("Object detected and picked!");

  Serial.println("Retracting arm...");
  for (int angle = 90; angle >= 0; angle -= 5) {
    pickupServo.write(angle);
    delay(100);
  }

  pickupServo.detach();
}


void dropObject() {
  const int pickupServoPin = 6;
  Servo pickupServo;
  pickupServo.attach(pickupServoPin);

  Serial.println("Placing object...");
  for (int angle = 0; angle <= 90; angle += 5) {
    pickupServo.write(angle);
    delay(100);
  }

  delay(1000);  // Let it rest at the place

  Serial.println("Retracting after placing...");
  for (int angle = 90; angle >= 0; angle -= 5) {
    pickupServo.write(angle);
    delay(100);
  }

  pickupServo.detach();
  Serial.println("Object placed at drop location.");
}



