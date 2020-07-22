#include<iostream>
using namespace std;

#define SWAP(a, b) a ^= b ^= a ^= b; // beware it does not change the actual contents, it is copy
void swap(int& a , int& b)
{
  int temp; temp = a; a = b; b = temp;
}
int partitionIndex(int a[], int start ,int end)
{
  int pivot  = a[end];
  int sIndex =  start - 1; // index of smaller element
  for(int i = start; i < end; ++i)
  {
    if ( a[i] <= pivot)
    {
      ++sIndex;
      swap(a[sIndex], a[i]);
    }
  }
  int pIndex = sIndex + 1; // after loop, adding one to sIndex gives correct location of pivot element
  swap(a[pIndex], a[end]); // putting pivot element at its right location

  return pIndex ;
}

void quicksort(int a[], int start, int end)
{
  if (start < end)
  {
    int pIndex = partitionIndex(a, start, end);
    quicksort(a, start, pIndex -1);
    quicksort(a, pIndex + 1, end);
  }
}

int main()
{
 int a[] = { 4, 5, 2, 3, 6};
// char a[] = "bcaed";

  int n = sizeof(a)/sizeof(a[0]);
  quicksort(a, 0, n - 1);
  for(auto const& ele : a)
  {
    cout << " " << ele;
  }

  return 0;
}
