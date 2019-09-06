#!/usr/bin/python
import smbus
import math
 
# Register
power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c
 
def read_byte(reg):
    return bus.read_byte_data(address, reg)
 
def read_word(reg):
    h = bus.read_byte_data(address, reg)
    l = bus.read_byte_data(address, reg+1)
    value = (h << 8) + l
    return value
 
def read_word_2c(reg):
    val = read_word(reg)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val
 
def dist(a,b):
    return math.sqrt((a*a)+(b*b))
 
def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)
 
def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)

bus = smbus.SMBus(1) # bus = smbus.SMBus(0) fuer Revision 1
address = 0x68       # via i2cdetect
 
# Activation
bus.write_byte_data(address, power_mgmt_1, 0)
 
gyro_xout = read_word_2c(0x43)
gyro_yout = read_word_2c(0x45)
gyro_zout = read_word_2c(0x47)
 
print "gyro_xout: ", ("%5d" % gyro_xout), " skaliert: ", (gyro_xout / 131)
print "gyro_yout: ", ("%5d" % gyro_yout), " skaliert: ", (gyro_yout / 131)
print "gyro_zout: ", ("%5d" % gyro_zout), " skaliert: ", (gyro_zout / 131)

# Accelerometer
 
aceleration_xout = read_word_2c(0x3b)
aceleration_yout = read_word_2c(0x3d)
aceleration_zout = read_word_2c(0x3f)
 
aceleration_xout_scale = aceleration_xout / 16384.0
aceleration_yout_scale = aceleration_yout / 16384.0
aceleration_zout_scale = aceleration_zout / 16384.0
 
print "Aceleration_xout: ", ("%6d" % aceleration_xout), " skaliert: ", aceleration_xout_scale
print "Aceleration_xout: ", ("%6d" % aceleration_yout), " skaliert: ", aceleration_yout_scale
print "Aceleration_zout: ", ("%6d" % aceleration_zout), " skaliert: ", aceleration_zout_scale
 
print "X Rotation: " , get_x_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert)
print "Y Rotation: " , get_y_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert)

