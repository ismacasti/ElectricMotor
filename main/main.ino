#define LEFT_RELAY A4
#define RIGHT_RELAY A3
#define POWER_RELAY A5

int state = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_RELAY, OUTPUT);
  pinMode(RIGHT_RELAY, OUTPUT);
  pinMode(POWER_RELAY, OUTPUT);
  state = 0;
}

void loop() {

}
