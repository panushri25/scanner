mport processing.serial.*;

Serial myport;

float[] temp = new float[90*91];


int data_low ;
int data_high ;
int count=0;
float mint=90;
float maxt=-50;
int count1=0;
float val;
float clr;
int i,p,j;
float r,g,b;

void setup(){
 colorMode(HSB,255);
 size(400,400);
 noStroke();
  println(Serial.list());
 String portName=Serial.list()[0];
 myport = new Serial(this, portName, 9600);
 noLoop();
}



void draw(){
 
 while(count<90*91)
{
  myport.write('p');
  
  while(myport.available()<=0)
  {}
 {data_low = myport.read();
 
 myport.write('t');
  while(myport.available()<=0)
  {}
 data_high = myport.read();
 
 float tempFactor = 0.02; // 0.02 degrees per LSB
float tempData = 0x0000;
float frac;
// This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
tempData = (float)(((data_high & 0x007F) << 8) + data_low);
tempData = (tempData * tempFactor)-0.01;
tempData = tempData - 273.15;
if(tempData>maxt)
{maxt=tempData;}
if(tempData<mint)
{mint=tempData;}
temp[count]=tempData;
count++;
println(tempData);
println(count);
 }
}
val=(mint-maxt)/200;
PImage timg = createImage(91, 90, RGB);
 timg.loadPixels();//accessing pixels  according to the servo motion
 for(j=1;j<=timg.width;j++){
if((j%2)!=0)
{for ( i =(timg.width*timg.height)-j; i>=0; i=i-timg.width) {
 float t=temp[count1];
++count1;
float h=(t-maxt)/val;
 color cat=color(h,255,255);
timg.pixels[i] = cat;
 }
}
 if(j%2==0)
{for(p=timg.width-j;p<timg.width*timg.height;p=p+timg.width)
{ 
float t=temp[count1];
++count1;
color cat=color (0,0,0);
float h=(t-maxt)/val;
cat=color(h,255,255);
timg.pixels[p] = cat;
}
}
}
image(timg,0,0,200,200);
save("file.jpg");
}
