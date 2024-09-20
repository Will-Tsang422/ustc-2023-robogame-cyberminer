import serial
import time
if __name__ == '__main__':
    ser = serial.Serial("/dev/ttyAMA1", 115200)
    writebuf = bytearray([0x01, 0x02, 0x03, 0x04])
    while 1:
        bytes = ser.write(writebuf)
        
        print(bytes)
        for i in range(4):
            writebuf[i] += 0x01
        time.sleep(2)
        
        