/* crcNTest.ino
 * Script that tests the behavior of the crcN library
 */

#include <crcN.h>

int data_test = 3387; // 0b110100111011, 0xD3B
int data_length_test = 12;
int crc_length_test = 4;
int pkt_test;
// for this test case the answer should be 0b1101001110110110,
//  0d54198

void setup() {
  Serial.begin(9600);  
  pkt_test = crcN(data_test, data_length_test, crc_length_test);
  Serial.print("The data is ");
  Serial.println(data_test);
  Serial.print("The compiled packet is ");
  Serial.println(word(pkt_test));
}

void loop() {
  
}
