
/* 130 DC Motor 
 by DFRobot <https:www.dfrobot.com> 

*/
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int motorPin = 4; //电机驱动管脚D3
int motorSpeed;   //电机转速变量

void setup()
{
    Serial.begin(9600);
    dht.begin();
    Serial.println("Hi star. Arduino is running...");
}
char target[] = "GET TH";
void loop()
{
    delay(2000);
    char a;
    if (Serial.available())
    {
        a = Serial.read();
        if (a == '1')
        {
            open();
            Serial.print("open f ok");
        }
        else if (a == '2')
        {
            close();
        }
        else if (a == '8')
        {
            getdata();
        }
    }
}

void open()
{
    for (motorSpeed = 0; motorSpeed <= 255; motorSpeed += 5)
    {
        analogWrite(motorPin, motorSpeed); //PWM调速
        delay(30);
    }
}

void close()
{
    for (motorSpeed = 255; motorSpeed >= 0; motorSpeed -= 5)
    {
        analogWrite(motorPin, motorSpeed); //PWM调速
        delay(30);
    }
}
void getdata()
{
    float h = dht.readHumidity(); // 读取当前的湿度

    float t = dht.readTemperature(); // 读取当前的温度，单位C

    float f = dht.readTemperature(true); //读取当前的温度，单位F

    // 如果读取失败则退出，再读取一次
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // 读取体感温度，单位F
    float hif = dht.computeHeatIndex(f, h);
    // 读取体感温度，单位C
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("hum: ");
    Serial.print(h);
    Serial.print("tem: ");
    Serial.println(t);
}