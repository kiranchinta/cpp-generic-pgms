/*
 * Program that takes in a decimal integer value and prints the +ve and -ve(2's
 * complement) binary form
 *
 * ./printTwosComplement 3
 * Input (decimal): 3
 * Positve integer value:  00000000000000000000000000000011
 * Negetive integer value: 11111111111111111111111111111101
 *
 * ./printTwosComplement 1024
 * Input (decimal): 1024
 * Positve integer value:  00000000000000000000010000000000
 * Negetive integer value: 11111111111111111111110000000000
 *
 */

#include <iostream>

using namespace std;

void printUsage(char* pgmName)
{
   cout << "Program that takes in a decimal integer value and prints the +ve and -ve(2's complement) binary form" << endl;
   cout << "Usage: " << pgmName << " IntNum" << endl;
   // Note: By default int is a signed int here.
   cout << "Input number should be inbetween 0 and 2147483647" << endl;
}

int main(int argc, char** argv)
{
   if (argc != 2)
   {
      printUsage(argv[0]);
      return 0;
   }

   // Note: By default int is a signed int here.
   int *posnum = new int(atoi(argv[1]));

   // Any number greater than 2147483647 will be a -ve number here
   if (*posnum < 0 )
   {
      printUsage(argv[0]);
      return 0;
   }

   signed int *negnum = new signed int(-*posnum);

   cout << "Input (decimal): " << *posnum << endl;
   cout << "Positve integer value:  " << std::bitset<32>(*posnum) << endl;
   cout << "Negetive integer value: " << std::bitset<32>(*negnum) << endl;

   delete posnum;
   delete negnum;
}
