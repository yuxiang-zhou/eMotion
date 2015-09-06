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

int ids[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void motion_light()
{
    int n_serial = 3;
    int start = 0;

    for(int i = start; i < start+n_serial; ++i)
    {
        group_control(i, ids, 1500, 32, 25);
        delay(light());
//        delay(1000);
    }

    for(int i = start; i < start+n_serial; ++i)
    {
        group_control(i, ids, 600, 32, 25);
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
