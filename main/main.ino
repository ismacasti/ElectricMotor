#define LEFT_RELAY A4
#define RIGHT_RELAY A3
#define POWER_RELAY A5
#define STATUS_LED 13
#define SPEED_BUTTON 2
#define DIRECTION_BUTTON 3

int state = 0;
int motor_direction = 0;

unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long currentMillis = 0;

bool previous_speed_button = false;
bool previous_direction_button = false;

bool current_speed_button = false;
bool current_direction_button = false;


void turn_motor(bool level) {
  digitalWrite(POWER_RELAY, level);
  digitalWrite(STATUS_LED, level);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_RELAY, OUTPUT);
  pinMode(RIGHT_RELAY, OUTPUT);
  pinMode(POWER_RELAY, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(SPEED_BUTTON, INPUT);
  pinMode(DIRECTION_BUTTON, INPUT);

  state = 0;
  motor_direction = 0;
  digitalWrite(LEFT_RELAY, LOW);
  digitalWrite(RIGHT_RELAY, LOW);
  turn_motor(HIGH);
  Serial.begin(9600);
}

void loop() {
  currentMillis = millis();
  //read buttons
  current_speed_button = digitalRead(SPEED_BUTTON);
  current_direction_button = digitalRead(DIRECTION_BUTTON);
  //Serial.println(current_direction_button);
  if (current_speed_button != previous_speed_button && current_speed_button == HIGH) {
    state = (state + 1) % 4;
    Serial.print("State: ");
    Serial.println(state);
  }

  if (current_direction_button != previous_direction_button && current_direction_button == HIGH) {
    motor_direction = (motor_direction + 1) % 2;
    turn_motor(LOW);
    Serial.print("Direction: ");
    Serial.println(motor_direction);
    if (motor_direction == 0) {
      digitalWrite(LEFT_RELAY, LOW);
      digitalWrite(RIGHT_RELAY, LOW);
    } else {
      digitalWrite(LEFT_RELAY, HIGH);
      digitalWrite(RIGHT_RELAY, HIGH);
    }
  }

  previous_speed_button = current_speed_button;
  previous_direction_button = current_direction_button;
  switch (state) {
    //speed mode selection
    case 0:
      //motor off
      turn_motor(LOW);
      break;
    case 1:
      //motor on, running at full speed
      turn_motor(HIGH);
      break;
    case 2:
      //motor on, running at 2/3 of speed
      if (currentMillis - previousMillis <= 333) {
        turn_motor(LOW);
      } else {
        turn_motor(HIGH);
      }
      break;
    case 3:
      //motor on, running at 2/3 of speed
      if (currentMillis - previousMillis <= 333) {
        turn_motor(HIGH);
      } else {
        turn_motor(LOW);
      }
      break;
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }

}

