#include <Servo.h> 
Servo leftWheel;
Servo rightWheel;
int led = 7;  // pin 7 connected to LED
int led_flag = 0;
byte inputByte = 0; // this will be a byte recieved via bluetooth
int lw_pin = 9;
int rw_pin = 10;
int moveSpd = 50; // movement speed

void setup() {
  Serial.begin(9600); // default baud rate
  leftWheel.attach(lw_pin);
  rightWheel.attach(rw_pin);
  pinMode(led,OUTPUT);  // for toggling LED
}

void loop() {
  leftWheel.write(90);
  rightWheel.write(90);
  while(Serial.available()>0){
    inputByte= Serial.read();
    Serial.println(inputByte);
    if (inputByte == 1){            // go forward
      leftWheel.write(90+moveSpd);
      rightWheel.write(90-moveSpd);
      waitForButtonRelease();
      leftWheel.write(90);
      rightWheel.write(90);
    }
    else if (inputByte == 2){       // reverse
      leftWheel.write(90-moveSpd);
      rightWheel.write(90+moveSpd);
      waitForButtonRelease();
      leftWheel.write(90);
      rightWheel.write(90);
    }
    else if (inputByte == 3){       // turn left
      leftWheel.write(90-moveSpd);
      rightWheel.write(90-moveSpd);
      waitForButtonRelease();
      leftWheel.write(90);
      rightWheel.write(90);
    }
    else if (inputByte == 4){       // turn right
      leftWheel.write(90+moveSpd);
      rightWheel.write(90+moveSpd);
      waitForButtonRelease();
      leftWheel.write(90);
      rightWheel.write(90);
    } 
    else if (inputByte == 5){       // toggle lights
      led_flag = toggleLights(led,led_flag);
    }
  }
} // end loop()

void waitForButtonRelease(){
  while(Serial.available() < 1){
    delay(100);
  }
}

int toggleLights(int led, int led_flag){
  if(led_flag == 0){    // turn on LED
    digitalWrite(led,HIGH);
    led_flag = 1;
  }
  else{                 // turn off LED
    digitalWrite(led,LOW);
    led_flag = 0;    
  }
  return led_flag;
}
