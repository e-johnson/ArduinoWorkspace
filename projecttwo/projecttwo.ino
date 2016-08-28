int switchState = 0; 
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(2, INPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  switchState - digitalRead(2); 

}
