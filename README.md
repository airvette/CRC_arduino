# CRC_arduino
This repo contains an Arduino code library providing the capability to develop a Cyclic Redundancy Check (CRC) suffix for I2C (or any) communication between an Arduino and a non-Arduino.  I originally created this library as a way to perform a CRC-4 checksum for a personal project, but found that it wasn't easy to find CRC options that used the Arduino functionality.  After I got the CRC-4 code to work, I jumped down the rabbit hole and put some effort into expanding the capabilities of the core algorithm so that it could accept a data input of any length (limited by memory, of course) as long as it was formatted as an array of 16-bit integers.  

The library accepts instructions to create CRCs of length anywhere between 3 and 15 bits.  This range was set based on a desire to keep the code simple and not over utilize the limited Arduino memory.  Essentially, when a CRC grows to be more than 15 bits, two integers in memory are needed to track the CRC calculations.  The CRC polynomials are preset in the function and are selected based on the bit length of the CRC.  One can reference P. Koopman (http://users.ece.cmu.edu/~koopman/crc/) for the source of the polynomials chosen.

To use this library, the function call for `crcN()` is:

`unsigned int crc = crcN (data, sizeof(data)/2, crc_length);`

Where:
- `crc` = the crc suffix returned by `crcN()`
- `data` = a 16-bit scalar or an array of 16-bit integers.  It is up to the user to format their data so that it meets this format constraint.
- `sizeof(data)/2` = the number of elements in the array.  The function `sizeof()` returns the number of bytes in the referenced variable.  Dividing this result yields the number of 16-bit integers
- `crc_length` = the desired length of the crc suffix.  The code will correct for it, but the values need to be between 3 and 15

This is my first attempt at creating code for the Arduino community, so any feedback is welcome!
