import serial
import numpy as np
import time

ser = serial.Serial(12, 9600)
print "Serial Port Name:" + ser.name

 # {0xBA,0x01,0xEA,0x60,0x01,0x03,0x02,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}
#define DEFAULT_BACKWARD_BYTE {0xBA,0x01,0xEA,0x60,0x01,0x03,0x01,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}
#define DEFAULT_STOP_BYTE     {0xBA,0x01,0xEA,0x60,0x01,0x03,0x03,0x30,0x00,0x63,0x9C,0x00,0x0A,0x02,0x26,0xA1,0xFE}

def action(pinID, angle=1500, speed=25):
    command = "#{}P{}T{}\r\n".format(pinID, angle, speed)
    print 'Command: ' + command
    ser.write(command)

def groupAction(pins, angs, speed=25):
    command = "{}T{}\r\n".format(
        ''.join(["#{}P{}".format(p,a) for p,a in zip(pins,angs)]), speed
    )
    print 'Command: ' + command
    ser.write(command)


def motion_1():
    n_leaf = 3
    while True:
        for i in range(1,10,n_leaf):
            groupAction(range(i,i+n_leaf), [1500]*n_leaf)
            time.sleep(np.random.rand())

        for i in range(1,10,n_leaf):
            groupAction(range(i,i+n_leaf), [600]*n_leaf)
            time.sleep(np.random.rand())        

if __name__ == '__main__':
    motion_1()