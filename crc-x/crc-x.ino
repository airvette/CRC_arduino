// Script to test the crc_x function

int data_test = 3387; // 0b110100111011, 0xD3B
int data_length_test = 12;
int crc_length_test = 4;
int telem_test;
// for this test case the answer should be 0b1101001110110110,
//  0d54198

void setup() {
  // put your setup code here, to run once:
  telem_test = crc_x(data_test, data_length_test, crc_length_test);  
} // end setup

void loop() {
  // put your main code here, to run repeatedly:
  // print telem_test to whateve monitor is being used (serial or LCD)
} // end loop

// This function has been tested to work for CRC-4 calculations.
//  Need to test for other crc lengths and write polynomial array values into function
int crc_x (int data, int data_length, int crc_length){
  // int data; // user defined data field
  int telem; // telem field, includes user defined data and x-bit crc
  //MODIFIY FOLLOWING CODE BEFORE POSTING TO FORUMS
  int poly = 19; // 5-bit polynomial that is used to create the 4-bit crc
  // the value 0d19 is equivalent to the standard crc representations of 0x3 (normal), 0xC (reversed) or
  //  0x9 (koonman); all are equal to the polynomail of x^4 + x^1 + 1 or 0b10011: https://en.wikipedia.org/wiki/Cyclic_redundancy_check
  int crc_polys[] = {-1, -1, -1, 0x5, 0x9, 0x12, 0x33, 0x65, 0xE7, 0x119, 0x327, 0x5DB, 0x987, 0x1ABF, 0x27CF, 0x4F23,
                0x8D95, 0x16FA7, 0x23979, 0x6FB57, 0xB5827, 0x1707EA, 0x308FD3, 0x540FD0, 0x8F90E3, 0x101690C, 
                0x33C19EF, 0x5E04635, 0x91DC1E3}; // declare the array that holds crc polynomials of bit size 3-28
                 // index number correspondends to bit size, "-1" in the first three cells are invalid selections.
                 //  if a "-1" is selected, the code defaults to index 3 or 0x5
                 // these polynomials are recommended by P. Koopman of Carnegie Mellon Univ
                 // https://users.ece.cmu.edu/~koopman/crc/#notation
  poly = (crc_polys[crc_length]<<1) + 1; // shift poly and add one to place it into a format usable by Arduino
  //END MODIFY SECTION
  int const poly_length = crc_length+1; // length of the crc polynomial
  int const telem_length = data_length + crc_length; // length of the telem field

  int tmp_telem = data << crc_length; // 16-bit working telem field, used to calculate the telem
  int tmp_quot; // 5-bit quotient for the intermediate steps in calculating the CRC
  
  // for loop starting with the MSB and working towards the LSB.  For a 16-bit telem and a 5-bit poly, 
  //  the index goes from 15 (MSB) to 4 (LSB+5)
  for (int i = telem_length-poly_length; i >= 0; i--){
    if (bitRead(tmp_telem, (i+poly_length-1)) == 1) // if the MSB of the selected telem subset is a 1
    {
      // then operate on that subset
      tmp_quot = (tmp_telem >> i) ^ poly; // for the current position divide the poly
      // next set all the more significant bits to zero in preparation for a bitwise AND
      for (int j = i; j <= telem_length-1; j++)
      {
        bitClear(tmp_telem, j);
      } // end for
      tmp_telem = tmp_quot << i | tmp_telem; // bitwise OR to prep the next iteration of the crc calculation
    } // end if
  } // end for

  // at the end of the for loop the output is the CRC code in the tmp_telem var 
  // next combine data with CRC to get the telemetry field
  return telem = (data << crc_length) | tmp_telem; // the final telem value
} // end crc_x

