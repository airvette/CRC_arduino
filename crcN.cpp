/* crcN.h
 * A simple library containing code to calculate the cyclic redundancy check (crc)
 * as a checksum for communication between an Arduino and another device.
 * To make the most use of the overloaded functionality, the recommended format
 * of the function call is:
 * int crc_output = crcN(data, sizeof(data)/2, crc_length);
 * Where "data" can be a single 16-bit integer or an array of 16-bit integers.
 *
 * Note on memory: There are two different functions below.  The standard
 *   function (crcN) uses the standard memory size of an integer (16 bits),
 *   whereas crcNl utilizes the long format for data types and crc checksums
 *   longer than 16 bits.  This extra capability function can handle a data input
 *   up to 32 bits and a crc as large as 28 bits with the draw back of utilizing
 *   much more memory
 */

#include "Arduino.h"
#include "crcN.h"

/* crcN (Cyclic Redundancy Check, non-array format)
 * This function uses three variables as the input:
 * - data: This is the data for which the user desires a crc. The standard data
 *   type length is 16 bits
 * - dataSize: This is the size of the data value in number of integers (16-
 *   bits each).  For this version of crcN() the value of this variable is
 *   not relevant because it is not used for the algorithm.  It is included in
 *   this version so that the format remains the same for both types of crcN().
 * - crc_length: The desired length of the crc checksum.  Acceptable values are
 *   3-15.  If the value entered is less than 3, crc_length is set to three and
 *   if the number is greater than 15, the length is set to 15, which is the max
 *   crc length for that can support a two-byte integer data type
 * One varible is returned:
 * - cksum: Short for checksum.  It assumed that calculating the CRC will be one of
 *   the last actions before transmitting a digital packet.  The user is
 *   responsible for assembling the packet which is made up of the input data,
 *   the crc and any other relevant info.
 */

unsigned int crcN (unsigned int data, int dataSize, int crc_length)
{
  unsigned int crc; // crc field, this is the output of this function
  int const memSize = 16; // constant defining the interger memory size (16 bits)
  unsigned int crc_polys[] = {-1, -1, -1, 0x5, 0x9, 0x12, 0x33, 0x65, 0xE7, 0x119, 0x327,
      0x5DB, 0x987, 0x1ABF, 0x27CF, 0x4F23};
      /* declare the array that holds crc polynomials of bit size 3-15
       * index number correspondends to bit size, "-1" in the first three cells
       * are invalid selections. If a "-1" is selected, the code defaults to
       * index 3 or 0x5. These polynomials are recommended by P. Koopman of
       * Carnegie Mellon Univ: https://users.ece.cmu.edu/~koopman/crc/#notation
       */

  // Check user input to ensure crc_length is >=3 and <=15.  If it isn't, set to
  //  acceptable values
  if (crc_length < 3){ // if less than min possible crc length
    crc_length = 3; // set to min crc_length of 3
  } // end if
  if (crc_length > 15){ // if greater than min possible crc length
    crc_length = 15; // set to typical crc_length of 15
  } // end if

  // shift poly and add one to place it into a format usable by Arduino
  // see https://en.wikipedia.org/wiki/Cyclic_redundancy_check for more info
  unsigned int poly = (crc_polys[crc_length] << 1) + 1;

  int const poly_length = crc_length + 1; // length of the crc polynomial
  unsigned int tmp_crc = data >> (memSize - poly_length); // variable size working crc field
      // field's size is determined on the size of the crc+1. Since a CRC calc
      // only works on a subset of the data input at any single time, only that
      // portion needs to be taken into account

  for (int i = memSize-1; i >= 0; i--){
    if (bitRead(tmp_crc, poly_length-1)){ // if the MSB of the working CRC val is 1
      tmp_crc = tmp_crc ^ poly; // execute the XOR calculation with the poly var
    } // end if

    // Regardless if the MSB is a 0 or 1 and the XOR calc was executed, tmp_crc
    //  needs to be prepped for the next FOR iteration if there is one
    if (i != 0){
      tmp_crc = tmp_crc << 1; // shift left to open up a new bit space
      if (i > crc_length && bitRead(data, i-crc_length-1)){
        // if tmp_crc LSB has not passed data's LSB and the next bit in the data
        //  input is a 1
        tmp_crc++; // set the tmp_crc LSB to 1, which is the same as incrementing
      } // end nested if
    } // end if
  } // end for
  return crc = tmp_crc; // return the answer
} // end crcN

/* crcN (Cyclic Redundancy Check, array format)
 * This function uses three variables as the input:
 * - data[]: This is the data for which the user desires a crc. The expected
 *   input is a data field divided up into a series of integers formatted with
 *   the most significant integer in the array's 0th index.
 *   The integers become less significant as the array index increases.
 *   For example, the data field of value E100CAFE should be formatted as
 *   data = {E100, CAFE} before this function is called
 * - dataSize: This is the size of the data value in number of integers (16-
 *   bits each).  For this version of crcN() the value of this variable should
 *   be some value greater than 1 and limited by the Arduino's memory. It is
 *   recommended that the Arduino function sizeof() be used as the input to this
 *   variable.
 * - crc_length: The desired length of the crc checksum.  Acceptable values are
 *   3-15.  If the value entered is less than 3, crc_length is set to three and
 *   if the number is greater than 15, the length is set to 15, which is the max
 *   crc length for that can support a two-byte integer data type
 * One varible is returned:
 * - cksum: Short for checksum.  It assumed that calculating the CRC will be one of
 *   the last actions before transmitting a digital packet.  The user is
 *   responsible for assembling the packet which is made up of the input data,
 *   the crc and any other relevant info.
 */

unsigned int crcN (unsigned int data[], int dataSize, int crc_length)
{
  unsigned int crc; // crc field, this is the output of this function
  int const memSize = 16; // constant defining the interger memory size (16 bits)
  Serial.println(dataSize);
  unsigned int crc_polys[] = {-1, -1, -1, 0x5, 0x9, 0x12, 0x33, 0x65, 0xE7, 0x119, 0x327,
      0x5DB, 0x987, 0x1ABF, 0x27CF, 0x4F23};
      /* declare the array that holds crc polynomials of bit size 3-15
       * index number correspondends to bit size, "-1" in the first three cells
       * are invalid selections. If a "-1" is selected, the code defaults to
       * index 3 or 0x5. These polynomials are recommended by P. Koopman of
       * Carnegie Mellon Univ: https://users.ece.cmu.edu/~koopman/crc/#notation
       */

  // Check user input to ensure crc_length is >=3 and <=15.  If it isn't, set to
  //  acceptable values
  if (crc_length < 3){ // if less than min possible crc length
    crc_length = 3; // set to min crc_length of 3
  } // end if
  if (crc_length > 15){ // if greater than min possible crc length
    crc_length = 15; // set to typical crc_length of 15
  } // end if

  // shift poly and add one to place it into a format usable by Arduino
  // see https://en.wikipedia.org/wiki/Cyclic_redundancy_check for more info
  unsigned int poly = (crc_polys[crc_length] << 1) + 1;

  int const poly_length = crc_length + 1; // length of the crc polynomial
  unsigned int tmp_crc = data[0] >> (memSize - poly_length); // variable size working crc field
      // field's size is determined on the size of the crc+1. Since a CRC calc
      // only works on a subset of the data input at any single time, only that
      // portion needs to be taken into account
  unsigned int nextInt; // init var which stores the next integer in the array

  for (int intIndex = 0; intIndex <= dataSize-1; intIndex++){
    // The following if-else block identifies if the lease significant integer
    //  in the input data field has been reached yet
    if (intIndex < dataSize-1){ // if the least-significant integer has not been reached yet
      nextInt = data[intIndex+1]; // load the next less-significant integer in
                                  // the next integer variable
    } // end if
    else { // otherwise if the least-significant integer has been reached
      nextInt = 0; // load zero into the next integer variable signifying the
                   // empty pre-crc suffix after the LSB of the data field
    }
    for (int i = memSize-1; i >= 0; i--){
      if (bitRead(tmp_crc, poly_length-1)){ // if the MSB of the working CRC val is 1
        tmp_crc = tmp_crc ^ poly; // execute the XOR calculation with the poly var
      } // end if

      //DEBUG CODE START
      Serial.print("Iteration's tmp_crc value: ");
      Serial.println(tmp_crc, BIN);
      //DEBUG CODE END

      // Regardless if the MSB is a 0 or 1 and the XOR calc was executed, tmp_crc
      //  needs to be prepped for the next FOR iteration if there is one
      //~if (i != 0){ // condition at the data field LSB
      if (i != 0 && intIndex != (dataSize-1)){ // condition at the data field LSB
        tmp_crc = tmp_crc << 1; // shift left to open up a new bit space
        if (i > crc_length && bitRead(data[intIndex], i-crc_length-1)){
          // if tmp_crc LSB has not passed data's LSB and the next bit in the data
          //  input is a 1
          tmp_crc++; // set the tmp_crc LSB to 1, which is the same as incrementing
        } // end nested if
        else if (i <= crc_length && bitRead(nextInt, memSize-1-((crc_length-1)-i))){
          // if tmp_crc LSB has passed data[intIndex]'s LSB and the next bit in
          //  data[intIndex+1] is a 1 then
          tmp_crc++; // set the tmp_crc LSB to 1, which is the same as incrementing
        } // end else if
      } // end if
    } // end nested for
  } // end for
  return crc = tmp_crc; // return the answer
} // end crcN
