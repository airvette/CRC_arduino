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
unsigned int data_long_test[] = {0xE1, 0xF3, 0xCA, 0xFE, 0x53, 0xA2};

/*
int data_32_test[] = {0b10000110110101110110111000011111, //2262265375, 0x86D76E1F
                      0b01100011101111101011010110011110, //1673442718, 0x63BEB59E
                      0b00010011110001110010010111001101, // 331818445, 0x13C725CD
                      0b00000000011111000111011010011111};//   8156831,   0x7C769F

int data_length_test[] = {32, 31, 29, 23};
*/
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
      crc_test = crcN(data_16_test[j], crc_length_test);
      Serial.print("The crc length is ");
      Serial.println(crc_length_test);
      Serial.print("The data is ");
      Serial.println(data_16_test[j], HEX);
      Serial.print("The compiled packet is ");
      Serial.println(crc_test, BIN);
      Serial.println();
    } // end nested for
  } // end for

  // Long format test
  crc_test = crcN(data_long_test, 5);
  Serial.print("The crc length is ");
  Serial.println(5);
  Serial.print("The data is ");
  Serial.print(data_long_test[0], HEX);
  Serial.print(data_long_test[1], HEX);
  Serial.println(data_long_test[2], HEX);
  Serial.print("The compiled packet is ");
  Serial.println(crc_test, BIN);
  Serial.println();
}

void loop() {
  
}
