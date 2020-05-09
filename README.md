# Arduino_RFIDtag
스마트폰 NFC, 아두이노 키트의 RFID 카드 등을 접촉하면 특정한 tag값을 출력한다.

부가적으로 접촉시 부저 울림, RTC 모듈을 통한 시간 출력 등 기능을 제공한다.


필요한 라이브러리는 다음.


#include <AddicoreRFID.h> //RFID


#include <LiquidCrystal_I2C.h> //LCD


#include <DS1302.h> //RTC


