void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10,INPUT);
  pinMode(11,INPUT);

}

void loop() {
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
    else{
    // send the value of analog input 0:
      Serial.println(analogRead(A0));

    }
     // Читаем значение с аналогового входа

    //Wait for a bit to keep serial data from saturating
    delay(1);
}