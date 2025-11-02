const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int ldrPin = A2;

const int bip=255;
const int rip=22;
const int gip=119;

int Tred, Tgreen, Tblue;


void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Step 1: Get LDR values for full brightness of each LED
  analogWrite(redPin, rip);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(500);
  Tred = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, gip);
  analogWrite(bluePin, 0);
  delay(500);
  Tgreen = analogRead(ldrPin);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, bip);
  delay(500);
  Tblue = analogRead(ldrPin);

  analogWrite(redPin, rip);
  analogWrite(greenPin, gip);
  analogWrite(bluePin, bip);
  delay(500);
  // Step 2: Find maximum brightness
  Serial.print("Tred : ");Serial.println(Tred);
  Serial.print("Tgreen : ");Serial.println(Tgreen);
  Serial.print("Tblue : ");Serial.println(Tblue);

  
  int flag=0;
  if(abs(Tred-Tblue)<30 && abs(Tblue-Tgreen)<30 && abs(Tred-Tgreen)<30){
    int avg = (Tred+Tgreen+Tblue)/3;
    if(avg<260){  
      Serial.println("White Colour");
    }
    Serial.println("Black Colour");
    flag=1;
  }
  
  if(flag==0){
  
  int Tmin = min(Tred, min(Tgreen, Tblue));
  // Step 3: Calibrate Red
  if (Tred == Tmin) {
    Serial.print("Red Colour");
  }

  // Step 4: Calibrate Green
  if (Tblue == Tmin) {
    Serial.print("Blue Colour");
  }
  if (Tgreen == Tmin) {
    Serial.print("Green Colour");
  }

  }

  

  
}

void loop() {
  // Optional: apply calibrated values to display white-balanced light
  
}