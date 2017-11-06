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
         //cout << "Char: " << argv[i][j] << " " << int(argv[i][j]) << endl;
         //cout << "Char: " << argv[i][j] << " is " << argv[i][j] - 'a' << endl;
         count[argv[i][j] - 'a']++;
         //count[int(argv[i][j]) - int('a')]++;
      }

      for (int j=0; j < strlen(argv[i]) ; j++)
      {
         cout << "Count of Char: " << argv[i][j] << " is " << count[argv[i][j] - 'a'] << endl;
         //cout << "Count of Char: " << argv[i][j] << " is " << count[int(argv[i][j]) - int('a')] << endl;
      }

      // Reset count arrat
      memset (count, 0, sizeof(count));
      
   }

   /*
   for (int i=1; i < argc; i++)
   {
      for (int j=0; j < strlen(argv[1]) ; j++)
      {
         cout << "Char: " << argv[i][j] << " is " << count[int(argv[i][j]) - int('a')] << endl;
      }
   }
   */

   return 0;
}
