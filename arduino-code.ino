#include <Servo.h> 
#include <i2cmaster.h>


Servo myservo;  //below servo for x-axis
Servo cat;      //above servo for y-axis
int pos; 
int ab;
int t;


void setup() 
{Serial.begin(9600);
i2c_init(); 
PORTC = (1 << PORTC4) | (1 << PORTC5);  //enable internal pullup resistors on i2c ports
myservo.attach(11);
 cat.attach(9);
}


void loop(){
 
int dev = 0x5A<<1;
int data_low = 0;
int data_high = 0;
int pec = 0;
 
 for(pos=41;pos<=131; pos += 1 )
 { 
 myservo.write(pos);

  if(pos%2!=0)
{ 
  for(ab=180;ab>=91;ab -= 1)
 { cat.write(ab);
 
i2c_start_wait(dev+I2C_WRITE);
i2c_write(0x07);
i2c_rep_start(dev+I2C_READ);
data_low = i2c_readAck(); //Read 1 byte and then send ack
data_high = i2c_readAck(); //Read 1 byte and then send ack
pec = i2c_readNak();
i2c_stop();

while(Serial.available()<=0)//Two Way Communication
{}
if(Serial.read()=='p')
{Serial.write(data_low);}
while(Serial.available()<=0)
{}
if(Serial.read()=='t')
{Serial.write(data_high);}
delay(1);
}
}

if(pos%2==0)
{
 for(t=91;t<=180;t += 1)
 { cat.write(t);
i2c_start_wait(dev+I2C_WRITE);
i2c_write(0x07);
i2c_rep_start(dev+I2C_READ);
data_low = i2c_readAck(); //Read 1 byte and then send ack
data_high = i2c_readAck(); //Read 1 byte and then send ack
pec = i2c_readNak();
i2c_stop();

while(Serial.available()<=0)//Two way communication
{}
if(Serial.read()=='p')
{Serial.write(data_low);}
while(Serial.available()<=0)
{}
if(Serial.read()=='t')
{Serial.write(data_high);}
delay(1);
 }
}
}
}
