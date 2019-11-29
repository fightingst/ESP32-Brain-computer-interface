/* ADS1256 simple library for Arduino
   ADS1256, datasheet: http://www.ti.com/lit/ds/sbas288j/sbas288j.pdf
   connections to Atmega328 (UNO)

    CLK  - pin 13
    DIN  - pin 11 (MOSI)
    DOUT - pin 12 (MISO)
    CS   - pin 10
    DRDY - pin 9
    RESET- pin 8 (or tie HIGH?)
    DVDD - 3V3
    DGND - GND
*/

#define ADS_SPISPEED 1250000

#define ADS_RST_PIN    8 //ADS1256 reset pin
#define ADS_RDY_PIN    9 //ADS1256 data ready
#define ADS_CS_PIN    10 //ADS1256 chip select
// 11, 12 and 13 are taken by the SPI

void initADS(){
  pinMode(ADS_CS_PIN, OUTPUT);

  pinMode(ADS_RDY_PIN, INPUT);
  pinMode(ADS_RST_PIN, OUTPUT);
  digitalWrite(ADS_RST_PIN, LOW);
  delay(1); // LOW at least 4 clock cycles of onboard clock. 100 microsecons is enough
  digitalWrite(ADS_RST_PIN, HIGH); // now reset to deafult values

  delay(150);

  digitalWrite(ADS_CS_PIN, LOW); // select ADS
  delayMicroseconds(50);
  while (digitalRead(ADS_RDY_PIN)) {}  // wait for ready_line to go low
  SPI.beginTransaction(SPISettings(ADS_SPISPEED, MSBFIRST, SPI_MODE1));
  delayMicroseconds(10);

  //Reset to Power-Up Values (FEh)
  SPI.transfer(0xFE);
  delayMicroseconds(100);

  byte status_reg = 0 ;  // address (datasheet p. 30)
  byte status_data = 0x01; //status: Most Significant Bit First, Auto-Calibration Disabled, Analog Input Buffer Disabled
  //0x03; //to activate buffer
  SPI.transfer(0x50 | status_reg);
  SPI.transfer(0x00);   // 2nd command byte, write one register only
  SPI.transfer(status_data);   // write the databyte to the register
  delayMicroseconds(10);

  //PGA SETTING
  //1 ±5V        000 (1)
  //2 ±2.5V      001 (2)
  //4 ±1.25V     010 (3)
  //8 ±0.625V    011 (4)
  //16 ±312.5mV  100 (5)
  //32 ±156.25mV 101 (6)
  //64 ±78.125mV 110 (7) OR 111 (8)
  byte adcon_reg = 2; //A/D Control Register (Address 02h)
  byte adcon_data = 0x20; // 0 01 00 000 => Clock Out Frequency = fCLKIN, Sensor Detect OFF, gain 1
  //0x25 for setting gain to 32, 0x27 to 64
  SPI.transfer(0x50 | adcon_reg);
  SPI.transfer(0x00);   // 2nd command byte, write one register only
  SPI.transfer(adcon_data);   // write the databyte to the register
  delayMicroseconds(10);
   
  //Set sampling rate
  byte drate_reg = 3; // Choosing Data Rate register = third register.
  byte drate_data = 0b11000000; // 11000000 = 3,750SPS
  SPI.transfer(0x50 | drate_reg);
  SPI.transfer(0x00);   // 2nd command byte, write one register only
  SPI.transfer(drate_data);   // write the databyte to the register
  delayMicroseconds(10);

  //done with settings, can close SPI transaction now
  digitalWrite(ADS_CS_PIN, HIGH); //unselect ADS
  delayMicroseconds(50);

  Serial.println("ADS1256 configured");
}

long readADS(byte channel) {
  long adc_val = 0; // unsigned long is on 32 bits

  digitalWrite(ADS_CS_PIN, LOW);
  delayMicroseconds(50);
  SPI.beginTransaction(SPISettings(ADS_SPISPEED, MSBFIRST, SPI_MODE1)); // start SPI
  delayMicroseconds(10);
  //The most efficient way to cycle through the inputs is to
  //change the multiplexer setting (using a WREG command
  //to the multiplexer register MUX) immediately after DRDY
  //goes low. Then, after changing the multiplexer, restart the
  //conversion process by issuing the SYNC and WAKEUP
  //commands, and retrieve the data with the RDATA
  //command.
  while (digitalRead(ADS_RDY_PIN)) {} ;

  byte data = (channel << 4) | (1 << 3); //AIN-channel and AINCOM
  SPI.transfer(0x50 | 1); // write (0x50) MUX register (0x01)
  SPI.transfer(0x00);   // number of registers to be read/written − 1, write one register only
  SPI.transfer(data);   // write the databyte to the register
  delayMicroseconds(10);

  //SYNC command 1111 1100
  SPI.transfer(0xFC);
  delayMicroseconds(10);

  //WAKEUP 0000 0000
  SPI.transfer(0x00);
  delayMicroseconds(10);

  SPI.transfer(0x01); // Read Data 0000  0001 (01h)
  delayMicroseconds(10);

  adc_val = SPI.transfer(0);
  adc_val <<= 8; //shift to left
  adc_val |= SPI.transfer(0);
  adc_val <<= 8;
  adc_val |= SPI.transfer(0);

  //The ADS1255/6 output 24 bits of data in Binary Two’s
  //Complement format. The LSB has a weight of
  //2VREF/(PGA(223 − 1)). A positive full-scale input produces
  //an output code of 7FFFFFh and the negative full-scale
  //input produces an output code of 800000h.
  if (adc_val > 0x7fffff) { //if MSB == 1
    adc_val = 16777216ul - adc_val; //do 2's complement, discard sign
  }
  
  delayMicroseconds(10);
   
  digitalWrite(ADS_CS_PIN, HIGH);
  delayMicroseconds(50);
  SPI.endTransaction();

  Serial.print("Got measurement from ADS ");
  Serial.println(adc_val);

  return adc_val;
}

long readADSDiff(byte positiveCh, byte negativeCh) {
  long adc_val = 0; // unsigned long is on 32 bits

  digitalWrite(ADS_CS_PIN, LOW);
  delayMicroseconds(50);
  SPI.beginTransaction(SPISettings(ADS_SPISPEED, MSBFIRST, SPI_MODE1));
  delayMicroseconds(10);
  
  while (digitalRead(ADS_RDY_PIN)) {} ;

  byte data = (positiveCh << 4) | negativeCh; //xxxx1000 - AINp = positiveCh, AINn = negativeCh
  SPI.transfer(0x50 | 1); // write (0x50) MUX register (0x01)
  SPI.transfer(0x00);   // number of registers to be read/written − 1, write one register only
  SPI.transfer(data);   // write the databyte to the register
  delayMicroseconds(10);

  //SYNC command 1111 1100
  SPI.transfer(0xFC);
  delayMicroseconds(10);

  //WAKEUP 0000 0000
  SPI.transfer(0x00);
  delayMicroseconds(10);

  SPI.transfer(0x01); // Read Data 0000  0001 (01h)
  delayMicroseconds(10);

  adc_val = SPI.transfer(0);
  adc_val <<= 8; //shift to left
  adc_val |= SPI.transfer(0);
  adc_val <<= 8;
  adc_val |= SPI.transfer(0);

  delayMicroseconds(10);

  digitalWrite(ADS_CS_PIN, HIGH);
  delayMicroseconds(50);

  if (adc_val > 0x7fffff) { //if MSB == 1
    adc_val = adc_val - 16777216; //do 2's complement, keep the sign this time!
  }
  Serial.print("Got diff measurement from ADS ");
  Serial.println(adc_val);

  return adc_val;
}
