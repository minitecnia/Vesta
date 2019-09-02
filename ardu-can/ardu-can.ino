/*
 
 CAN, IMU register using USB server

 A simple CAN, IMU data USB server sends the value of the CAN frame 
 and acceleration/angle input using an Arduino.

 created 25 Ago 2019
 by Francisco Ochando
 modified 25 Ago 2019
 by Francisco Ochando
 
 Using Arduino UNO with MPU6050, MCP2515
 MPU6050 IMU card
 Vcc - 3.3V
 SDA - A4
 SCL - A5
 GND - GND
 
 MCP2515 CAN card
 Vcc - 5V
 CS - 10
 SI - 11
 SO - 12
 SCK - 13
 GND - GND

*/

void getAcc() {
  mpu.getAcceleration(&ax, &ay, &az);
  
  float ax_ = ax;
  float ay_ = ay;
  float az_ = az;
  float agx = ax_/4096;
  float agy = ay_/4096;
  float agz = az_/4096;
 
  // Send results
  Serial.print("{'eID':'Acceleration','X':'");
  Serial.print(ax);
  Serial.print("','Y':'");
  Serial.print(ay);
  Serial.print("','Z':'");
  Serial.print(az);
  Serial.println("'}'"); 
}

void printAcc() {
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate angle
  float accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2))) * (180.0 / 3.14);
  float accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * (180.0 / 3.14);

  // Show results
  Serial.print("{'eID':'Inclinacion','X':'");
  Serial.print(accel_ang_x);
  Serial.print("','Y':'");
  Serial.print(accel_ang_y);
  Serial.println("'}'");
  delay(100);
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    Wire.begin();
    mpu.initialize();
    Serial.println(mpu.testConnection() ? F("# IMU ready!") : F("# IMU error!"));
    gps.begin(9600);
    pinMode(ledPin,OUTPUT);
    Serial.println("# GPS Init Ok. Listening!");

    while (CAN_OK != CAN.begin(CAN_250KBPS))
    {
        Serial.println("# CAN BUS Failed");
        delay(100);
    }
    Serial.println("# CAN BUS OK. Listening!");
    Serial.println("#");
    delay(3000);
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    printAcc();
    if (gps.available())
    {
        char data;
        data = gps.read();
        Serial.print(data);
    }

    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);

        unsigned long canId = CAN.getCanId();

        Serial.print(canId, HEX);
        Serial.print(", ");

        for(int i = 0; i<len; i++)
        {
            Serial.print(buf[i]);
            Serial.print(", ");
            if(ledON && i==0)
            {

                digitalWrite(ledPin, buf[i]);
                ledON = 0;
                delay(500);
            }
            else if((!(ledON)) && i==4)
            {

                digitalWrite(ledPin, buf[i]);
                ledON = 1;
            }
        }
        Serial.println();
    }
}
