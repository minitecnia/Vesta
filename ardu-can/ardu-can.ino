/*
 
 created 25 Ago 2019
 by Francisco Ochando
 modified 25 Ago 2019
 by Francisco Ochando

*/

void getAcc() {
  mpu.getAcceleration(&ax, &ay, &az);
  
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
