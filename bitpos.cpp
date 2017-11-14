// Author: Kiran Chinta
// Prints the set bit positions for a given 64bit number. 

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
   if (argc != 2)
   {
      cout << "Incorrect number of arguments" << endl;
      cout << "Given a number(less than 9223372036854775808), outputs the bit position(s) set in binary format for that decimal number" << endl;
      cout << "Usage: " << argv[0] << " DecimalNumber" << endl;

      return 0;
   }

   char * end;
   unsigned long long num = strtoull(argv[1], &end, 10);

   cout << "Input : " << num << endl;
   cout << "Binary: " << std::bitset<64>(num) << endl;

   int pos = 0;

   while( num != 0 )
   {
      if (( num & 1) == 1)
      {
         cout << "Bit position: " << pos << " is set" << endl;
      }

      num >>= 1;
      pos++;
   }
}
