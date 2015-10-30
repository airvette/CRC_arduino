/* crcN.h
 * A simple header file containing the function prototype for calculating the
 * cyclic redundancy check (crc)
 * as a checksum for communication between an Arduino and another device.
 * This function uses three variables as the input:
 * - data: This is the data for which the user desires a crc
 * - data_length: This is the length of the data in bits.  This value could be
 *   derived from the data type and MSB of the data varible, but was not
 *   implemented in this version.
 * - crc_length: The desired length of the crc checksum.  Acceptable values are
 *   3-28.  If the value entered is less than 3, crc_length is set to three and
 *   if the number is greater than 28, the length is set to 16, which is suitable
 *   crc length for most applications that can support a two-byte crc
 * One varible is returned:
 * - pkt: Short for packet.  It assumed that calculating the CRC will be one of
 *   the last actions before transmitting a digital packet, so packet was the
 *   chosen name.  The packet is made up of the input data and the crc, which is
 *   added as a suffix
 */

 #include "Arduino.h"

 int crcN (int data, int data_length, int crc_length);