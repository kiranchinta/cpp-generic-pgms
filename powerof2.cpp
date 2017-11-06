// Author: Kiran Chinta
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
   char * end;

   // Todo: Check the number is below less than 9223372036854775808

   // base 10
   unsigned long long i = strtoull(argv[1], &end, 10);

   cout << "Input: " << i << endl;
   cout << "Input (base 2):               " << std::bitset<64>(i) << endl;
   cout << "Input-1 (base 2):             " << std::bitset<64>(i-1) << endl;

   unsigned long long result = i&(i-1);

   cout << "Input & (Input -1), (base 2): " << std::bitset<64>(result) << endl;
   cout << "result: " << result << endl;

   //if (!(i&(i-1)))
   // If the value of result is 0 then the input is a power of 2
   if (!result)
   {
      cout << "\nTrue" << endl;
   }
   else
   {
      cout << "\nFalse" << endl;
   }
   return 0;
}
