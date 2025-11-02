const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int ldrPin = A2;

int Tred, Tgreen, Tblue;

int mode = -1;
int Tmax = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

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

  Tmax= max( max(Tred,Tblue),Tgreen );

  Serial.print("Tred : ");Serial.println(Tred);
  Serial.print("Tgreen : ");Serial.println(Tgreen);
  Serial.print("Tblue : ");Serial.println(Tblue);
  Serial.print("Tmax : ");Serial.println(Tmax);


  

  Serial.println("Calibration Started...");
  Serial.println("Enter:");
  Serial.println("1 - Calibrate RED");
  Serial.println("2 - Calibrate GREEN");
  Serial.println("3 - Calibrate BLUE");
  Serial.println("0 - Exit Calibration");
}

void loop() {
  
}
