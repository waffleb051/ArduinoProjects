//Imported Libaries Area
#include <LiquidCrystal.h>

//Pin Area
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnUP     1
#define btnDOWN   2
#define btnNONE   5

const int DSTPIN = 22;

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in > 1000) return btnNONE;
 
 return btnNONE; 
  
}//end button reads

//Code area
void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Distance in: "); // print a simple message
}//end setup


//Loop Area
void loop()
{
  long duration, inches, cm;
  
  pinMode(DSTPIN, OUTPUT);
  digitalWrite(DSTPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(DSTPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(DSTPIN, LOW);
  
  pinMode(DSTPIN, INPUT);
  duration = pulseIn(DSTPIN, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  lcd.setCursor(2,1);
  
  lcd.setCursor(0,1);  
  lcd_key = read_LCD_buttons(); 
  
  switch (lcd_key)
  {
    case btnUP:
    {
     lcd.print("CM: ");
     lcd.print(cm);s
     break; 
    }
    case btnDOWN:
    {
     lcd.print("Inches: ");
     lcd.print(inches);
     break;
    }
    case btnNONE:
    {
     lcd.print("                    ");
     
     break;
    }
  }//end switch
}//end loop

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
