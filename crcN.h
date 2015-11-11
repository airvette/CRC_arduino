/* crcN.h
 * A simple header file containing the function prototype for calculating the
 * cyclic redundancy check (crc) as a checksum for communication between an
 * Arduino and another device.
 *
 * To make the most use of the overloaded functionality, the recommended format
 * of the function call is:
 * int crc_output = crcN(data, sizeof(data)/2, crc_length);
 * Where "data" can be a single 16-bit integer or an array of 16-bit integers.
 *
 * This function uses three variables as the input:
 * - data: This is the data for which the user desires a crc. The standard data
 *   type length is 16 bits
 * - dataSize: This is the size of the data value in number of integers (16-
 *   bits each).  For this version of crcN() the value of this variable should
 *   be some value greater than 1 and limited by the Arduino's memory. It is
 *   recommended that the Arduino function sizeof() be used as the input to this
 *   variable.
 * - crc_length: The desired length of the crc checksum.  Acceptable values are
 *   3-16.  If the value entered is less than 3, crc_length is set to three and
 *   if the number is greater than 16, the length is set to 16, which is suitable
 *   crc length for most applications that can support a two-byte crc
 * One varible is returned:
 * - crc: Short for Cyclic Reduncancy Check, a type of checksum.  It assumed
 *   that calculating the CRC will be one of the last actions before
 *   transmitting a digital packet.  The user is responsible for assembling the
 *   packet which should be made up of the input data, the crc and any other
 *   relevant info.
 *
 * Note on memory: There are two different functions below.  The standard
 *   function (crcN) uses the standard memory size of an integer (16 bits),
 *   whereas crcN utilizes the an array format for data types
 *   longer than 16 bits.
 */

 #include "Arduino.h"

 unsigned int crcN (unsigned int data, int dataSize, int crc_length);
 unsigned int crcN (unsigned int data[], int dataSize, int crc_length);
