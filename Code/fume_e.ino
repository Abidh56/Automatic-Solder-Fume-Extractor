/*Automatic Solder fume Extractor
 * BY 
 * ABID HOSSAIN
 * The Fume Extracture turns on when it detects any somoke....
 * 
*/

int SensorPin = A5;
int led = 7;  
float SensorOut = 0;
float SensorVo = 0;
float Dust = 0;
float Voltage_noDust = 0.12; //calibrate by changing this
float K = 0.5;               //Sensitivity from the datasheet 0.5V/ugm/m^3
int relay= 2;

void setup()
{
 pinMode(led,OUTPUT);
 pinMode(relay,OUTPUT);
 Serial.begin(115200);
 delay(10);
 digitalWrite (relay, HIGH);
 delay(5000);
 digitalWrite (relay, LOW);

}

void loop()
{
  digitalWrite(led,LOW);          //turning on the led
  delayMicroseconds(280);         //wait for 0.28ms
  SensorOut = analogRead(SensorPin);    //read the sensor output voltage
  delayMicroseconds(50);                //wait for 50us
  digitalWrite(led,HIGH);               //turning off the led
  delayMicroseconds(9670);              //wait for (10000-280-50)=9670us
  SensorVo = SensorOut*(5.0/1024);      //calculating sensor output voltage
  Dust = (SensorVo-Voltage_noDust)*100/K;     //calculating Dust density(ugm)/m^3
 
  if ( Dust < 0)
  {
    Dust = 0.00;
  }
//Serial.println(Dust); 
//delay(100);

if (Dust > 100){
 digitalWrite (relay, HIGH);
 delay(5000);
}
else {
 digitalWrite (relay, LOW);
}
}
