#include "Log.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
// saving log file
File filef;
int SDOK=0;
const int chipSelect = 53;  // chip select pin for the SD module.it should be connected to 53 of module


/*
    SD card Functions
*/

void initSD(){

    if(SDOK==0){
        if (SD.begin(chipSelect)) 
            printErrorCode(F("SD_INIT_DONE"),SD_INIT_DONE); 
        else
            printErrorCode(F("SD_INIT_ERROR"),SD_INIT_ERROR);
        SDOK=1;
    }
}

// file extention
void createFileSD(String fileName)
{
  if (!SD.exists(fileName)) 
  {
    filef = SD.open(fileName, FILE_WRITE);
    filef.close();
 
    if (SD.exists(fileName)) 
        printErrorCode(F("SD_FILE_CREATION_ERROR : "),SD_FILE_CREATION_ERROR);
  }
}

//Write the message on the Log
void writeFileSD(String fileName,String message)
{
    createFileSD(fileName);
    filef = SD.open(fileName, FILE_WRITE);
    if (filef) 
    {
        filef.println(message);
        filef.close();
    } 
    else 
    {
        Serial.println("SD_FILE_OPEN_ERROR :" + fileName);
    }
}

/*
    LCD Functions
*/

void initLCD(){

    uint8_t signal_0[8]  = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f};
    uint8_t signal_1[8]  = {0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x1f};
    uint8_t signal_2[8]  = {0x0, 0x0, 0x0, 0x1f, 0x1f, 0x1f, 0x1f};
    uint8_t signal_3[8]  = {0x0, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
    uint8_t signal_4[8]  = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};

    lcd.begin();
    lcd.backlight();

    lcd.createChar(0, signal_0);
    lcd.createChar(1, signal_1);
    lcd.createChar(2, signal_2);
    lcd.createChar(3, signal_3);
    lcd.createChar(4, signal_4);
    lcd.home();
}

void printLCDDouble(double val,int i,int j){ 
    lcd.setCursor(i,j);
    lcd.print(String(val,2));
}
  
void printLCDCharArray(char *f,int i,int j){
    lcd.setCursor(i,j);
    lcd.print(f);
}
  
void printLCDString(String f,int i,int j){
    lcd.setCursor(i,j);
    lcd.print(f);
}
  
void printLCD(char *f){
    lcd.clear();
    lcd.print(f);
}

void clearLCD(){
    lcd.clear();
}

/*
    Print Functions 
*/

void printValues(String name_index,double value){
    Serial.print(name_index + ":");
    Serial.println(value);
    lcd.clear();
    printLCDString(name_index,0,0);
    printLCDDouble(value,0,1);
    delay(1000);
}

void printValues(String name_index,String value){
    Serial.print(name_index);
    Serial.println(value);
    lcd.clear();
    printLCDString(name_index,0,0);
    printLCDString(value,0,1);
    delay(1000);
}

void printValues(String name_index,String tx,double value){
    Serial.print(name_index + ":");
    Serial.println(value);
    printLCDString("           ",0,0);
    printLCDString("           ",1,0);
    printLCDString(name_index,0,0);
    printLCDDouble(value,5,0);
    printLCDString(tx.substring(2),0,1);
    
    delay(1000);
}

void printValues(String name_index,String tx,String value){
    Serial.print(name_index);
    Serial.println(value);
    printLCDString("           ",0,0);
    printLCDString("           ",1,0);
    printLCDString(value,5,0);
    printLCDString(tx.substring(2),0,1);
    delay(1000);
}

void printError(String text){
    Serial.println(text);
    lcd.clear();
    printLCDString(text,0,0);
}

void printStrOnDebug(String text){
    Serial.print(text);
}

void printStr(String text){
    Serial.println(text);
    lcd.clear();
    printLCDString(text,0,0);
}

void logData(String &text){
    Serial.println(text);
    writeFileSD("DTLOG.txt",text);
}

void writeErrorLogData(String &text){
  writeFileSD(F("SE.txt"),text);
}

void printStr(String text,String logTime,int DefinitionCode ){
    Serial.println(text);
    logTime.concat(" | ");
    logTime.concat(text);
    writeFileSD("SYSLOG.txt",logTime);
    lcd.clear();
    printLCDString(text,0,0);
    soundIndicator(DefinitionCode/10,DefinitionCode%10);
}

void printErrorCode(String text, int DefinitionCode){
    Serial.println(text);
    writeFileSD("ERRLog.txt",text);
    lcd.clear();
    printLCDString(text,0,0);
    soundIndicator(DefinitionCode/10,DefinitionCode%10);
}

void printErrorCode(String text,String logTime,int DefinitionCode ){
    Serial.println(text);
    logTime.concat(" | ");
    logTime.concat(text);
    writeFileSD("ERRLog.txt",logTime);
    lcd.clear();
    printLCDString(text,0,0);
    soundIndicator(DefinitionCode/10,DefinitionCode%10);
}

// sound soundIndicator
void soundIndicator(int count1,int count2){

    //long turn
    while(count1>0){
        tone(BUZZER,1000);
        delay(200);
        noTone(BUZZER);
        delay(100);
        count1--;
    }
    //long turn
    while(count2>0){
        tone(BUZZER,1000);
        delay(100);
        noTone(BUZZER);
        delay(100);
        count2--;
    }
    delay(1000);
  }


void showStrength(int x){
  lcd.setCursor(12,0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
  lcd.setCursor(12,0);
  if(x< 10 && x>= 2)
    lcd.write(1);
  else if(x< 15 && x>= 10){
    lcd.write(1);
    lcd.write(2);
  }
  else if(x< 20 && x>= 15){
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
  }
  else if(x<=30 && x>= 20){
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
  }else
    lcd.write(0);
}
