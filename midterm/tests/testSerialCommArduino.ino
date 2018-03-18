int led = 1;
char serialData;

void setup() {

  Serial.begin(9600);       
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
}

void loop() {

  if (Serial.available()) {
    serialData = Serial.read();
    
    // turn off current light and turn on next light
    if (serialData == '1') {
      digitalWrite(led, LOW);
      led++;      
      led = led > 7 ? 2 : led;
      digitalWrite(led, HIGH);
    }
  }

  
}
