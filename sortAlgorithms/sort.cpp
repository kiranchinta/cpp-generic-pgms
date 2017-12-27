// Author: Kiran Chinta
// For usage, see printUsage() below
// A summary of a number of different sorting algorithms can be found here
// https://en.wikipedia.org/wiki/Sorting_algorithm

#include <iostream>
#include <assert.h>
#include <vector>
#include <utility> // std::swap
#include <csignal> // std::signal
#include <execinfo.h> // For backtrace
#include <unistd.h> // For STDERR_FILENO
#include <time.h> // For clock
#include <fstream>      // std::ifstream
#include <valarray>     // std::valarray

using namespace std;

// For debug purpose
// #define PGM_DEBUG_DETAILED 1
// #define PGM_DEBUG 1

namespace
{
   volatile std::sig_atomic_t gSignalStatus;
}

void printUsage(char* pgmName)
{
      cout << "Input: A file containing a list of integers OR a list of integers separated by space" << endl;
      cout << "This program sorts a list of integers using the below sort algorithms and prints the time taken for each sort algorithm" << endl;
      cout << " std::sort\n AiHaSort\n RadixSort\n MergeSort\n QuickSort\n InsertionSort\n SelectionSort\n BubbleSort\n" << endl;
      cout << "Usage 1: " << pgmName << " list_of_integers_(minimum_two_integers)  (example: " << pgmName << " 10 9 8 7)" << endl;
      cout << "Usage 2: " << pgmName << " $fileName_containing_list_of_integers_1perRow (example: " << pgmName << " file1)" << endl;
}

void signalHandler(int signal)
{
   void *array[10];
   size_t size;

   // get void* of all entries in the stack
   size = backtrace(array,10);

   backtrace_symbols_fd(array, size, STDERR_FILENO);

   cout << "Handling signal " << signal << gSignalStatus << endl;
   gSignalStatus = signal;

   exit(EXIT_FAILURE);
}

void printVectorElements(std::vector<int> const &sortVec)
{
   cout << "Vector elements: " ;
   for (std::vector<int>::const_iterator it = sortVec.begin(); it != sortVec.end(); it++)
   {
      cout << *it << " " ;
   }
   cout << endl;
}

bool testSort(std::vector<int> const &vec1, std::vector<int> const &vec2)
{
   assert(vec1.size() == vec2.size());

   bool resMatch = true;

   for (int i=0; i < vec1.size(); i ++)
   {
      if (vec1[i] != vec2[i])
      {
         resMatch = false;
      }
   }

   return resMatch;
}

// AiHa sort (pronounced Aye-ha): Allocate a temporary structure from 0 to max
// value in the input list. Walking from first element in the input list to
// last element in the input list, increment the corresponding index counter
// for each value in the input list. Next, go through this temporary structure
// from 0th index to the max index, then write that index value into the output
// array the number of times tracked by the counter.
// Runtime: O(n)
// Memory: O(n)
//
// My own sorting algorithm, AiHa sort (pronounced Aye-ha)
// Characteristics: 
//   [a] Non comparison sort
//   [b] Not a stable sort since the relative ordering of duplicate elements
//       is not preserved.
//   [c] Not an in-place sort as it uses additional vector to store meta data
//   [d] Time complexity is O(n), max runtime is 3n + time for memory
//   allocations for the temporary vector.  
//   [e] A counting sort that is suited
//   for an array of integer numbers.
//   [f] Memory: O(n)
void AiHaSort(std::vector<int> &AiHaSortVec)
{
#ifdef PGM_DEBUG_DETAILED
    cout << "\nEntering AiHa sort: \n" ;
#endif

   int max = 0;

   // TODO: Improvement: You can also gather the min and only allocate a vector
   // of pairs of the size of (max - min). This way if the min and max are far
   // apart, we can save ourself from the unnecessary long vector allocation.
   //
   // Find the max
   for (int i=0; i < AiHaSortVec.size(); i++)
   {
      if (AiHaSortVec[i] > max)
      {
         max = AiHaSortVec[i];
      }
   }

   // Initialize all to false.
   //
   // After testing with std::vector and std:valarray, performance seems to be
   // better when valarray is used. Reading on the web, valarray seems to be
   // intended for optimized performance for some vectorized processing of
   // arrays (like done in FORTRAN) which never happened.
   //
   // std::vector<int> valExists(max+1, 0);
   //
   // valarray constructor takes in arguments in a different order compared to
   // std::vector, bit odd.
   // valarray (const T& val, size_t n);
   std::valarray<int> valExists(0, max+1);

   // Test performance using dynarray, the memory
   // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3662.html
   // std::dynarray<int> valExists(max+1, 0);

   for (int i=0; i <= AiHaSortVec.size() - 1; i++)
   {
      // Keep a count of duplicates
      valExists[AiHaSortVec[i]]++;
   }

   for (int i=0, j =0; i <= max; i++)
   {
      for (int k=0; k < valExists[i]; k++)
      {
         AiHaSortVec[j] = i;
         j++;
      }
   }

#ifdef PGM_DEBUG_DETAILED
    cout << "\nExiting AiHa sort: \n" ;
#endif
}

// Counting sort: Count the number of objects that have each distinct key
// values, use arithmetic on those counts to determine the positions of each
// key value in the output sequence
// Runtime: O(n)
// Memory: O(n + range)
void countingSort(std::vector<int> &countingSortVec) 
{
#ifdef PGM_DEBUG_DETAILED
         cout << "\nEntering countingSort: \n" ;
#endif

   int max = 0;
   int inputSize = countingSortVec.size();

   // Find the max
   for (int i=0; i < inputSize; i++)
   {
      if (countingSortVec[i] > max)
      {
         max = countingSortVec[i];
      }
   }

   // Initialize all to false.
   //
   // After testing with std::vector and std:valarray, performance seems to be
   // better when valarray is used. Reading on the web, valarray seems to be
   // intended for optimized performance for some vectorized processing of
   // arrays (like done in FORTRAN) which never happened.
   //
   // std::vector<int> valExists(max+1, 0);
   //
   // valarray constructor takes in arguments in a different order compared to
   // std::vector, bit odd.
   // valarray (const T& val, size_t n);
   std::valarray<int> valExists(0, max+1);

   // Test performance using dynarray, the memory
   // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3662.html
   // std::dynarray<int> valExists(max+1, 0);

   // Calculate the histogram of key frequencies
   for (int i=0; i < inputSize; i++)
   {
      valExists[countingSortVec[i]]++;
   }

   // Calculate the starting index for each key
   for (int i=1; i <= max; i++)
   {
      valExists[i] += valExists[i-1];
   }

   std::vector<int> tempVec(inputSize, 0);

   // Copy the integer to temp array, preserving order of inputs with equal
   // values
   for (int i = inputSize -1; i >= 0; i--)
   {
      // Index is 0 based, count is 1 based
      valExists[countingSortVec[i]]--;
      tempVec[valExists[countingSortVec[i]]] = countingSortVec[i];

#ifdef PGM_DEBUG_DETAILED
      cout << "Iterating in For Loop\n" ;
      printVectorElements(tempVec);
#endif
   }

#ifdef PGM_DEBUG_DETAILED
   cout << "Out of For Loop\n" ;
#endif

   // Copy the tempVec to input Vec
   for (int i = 0; i < inputSize; i++)
   {
      countingSortVec[i] = tempVec[i];
   }

#ifdef PGM_DEBUG_DETAILED
    cout << "Iterating in While Loop\n" ;
    printVectorElements(countingSortVec);
    cout << "\nExiting countingSort: \n" ;
#endif
}

// Radix sort: Iterate through each k'th digit(k being the same signigicant
// position, starting from pos 0) grouping numbers by each digit. I have
// used counting sort to sort the numbers at each position.
// Runtime: O(nk) (k: number of digits in the max key)
// Memory: O(n)
void radixSort(std::vector<int> &radixSortVec) 
{
#ifdef PGM_DEBUG_DETAILED
         cout << "\nEntering Radix sort: \n" ;
#endif

   int max = 0;
   int inputSize = radixSortVec.size();

   // Find the max
   for (int i=0; i < inputSize; i++)
   {
      if (radixSortVec[i] > max)
      {
         max = radixSortVec[i];
      }
   }

   int digitPos = 1;
   std::vector<int> tempVec(inputSize, 0);

   // If the max number consists of 'k' digits then we will have to make 'k'
   // passes through all the numbers and 'k' sorts
   while ( max/digitPos > 0 )
   {
      int alphabetCount[10] = {0};

      // Calculate the histogram of key frequencies in the respective digitPos
      // location
      for (int i=0; i < inputSize; i++)
      {
         alphabetCount[(radixSortVec[i]/digitPos) % 10]++;
      }

      // Calculate the starting index for each key
      for (int i=1; i < 10; i++)
      {
         alphabetCount[i] += alphabetCount[i-1];
      }

      // Copy the integer to temp array, preserving order of inputs with equal
      // values
      for (int i = inputSize -1; i >= 0; i--)
      {
         // Index is 0 based, count is 1 based
         alphabetCount[(radixSortVec[i]/digitPos) % 10]--;
         tempVec[alphabetCount[(radixSortVec[i]/digitPos) % 10]] = radixSortVec[i];

#ifdef PGM_DEBUG_DETAILED
         cout << "Iterating in For Loop\n" ;
         printVectorElements(tempVec);
#endif
      }

#ifdef PGM_DEBUG_DETAILED
      cout << "Out of For Loop\n" ;
#endif

      // Copy the tempVec to input Vec
      for (int i = 0; i < inputSize; i++)
      {
         radixSortVec[i] = tempVec[i];
      }

#ifdef PGM_DEBUG_DETAILED
    cout << "Iterating in While Loop\n" ;
    printVectorElements(radixSortVec);
#endif

      digitPos *= 10;
   }

#ifdef PGM_DEBUG_DETAILED
         cout << "\nExiting Radix sort: \n" ;
#endif
}

void merge(std::vector<int> &mVec, std::vector<int> &tempVec, int start, int
      middle, int end)
{
   // First copy all the vector elements to the temp vector since we will be
   // overwriting the mVec with sorted elements.
   for (int i = start; i <= end; i++)
   {
      tempVec[i] = mVec[i];
   }

   int mVecCurrent = start;
   int leftHalfStart = start;
   int rightHalfStart = middle +1;

   while (leftHalfStart <= middle && rightHalfStart <= end)
   {
      if (tempVec[leftHalfStart] <= tempVec[rightHalfStart])
      {
         mVec[mVecCurrent] = tempVec[leftHalfStart];
         leftHalfStart++;
      }
      else
      {
         mVec[mVecCurrent] = tempVec[rightHalfStart];
         rightHalfStart++;
      }

      mVecCurrent++;
   }

   int remLeft = middle - leftHalfStart;

   while (remLeft >= 0 )
   {
      mVec[mVecCurrent] = tempVec[leftHalfStart];
      mVecCurrent++;
      leftHalfStart++;
      remLeft--;
   }
}

void mergeSortElements(std::vector<int> &mVec, std::vector<int> &tempVec, int start, int end)
{
   if (start < end)
   {
      int middle = (start + end)/2;
      // MergeSort the left half
      mergeSortElements(mVec, tempVec, start, middle);
      // MergeSort the right half
      mergeSortElements(mVec, tempVec, middle + 1, end);
      // Now merge these two halfs
      merge(mVec, tempVec, start, middle, end);
   }
}

// Merge sort: Divide the list of numbers into two halfs, sort each half and
// merge them back together in sorted order. Each of the half recursively
// applies the same sorting algorithm.
// Runtime: O(n log n)
// Memory:  O(n)
void mergeSort(std::vector<int> &mergeVec)
{
   std::vector<int> tempVec(mergeVec.size());

   mergeSortElements(mergeVec, tempVec, 0, mergeVec.size() - 1);

#ifdef PGM_DEBUG_DETAILED
    printVectorElements(mergeVec);
#endif
}

int quickSortPartitionAndReorder(std::vector<int> &qv, int left, int right)
{
   // this can be any element, let's just pick the middle position
   int pivot = (left+right)/2;
   int pivotVal = qv[pivot];

   while (left <= right)
   {
      // Find the element on the left side that is greater than pivotVal
      while(qv[left] < pivotVal)
      {
         left++;
      }

      // Find the element on the right side that is smaller than pivotVal
      while(qv[right] > pivotVal)
      {
         right--;
      }

      // Now swap the left element with the right element
      if (left <= right)
      {
         std::swap(qv[left], qv[right]);
         left++;
         right--;
      }
   }
   return left;

}

// Quick sort: Pick a random element (pivot) in the list and partition the
// list, reorder the array so that all elements less than pivot come to the
// left of pivot and all elements greater than the pivot come to the right of
// pivot. Recursively apply the same logic to the sub-arrays of elements on the
// left and to the sub-array of elements to the right.
// Runtime: Average case - O(n log n) , Worst case - O(n^2)
// Memory: O(1)
void quickSort(std::vector<int> &quickVector, int left, int right)
{
   int pivot = quickSortPartitionAndReorder(quickVector, left, right);
   
   if (left < pivot -1)
   {
      // Sort elements on the left of the pivot
      quickSort(quickVector, left, pivot-1 );
   }

   if (pivot < right)
   {
      // sort elements on the right of the pivot
      quickSort(quickVector, pivot, right);
   }

#ifdef PGM_DEBUG_DETAILED
    printVectorElements(quickVector);
#endif
}

// Insertion sort: Start from the top+1 element and insert it in the sorted
// order in the list above it. Then take the top most + 2 element and insert in
// the sorted order in the list above it. Continue doing this until you've
// inserted the last element in the input list. You are basically picking up a
// new element and inserting it in the sorted order. On how you find the
// position to insert can be improved by various other search algorithms. The
// below pgm does a linear search.
// Runtime: O(n^2)
// Memory: O(1)
void insertionSort(std::vector<int> & insVec)
{
   // Look until size-1 since in insertion sort we look 1+i
   for (int i=0; i < insVec.size() - 1; i++)
   {
      for (int j=i+1; j > 0 ; j--)
      {
         if (insVec[j] < insVec[j-1])
         {
            std::swap(insVec[j], insVec[j-1]);
         }
      }
   }

#ifdef PGM_DEBUG_DETAILED
    printVectorElements(insVec);
#endif
}

// Selection sort: Find the smallest element using a linear scan and move it to
// the front. Then find the second smallest and move to the second position.
// Continue doing this until the entire list is sorted.
// Runtime: O(n^2)
// Memory:: O(1)
void selectionSort(std::vector<int> &selVec)
{
   int min;
   int minPos;

   for (int i=0; i < selVec.size(); i++)
   {
      min = selVec[i];
      minPos = i;

      for (int j=i+1; j < selVec.size(); j++)
      {
         if (selVec[minPos]  > selVec[j])
         {
            minPos = j;
         }
      }

      std::swap(selVec[i], selVec[minPos]);
   }

#ifdef PGM_DEBUG_DETAILED
    printVectorElements(selVec);
#endif
}

// Bubble sort: Start at the beginning of the array, compare the first two
// elements and swap based on the comparison performed. Then move to the next
// pair of elements, compare and swap as necessary. Continue doing this until
// the entire array is sorted. 
// Runtime: O(n^2)
// Memory:: O(1)
void bubbleSort(std::vector<int> &bubVec)
{

#ifdef PGM_DEBUG_DETAILED
   cout << "\nIn Bubble sort: " << endl;
   printVectorElements(bubVec);
#endif

   for (int i=0; i < bubVec.size(); i++)
   {
      for (int j=1; j < bubVec.size() - i; j++)
      {
         if (bubVec[j-1] > bubVec[j])
         {
            std::swap(bubVec[j-1], bubVec[j]);
         }
      }
   }

#ifdef PGM_DEBUG_DETAILED
    printVectorElements(bubVec);
#endif
}

int main(int argc, char* argv[])
{
   bool testStatus = true;
   clock_t timeStart;
   clock_t timeEnd;

   // strncmp returns 0 if the strings are same. So use a !
   if (argc < 2 || !strncmp(argv[1],"-h",strlen(argv[1])) || !strncmp(argv[1],"-help",strlen(argv[1])))
   {
      printUsage(argv[0]);
      return 0;
   }

   std::signal(SIGABRT, signalHandler);
   std::signal(SIGSEGV, signalHandler);

   std::vector<int> inList;
   size_t arraySize = 0;


   // Input is a file name containing integers
   if (argc == 2)
   {
      std::ifstream input(argv[1], std::ifstream::in);
      int val;

      if (input.is_open())
      {
         while (input >> val)
         {
            inList.push_back(val);
            arraySize++;
         }
      }
      else
      {
         printUsage(argv[0]);
         return 0;
      }
   }
   else
   {
      arraySize = argc -1;
#ifdef PGM_DEBUG_DETAILED
      cout << "         ";
#endif
      for(int i=0; i < arraySize; i++)
      {
#ifdef PGM_DEBUG_DETAILED
         cout << argv[i+1] << " ";
#endif
         inList.push_back(atoi(argv[i+1]));
      }
#ifdef PGM_DEBUG_DETAILED
      cout << endl;

      cout << "Size of the input array: " << inList.size() << endl;
#endif
   }

   assert(arraySize == inList.size());

#ifdef PGM_DEBUG_DETAILED
   printVectorElements(inList);
#endif

   // Let's sort using std::sort to later test our sorting output.  First copy
   // the inList array to a stdsortVector since std::sort sorts the elements
   // inline
   std::vector<int> stdsortVector(inList);
   cout << "clocks ticks per second: " << CLOCKS_PER_SEC << endl;
   timeStart = clock();
   std::sort(stdsortVector.begin(), stdsortVector.end());
   timeEnd = clock();
   cout << "\nTime taken by std::sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
#ifdef PGM_DEBUG
   cout << "\nSorted Elements by std: " << endl;
   printVectorElements(stdsortVector);
#endif

   // My own sorting algorithm, AiHa sort (pronounced Aye-ha)
   // Characteristics: 
   //   [a] Non comparison sort
   //   [b] Not a stable sort since the relative ordering of duplicate elements
   //       is not preserved.
   //   [c] Not an in-place sort as it uses additional vector to store meta data
   //   [d] Time complexity is O(n) , max runtime is 3n + time for memory
   //   allocations for the temporary vector.
   //   [e] A counting sort that is
   //   suited for an array of integer numbers.
   //   [f] Memory: O(n)
   std::vector<int> AiHaSortVector(inList);
   timeStart = clock();
   AiHaSort(AiHaSortVector);
   timeEnd = clock();
   cout << "\nTime taken by AiHa Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,AiHaSortVector))
   {
      cout << "\nAiHa Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(AiHaSortVector);
#endif
      testStatus = false;
   }

   // Counting sort
   std::vector<int> countingSortVector(inList);
   timeStart = clock();
   countingSort(countingSortVector);
   timeEnd = clock();
   cout << "\nTime taken by counting Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,countingSortVector))
   {
      cout << "\ncounting Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(countingSortVector);
#endif
      testStatus = false;
   }

   // Radix sort
   std::vector<int> radixVector(inList);
   timeStart = clock();
   radixSort(radixVector);
   timeEnd = clock();
   cout << "\nTime taken by Radix Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,radixVector))
   {
      cout << "\nRadix Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(radixVector);
#endif
      testStatus = false;
   }

   // Merge sort
   std::vector<int> mergeVector(inList);
   timeStart = clock();
   mergeSort(mergeVector);
   timeEnd = clock();
   cout << "\nTime taken by Merge Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,mergeVector))
   {
      cout << "\nMerge Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(mergeVector);
#endif
      testStatus = false;
   }

   // Quick sort
   std::vector<int> quickVector(inList);
   timeStart = clock();
   quickSort(quickVector, 0, quickVector.size()-1);
   timeEnd = clock();
   cout << "\nTime taken by Quick Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,quickVector))
   {
      cout << "\nQuick Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(quickVector);
#endif
      testStatus = false;
   }

   // Insertion sort
   std::vector<int> insVector(inList);
   timeStart = clock();
   insertionSort(insVector);
   timeEnd = clock();
   cout << "\nTime taken by Insertion Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,insVector))
   {
      cout << "\nInsertion Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(insVector);
#endif
      testStatus = false;
   }

   // Selection sort
   std::vector<int> selectionVector(inList);
   timeStart = clock();
   selectionSort(selectionVector);
   timeEnd = clock();
   cout << "\nTime taken by Selection Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,selectionVector))
   {
      cout << "\nSelection Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(selectionVector);
#endif
      testStatus = false;
   }

   // Bubble sort
   std::vector<int> bubbleVector(inList);
   timeStart = clock();
   bubbleSort(bubbleVector);
   timeEnd = clock();
   cout << "\nTime taken by Bubble Sort: " << timeEnd - timeStart << " clicks,  " << (timeEnd - timeStart)*1.0/CLOCKS_PER_SEC << " seconds" << endl;
   if (!testSort(stdsortVector,bubbleVector))
   {
      cout << "\nBubble Sort sorted incorrectly" << endl;
#ifdef PGM_DEBUG
      printVectorElements(bubbleVector);
#endif
      testStatus = false;
   }


   // Heap sort

   // Timsort

   // Print the test outcome
   std::string str(testStatus?"Passed":"Failed" );
   cout << "\n\n Test " << str << endl;
   
   return 0;
}
