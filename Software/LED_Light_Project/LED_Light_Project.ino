
#define FLASH_RATE_HZ 2
#define BUTTON_IN 8
#define PWM_LED_OUT 11

// operating mode: 0-off, 1-bright, 2-mid-bright, 3-dim, 4-flashing
int operating_mode = 0;
int button_state = 0;
int previous_button_state  = 0;
int PWM_OUT = 0;
int light_flash_state = 0;
unsigned long currentmillis = 0;
unsigned long prevmillis = 0;
long interval = 0;
int ledState = LOW;

void setup() {
  attachInterrupt(BUTTON_IN, button_pushed, FALLING);
  // Define output pin for LED

}

void loop() {
check_for_button_press();

// Create a function here which changes the operating mode

switch(operating_mode) {
  case 0:
    PWM_OUT = 0;
  case 1:
    PWM_OUT = 255;
  case 2:
    PWM_OUT = 128;
  case 3:
    PWM_OUT = 64;
  case 4:
    flash_the_light();
}
  if (operating_mode != 4 ) {
    shine_LED(PWM_OUT);
  }

}

void check_for_button_press() {
  //Updates the operating mode (and resets the button interrupt) in response to a button press
  if (button_state == 1) {
      if (operating_mode == 4) {
        operating_mode = 0;
      }
      else {
        operating_mode = operating_mode + 1;
      }

    button_state = 0;
  }

  
// set operating mode
// reset previous button mode state
}

void button_pushed() {
  //Interrupt command that sets the button state to 1 to indicate that it was pressed
  button_state = 1;
}

void shine_LED(int PWM_OUT) {
  //Write to the digital output pin related to the given PWM value
  digitalWrite(PWM_LED_OUT, PWM_OUT);
}

void flash_the_light(){
  //Calculate the how rapidly the light should flash based upon the specified frequency
  interval = 1000/(FLASH_RATE_HZ * 2);
  currentmillis = millis();

  if(currentmillis - prevmillis >= interval) {
    prevmillis = currentmillis;
  }
  if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(PWM_LED_OUT,ledState);


}
