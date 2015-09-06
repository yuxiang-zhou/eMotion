// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
//B3 02 F8 0C 01 03 00 31 00 15 7C 02 26 02 26 00 01 00 01 1F FE

/*
  0: begin
  1: 00 :点动模式 01:单步模式 02:自动模式 03:单次往返 04:按次往返 05 :按键回零单方向 06 :前进回零往返模式 7：单放向运行模式 第
  2-3: speed
  4: addr
  5: dont care
  6: direction & stop 01 :正运行  02 :负运行  03 :停止 
  7: 启动上电运行使能、启动上电回零使能、急停常开、限位常开、 启动 0.2 倍频率输出、启动单开关触发、启动输入开关失效、启动位置控制使能
  8-10: dont care
  11-12: speed up
  13-14: speed down
  15: CRC
  16: Ending

*/ 
//                             0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20
#define DEFAULT_INIT_BYTE     {0xB3,0x01,0xEA,0x60,0x01,0x03,0x00,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0x00,0x01,0x00,0x01,0xD9,0xFE}

#define DEFAULT_FORWARD_BYTE  {0xBA,0x01,0xEA,0x60,0x01,0x03,0x02,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}
#define DEFAULT_BACKWARD_BYTE {0xBA,0x01,0xEA,0x60,0x01,0x03,0x01,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}
#define DEFAULT_STOP_BYTE     {0xBA,0x01,0xEA,0x60,0x01,0x03,0x03,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}
// #define DEFAULT_STOP_BYTE     {0xBA,0x01,0xEA,0x60,0x01,0x03,0x03,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}

int nIndex = 25;
int gap = 200;
int start = 1;
int indexes[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};

void setup() {
  Serial.begin(9600);
  // Serial1.println("Initialising...\n");
//
  for ( byte i = start; i < start + nIndex; ++i )
  {
    InitDevice(indexes[i]);
    delay(1000);
  } 
  // Serial1.flush();
  // Serial.println(10);
  // delay(1000);
  // Serial.println(9);
  // delay(1000);
  // Serial.println(8);
  // delay(1000);
  // Serial.println(7);
  // delay(1000);
  // Serial.println(6);
  // delay(1000);
  // Serial.println(5);
  // delay(1000);
  // Serial.println(4);
  // delay(1000);
  // Serial.println(3);
  // delay(1000);
  // Serial.println(2);
  // delay(1000);
  // Serial.println(1);
  // delay(1000);
  // Serial.println("Begin");
}

void loop() {
  Serial.println("Begin");
  for ( int i = start; i < start + nIndex; ++i )
  {
    Forward(indexes[i]);
    delay(gap);
  }
  // Serial.flush();
  delay(2000);


  for ( int i = start; i < start + nIndex; ++i )
  {
    Backward(indexes[i]);
    delay(gap);
  }
  // Serial.flush();

  delay(2000);

  
  for (int i = start; i < start + nIndex; ++i)
  {
    Stop(indexes[i]); 
    delay(gap);
  }
  // Serial.flush();
  return;
    
}


//Set default parameters to the selected device
byte InitDevice(byte nDeviceID)
{
  
  byte control[] = DEFAULT_INIT_BYTE; 
  control[4] = nDeviceID;
  control[19] = CRC(control,19);

  Serial1.write(control,21);

  byte nread = Serial1.read();
  Serial1.println(nread);
  return nread;

}

//Send Run command to selected device
void Forward(byte nDeviceID)
{
  byte control[] = DEFAULT_FORWARD_BYTE;
  control[4] = nDeviceID;
  control[15] = CRC(control,15);

  Serial1.write(control,17);
  Serial.print("Forward ");
  Serial.println(nDeviceID);
  Serial1.flush();
  int nread = Serial1.read();
  // while(nread != 0xb1 ) {
  //   Serial1.write(control,17);
  //   Serial1.flush();
  //   nread = Serial1.read();
  // }
}

//
void Backward(byte nDeviceID)
{
  byte control[] = DEFAULT_BACKWARD_BYTE;
  control[4] = nDeviceID;
  control[15] = CRC(control,15);

  Serial1.write(control,17);
  Serial.print("Backward");
  Serial.println(nDeviceID);
  int nread = Serial1.read();
  // while(nread != 0xb1 ) {
  //   Serial1.write(control,17);
  //   Serial1.flush();
  //   nread = Serial1.read();
  // }
  // Serial1.flush();
}

//Stop 
void Stop(byte nDeviceID)
{
  byte control[] = DEFAULT_STOP_BYTE;
  control[4] = nDeviceID;
  control[15] = CRC(control,15);

  Serial1.write(control,17);
  Serial.print("test");
  Serial.println(nDeviceID);
  int nread = Serial1.read();
  // while(nread != 0xb1 ) {
  //   Serial1.write(control,17);
  //   Serial1.flush();
  //   nread = Serial1.read();
  // }

  
}

//Process CRC
byte CRC(byte btys[], byte nLength)
{
  byte bty = btys[0]; 
//byte nRet = 0;
  for ( byte i = 1; i < nLength; i ++ )
  {
//nRet = nRet ^ byte(btys[i]);
    bty ^= btys[i];
  }
  return bty;
}

