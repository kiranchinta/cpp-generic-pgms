// Author: Kiran Chinta
// Problem: Given a string, find the frequency of the characters in the string.
// Limitation: Only works for strings from small a to small z

#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{

   if (argc == 1)
   {
      cout << "Input atleast one string" << endl;
      return 0;
   }

   // Ignore the name of the program
   for(int i=1; i<argc; i++)
   {
      cout << "String input: " << argv[i] ;
      cout << " length: " << strlen(argv[i]) << endl;
   }

   int count[26] = {0};

   for (int i=1; i < argc; i++)
   {
      cout << "\nFor String " << argv[i] << endl;

      for (int j=0; j < strlen(argv[i]) ; j++)
      {
         count[argv[i][j] - 'a']++;
      }

      for (int j=0; j < strlen(argv[i]) ; j++)
      {
         cout << "Count of Char: " << argv[i][j] << " is " << count[argv[i][j] - 'a'] << endl;
      }

      // Reset count array
      memset (count, 0, sizeof(count));
      
   }

   return 0;
}
