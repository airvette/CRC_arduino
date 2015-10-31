/* crcN.h
 * A simple library containing code to calculate the cyclic redundancy check (crc)
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
#include "crcN.h"

int crcN (int data, int data_length, int crc_length)
{
  int pkt; // pkt field, includes user defined data and x-bit crc
  int crc_polys[] = {-1, -1, -1, 0x5, 0x9, 0x12, 0x33, 0x65, 0xE7, 0x119, 0x327,
      0x5DB, 0x987, 0x1ABF, 0x27CF, 0x4F23, 0x8D95, 0x16FA7, 0x23979, 0x6FB57,
      0xB5827, 0x1707EA, 0x308FD3, 0x540FD0, 0x8F90E3, 0x101690C, 0x33C19EF,
      0x5E04635, 0x91DC1E3};
      /* declare the array that holds crc polynomials of bit size 3-28
       * index number correspondends to bit size, "-1" in the first three cells
       * are invalid selections. If a "-1" is selected, the code defaults to
       * index 3 or 0x5 these polynomials are recommended by P. Koopman of
       * Carnegie Mellon Univ: https://users.ece.cmu.edu/~koopman/crc/#notation
       */

  // Check user input to ensure crc_length is >=3 and <=28.  If it isn't, set to
  //  acceptable values
  if (crc_length < 3){ // if less than min possible crc length
    crc_length = 3; // set to min crc_length of 3
  } // end if
  if (crc_length > 28){ // if greater than min possible crc length
    crc_length = 16; // set to typical crc_length of 16
  } // end if

  // shift poly and add one to place it into a format usable by Arduino
  // see https://en.wikipedia.org/wiki/Cyclic_redundancy_check for more info
  int poly = (crc_polys[crc_length] << 1) + 1;

  int const poly_length = crc_length + 1; // length of the crc polynomial
  int const pkt_length = data_length + crc_length; // length of the pkt field

  int tmp_pkt = data << crc_length; // 16-bit working pkt field, used to calculate the pkt
  int tmp_quot; // 5-bit quotient for the intermediate steps in calculating the CRC

  // For loop starting with the MSB and working towards the LSB and stopping at
  //  the LSB plus the crc_length.  For example, a 16-bit pkt and a 5-bit poly
  //  will move the index from 15 (MSB) to 4 (LSB+5)
  for (int i = pkt_length-poly_length; i >= 0; i--){
    if (bitRead(tmp_pkt, (i+poly_length-1)) == 1) // if the MSB of the selected pkt subset is a 1
    {
      // then operate on that subset
      tmp_quot = (tmp_pkt >> i) ^ poly; // for the current position divide the poly
      // next set all the more significant bits to zero in preparation for a bitwise AND
      for (int j = i; j <= pkt_length-1; j++)
      {
        bitClear(tmp_pkt, j);
      } // end for
      tmp_pkt = tmp_quot << i | tmp_pkt; // bitwise OR to prep the next iteration of the crc calculation
    } // end if
  } // end for

  // at the end of the for loop the output is the CRC code in the tmp_pkt var
  // next combine data with CRC to get the packet field
  return pkt = (data << crc_length) | tmp_pkt; // the final pkt value
} // end crcN
