#include <Servo.h> 


Servo myservo;  
Servo cat;

int pos;
int ab;
int t;


void setup() 
{Serial.begin(9600);
myservo.attach(11);// below servo x-axis
 cat.attach(9); // above servo y-axis
} 


void loop(){
 
 
 for(pos=130;pos>=41; pos -= 1 )
 { 
 myservo.write(pos);

 if(pos%2==0)
{ 
  for(ab=180;ab>=90;ab -= 1)
 { cat.write(ab);
 delay(30);
 }
}
if(pos%2!=0)
{
 for(t=90;t<=180;t += 1)
 { cat.write(t);
 delay(30);
 }
}
}
}
