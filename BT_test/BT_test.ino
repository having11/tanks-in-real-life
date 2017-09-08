int JS_VALS[2] = {};

const int button_pin = 2;
const int deadzone = 8;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(button_pin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(button_pin), fire_laser, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  JS_VALS[0] = analogRead(A1);
  JS_VALS[1] = analogRead(A2);
  int x = map(JS_VALS[0], 0, 1023, -50, 50);
  x = constrain(x, -100, 100);
  int y = map(JS_VALS[1], 0, 1023, -50, 50);
  y = constrain(y, -100, 100);
  int motor1 = x+y;
  int motor2 = y-x;
  motor1 = constrain(motor1, -100, 100);
  motor2 = constrain(motor2, -100, 100);
  if(abs(motor1) <= deadzone){
    motor1 = 0;
  }
  if(abs(motor2) <= deadzone){
    motor2 = 0;
  }
  //Serial.println("X: "+String(JS_VALS[0])+", Y: "+String(JS_VALS[1]));
  String json_string = "{\"motor\":[" + String(motor1)+","+String(motor2)+"]}";
  Serial.println(json_string);
  delay(30);
}

void fire_laser(){
  String json_string = "{\"shoot\":\"1\"}";
  Serial.println(json_string);
}

