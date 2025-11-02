const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int ldrPin = A2;

int Tred, Tgreen, Tblue;
int Rcal, Gcal, Bcal;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Step 1: Get LDR values for full brightness of each LED
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
        Rcal = i;
        break;
      }
    }
  } else {
    Rcal = 255;
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
        Gcal = i;
        break;
      }
    }
  } else {
    Gcal = 255;
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
        Bcal = i;
        break;
      }
    }
  } else {
    Bcal = 255;
  }

  // Print Calibrated Values
  Serial.println("Calibrated PWM values:");
  Serial.print("Red: "); Serial.println(Rcal);
  Serial.print("Green: "); Serial.println(Gcal);
  Serial.print("Blue: "); Serial.println(Bcal);
}

void loop() {
  // Optional: apply calibrated values to display white-balanced light
  analogWrite(redPin, Rcal);
  analogWrite(greenPin, Gcal);
  analogWrite(bluePin, Bcal);
}