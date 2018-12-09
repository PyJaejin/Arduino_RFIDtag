#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
 
#define uchar   unsigned char
#define uint    unsigned int
 
//4 bytes tag serial number, the first 5 bytes for the checksum byte
uchar serNumA[5];
 
uchar fifobytes;
uchar fifoValue;
 
AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module
int  buzz = 7;
const int chipSelectPin = 10;
const int NRSTPD = 9;
#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Maximum length of the array
#define MAX_LEN 16
DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);


void setup() {               
   Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps
   pinMode(buzz, OUTPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(SUNDAY);
  rtc.setTime(17,58,0);
  rtc.setDate(9,12,2018); 
  
  // start the SPI library:
    SPI.begin();
   
    pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
    pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
    digitalWrite(NRSTPD, HIGH);
 
    myRFID.AddicoreRFID_Init(); 
}
 
void loop()
{
  lcd.setCursor(0,0);
  lcd.print(rtc.getDOWStr());
  lcd.setCursor(0,1);
  lcd.print(rtc.getDateStr());
  
  uchar i, tmp, checksum1;
  uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;  //Selection operation block address 0 to 63
  String mynum = "";
  str[1] = 0x4400;

    //Find tags, return tag type
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
    if (status == MI_OK) { }
    //Anti-collision, return tag serial number 4 bytes
    status = myRFID.AddicoreRFID_Anticoll(str);
    if (status == MI_OK)
    {
      checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
      Serial.println(str[0]); // RFID 고유값
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz,LOW);
    }
         
        myRFID.AddicoreRFID_Halt();        //Command tag into hibernation 
        delay(500);        
}
