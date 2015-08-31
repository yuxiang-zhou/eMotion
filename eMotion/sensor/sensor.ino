// Basic Commands

#define humanIN 5
#define sonarIN 3
#define sonarOUT 2
void setup()
{
//  Serial.println('Started');
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  pinMode(sonarIN, INPUT);
  pinMode(humanIN, INPUT);
  pinMode(sonarOUT, OUTPUT);
}

void loop()
{
    Serial.print("Light sensor: ");
    int light = analogRead(1);
    Serial.println(light);  

    Serial.print("Human sensor: ");
    int human =  digitalRead(humanIN);
    Serial.println(human);
//
//    Serial.print("Sonar sensor: ");
//    digitalWrite(sonarOUT, LOW); 
//    delayMicroseconds(2); 
//    
//    digitalWrite(sonarOUT, HIGH);
//    delayMicroseconds(10); 
//     
//    digitalWrite(sonarOUT, LOW);
//    long duration = pulseIn(sonarIN, HIGH);
//     
//     //Calculate the distance (in cm) based on the speed of sound.
//    long distance = duration/58.2;
//    Serial.println(distance);

    delay(1000);
}
