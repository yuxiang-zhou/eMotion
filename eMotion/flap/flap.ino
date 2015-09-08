// Basic Commands
int ids[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void group_control(int nSerial, int ids[], int angle, int num, int sp){
  char command[512] = "";

  for(int i = 0; i < num; ++i)
  {
    char id[16] = "";
    sprintf(id, "#%dP%d", ids[i], angle);
    strcat(command, id); 
  }
  char chrspeed[8] = "";
  sprintf(chrspeed, "T%d", sp);
  strcat(command, chrspeed);

  switch(nSerial)
  {
    case 0:
    {
      Serial1.println(command);
      Serial1.flush();
      break;  
    }
    case 1:
    {
      Serial2.println(command);
      Serial2.flush();
      break;  
    }
    case 2:
    {
      Serial3.println(command);
      Serial3.flush();
      break;  
    }  
  }

  Serial.print(nSerial);
  Serial.print(" ");
  Serial.println(command);
  Serial.flush();
}

int sonsor_reading(int pin)
{
  int sensorPin = pin;
  int reading = analogRead(sensorPin);
  return reading;
}

int irRead(int readPin, int triggerPin)
{
  int halfPeriod = 13; //one period at 38.5khZ is aproximately 26 microseconds
  int cycles = 38; //26 microseconds * 38 is more or less 1 millisecond
  int i;
  for (i=0; i <=cycles; i++)
  {
    digitalWrite(triggerPin, HIGH); 
    delayMicroseconds(halfPeriod);
    digitalWrite(triggerPin, LOW); 
    delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
  }
  return digitalRead(readPin);
}

// Helper Functions

int light()
{
  int num = sonsor_reading(1);
  return 100000 / num;
}

int irSensorPin = 2;
int irLED = 3;

int IR()
{
  int num = irRead(irSensorPin, irLED);
  return num;
}

// Motion Definition
void motion_light()
{
    int n_serial = 3;
    int start = 0;

    for(int i = start; i < start+n_serial; ++i)
    {
        group_control(i, ids, 1500, 32, 25);
        if(IR())
          delay(1000);
        else
          delay((rand() / RAND_MAX) * light());       
    }

    for(int i = start; i < start+n_serial; ++i)
    {
        group_control(i, ids, 600, 32, 25);
        if(IR())
          delay(1000);
        else
          delay((rand() / RAND_MAX) * light());
    }
            
}

void setup()
{
  pinMode(irSensorPin, INPUT);
  pinMode(irLED, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop()
{
    motion_light();
}
