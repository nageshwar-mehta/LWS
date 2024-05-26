#define ldr_pin A0

int prev_val = 0;
void setup(){
  Serial.begin(9600);
}
void loop(){
  int sensor_val = analogRead(ldr_pin);
  // if(sensor_val >20)
  {
    Serial.println(sensor_val);
  }
  delay(10);
}
