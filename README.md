# istSOS Open source Weather station

istSOS is a Free and Open Source Sensor Observation Service Data Management System. istSOS allows for 
managing and dispatch observations from monitoring sensors according to the Sensor Observation Service standard.
istSOS has oppotunity to connect datacollectors wia REST API. This Source explains the data collector internal structure.

 [More About ISTSOS](http://istsos.org/en/latest/doc/index.html)
 
 <p align="center">
  <img src="https://github.com/HarithKK/ISTSOS/blob/master/img.png"/>
 </p>
 
## Getting Started

This Is a Weather station Internal code. this is requested to buy the hardware implementation. this is fully Arduino based implemantation.

### Prerequisites

1. [Arduino IDE](https://www.arduino.cc/en/Main/Software) - Download for Source edit
2. Hardware Implementation

### Installing

1. Install Arduino To Your Computer
2. Open esos/esos.ino in Arduino IDE
3. External Libraries are shown below
```
  External Libraries
  ```
    1.Grove_BME280
    2.BH1750
    3.DallasTemperature
    4.DHTlib - DHT sensor library
    5.DS1307RTC
    6.Sim800
    7.OneWire
    8.TinyGSM
    9.Arduino-LiquidCrystal-I2C-library-master
  ```
```

4. Copy Libraries to your default Arduino library folder
  ```
    For Windows : C:\Users\<Username>\Documents\Arduino\libraries Folder
    For OSx     : ~/Documents/Arduino/libraries/
  ```
### Change Common GPRS Settings

1. Open Settings.h file 
2. Chnage APN, Username, Password
 ```
  #define APN "mobitel"
  #define USERNAME ""
  #define PASSWORD ""
 ```
### Change istSOS Server Settings

1. Open Settings.h file 
2. Chanage POSTREQ for POST Request URL. (** Read [istSOS Document](http://istsos.org/en/latest/doc/) clearly Before Change this     parameter)
3. Change PROCEDURE as your istSOS procedure ID

```
   #define POSTREQ "/istsos/wa/istsos/services/sl/operations/fastinsert"
   #define PROCEDURE "a0303bb4f9e311e7953f0800273cbaca"

```
### Change SLPIOT Server Settings

1. Open Settings.h file 
2. Change GUID_SLPIOT as your SLPIOT Station ID

```
   #define SERVER "slpiot.org"
   #define GUID_SLPIOT "e813b67c-3c7a-40"
```

### Enable Server Communication

1. Open Settings.h file 
2. Change ENABLE_ISTSOS as 1 for Communicate with ISTSOS Server (0 if not)
3. Change ENABLE_SLPIOT as 1 for Communicate with SLPIOT Server (0 if not)

```
   #define ENABLE_ISTSOS 1
   #define ENABLE_SLPIOT 1
```

### Enable Sensor Participation

This will enable each and every sensor connected to the whether station.( 1 for enable the sensor and 0 for otherwise)

```
#define EXT_TEMP_ENABLE 1
#define INT_TEMP_ENABLE 1
#define EXT_HUM_ENABLE 1
#define INT_HUM_ENABLE 1
#define SM_ENABLE 1
#define PRESSURE_ENABLE 1
#define ALTITUDE_ENABLE 1
#define LUX_ENABLE 1
#define WS_ENABLE 1
#define WD_ENABLE 1
#define RG_ENABLE 1
#define BT_ENABLE 1

```

### Running 

1. Run esos.ino file from arduino IDE.
2. Upload the Changed source to your station
3. Run the station.

