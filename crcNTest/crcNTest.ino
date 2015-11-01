/* crcNTest.ino
 * Script that tests the behavior of the crcN library
 */

#include <crcN.h>

//int data_test = 3387; // 0b110100111011, 0xD3B
//int data_length_test = 12;
//int crc_length_test = 4;
int pkt_test;
// for this test case the answer should be 0b1101001110110110,
//  0d54198

int data_32_test[] = {0b10000110110101110110111000011111, //2262265375, 0x86D76E1F
                      0b01100011101111101011010110011110, //1673442718, 0x63BEB59E
                      0b00010011110001110010010111001101, // 331818445, 0x13C725CD
                      0b00000000011111000111011010011111};//   8156831,   0x7C769F

int data_length_test[] = {32, 31, 29, 23};

void setup() {
  Serial.begin(9600);  
  for(int crc_length_test = 3; crc_length_test<=16; crc_length_test++){
    for (int j = 0; j<=3; j++){
      pkt_test = crcN(data_32_test[j], data_length_test[j], crc_length_test);
      Serial.print("The crc length is ");
      Serial.println(crc_length_test);
      Serial.print("The data is ");
      Serial.println(data_32_test[j], HEX);
      Serial.print("The compiled packet is ");
      Serial.println(pkt_test, BIN);
    } // end nested for
  } // end for
}

void loop() {
  
}
