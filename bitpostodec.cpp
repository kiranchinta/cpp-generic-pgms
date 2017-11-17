// Author: Kiran Chinta

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      cout << "Usage: BITOR of the binary numbers with the respective positions(inputs) set to 1" << endl;
      cout << "Input at least one number less than 63" << endl;
   }

   unsigned long long sumNum = 0;
   unsigned long long diffNum = 0;
   unsigned long long val = 0;

   for (int i=1; i < argc; i++)
   {
      val = atoi(argv[i]);
      sumNum += 0x1ULL<<val;
   }

   cout << endl;
   cout << "Bitset after setting those bit positions: \n" << std::bitset<64>(sumNum) << endl;
   cout << "Decimal: " << sumNum << endl;
}
