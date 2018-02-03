// Declare pin variables
const int red_led_1 = 5;
const int red_led_2 = 4;
const int green_led_1 = 3;
const int button = 2;

int switchState = 0;

void setup() {

  pinMode(red_led_1, OUTPUT);
  pinMode(red_led_2, OUTPUT);
  pinMode(green_led_1, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  switchState = digitalRead(button);

  // Light up Green, dim Red LEDs when button is pressed
  if (switchState == HIGH) {
    digitalWrite(green_led_1, HIGH);
    digitalWrite(red_led_1, LOW);
    digitalWrite(red_led_2, LOW);
  } else {
    // Toggle Red LEDs
    digitalWrite(green_led_1, LOW);
    digitalWrite(red_led_1, HIGH);
    digitalWrite(red_led_2, LOW);

    delay(250);
    digitalWrite(red_led_1, LOW);
    digitalWrite(red_led_2, HIGH);
    delay(250);
  }
}
