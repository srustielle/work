int switchpin =D4;
int ledpin= D0;
int switchvalue;

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(switchpin, INPUT_PULLUP);
  pinMode(switchpin, 
  // put your setup code here, to run once:

}

void loop() {
  switchvalue= digitalRead(switchpin);
  digitalWrite(ledpin, !switchvalue);// put your main code here, to run repeatedly:

}
