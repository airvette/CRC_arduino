/* crcNTest.ino
 * Script that tests the behavior of the crcN library
 */

#include <crcN.h>

unsigned int crc_test;
/*
int data_test = 3387; // 0b110100111011, 0xD3B
int data_length_test = 12;
int crc_length_test = 4;
// for this test case the answer should be 0b1101001110110110,
//  0d54198
*/

unsigned int data_16_test[] = {0x6E1F, 0xB59E, 0x25CD, 0x69F};
//unsigned int data_long_test[] = {0xE1F3, 0xC579};
unsigned int data_long_test[] = {0x21F3, 0x4C82, 0x552F, 0xAD5C};
unsigned int crc_long_test = 8;

void setup() {
  Serial.begin(9600);  

  /*
  // Single case test script
  pkt_test = crcN(data_test, data_length_test, crc_length_test);
  Serial.print("The crc length is ");
  Serial.println(crc_length_test);
  Serial.print("The data is ");
  Serial.println(data_test, HEX);
  Serial.print("The CRC is ");
  Serial.println(pkt_test, BIN);
  */
  
  // Multiple case test script
  for(int crc_length_test = 3; crc_length_test<=5; crc_length_test++){
    for (int j = 0; j<=3; j++){
      crc_test = crcN(data_16_test[j], 1, crc_length_test);
      Serial.print("The crc length is ");
      Serial.println(crc_length_test);
      Serial.print("The data is ");
      Serial.println(data_16_test[j], HEX);
      Serial.print("The CRC is ");
      Serial.println(crc_test, BIN);
      Serial.println();
    } // end nested for
  } // end for

  // Long format test
  crc_test = crcN(data_long_test, sizeof(data_long_test)/2, crc_long_test);
  Serial.print("The crc length is ");
  Serial.println(3);
  Serial.print("The data is ");
  Serial.print(data_long_test[0], HEX);
  Serial.print(data_long_test[1], HEX);
  Serial.print(data_long_test[2], HEX);
  Serial.println(data_long_test[3], HEX);
  Serial.print("The CRC is ");
  Serial.println(crc_test, BIN);
  Serial.println();
}

void loop() {
  
}
