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

  Serial.println(command);
}
// Motion Definition

int ids[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};


void setup()
{
//  Serial.println('Started');
  Serial.begin(9600);
}

void loop()
{
    group_control(0, ids, 1500, 32, 25);
    delay(1000);
    group_control(0, ids, 500, 32, 25);
    delay(1000);
}
