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

   for (int i=1; i < argc; i++)
   {
      sumNum += 0x1ULL<<atoi(argv[i]);
   }

   cout << "Value: " << sumNum << endl;
}
