// Basic Commands

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
      break;  
    }
    case 1:
    {
      Serial2.println(command);
      break;  
    }
    case 2:
    {
      Serial3.println(command);
      break;  
    }  
  }

  Serial.print(nSerial);
  Serial.print(" ");
  Serial.println(command);
}

int sonsor_reading(int pin)
{
  int sensorPin = pin;
  int reading = analogRead(sensorPin);
  return reading;
}

// Helper Functions

int light()
{
  int num = sonsor_reading(1);
  return 100000 / num;
}

// Motion Definition

void motion_light()
{
    int n_serial = 3;
    int start = 0;
  
    for(int i = start; i < start+n_serial; ++i)
    {
        int ids[3] = {1,2,3};
        group_control(i, ids, 1500, 3, 25);
        delay(light());
//        delay(1000);
    }

    for(int i = start; i < start+n_serial; ++i)
    {
        int ids[3] = {1,2,3};
        group_control(i, ids, 600, 3, 25);
        delay(light());
//        delay(1000);
    }
            
}

void setup()
{
//  Serial.println('Started');
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop()
{
    motion_light();
}
