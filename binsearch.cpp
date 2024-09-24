#include <iostream>
#include <fstream>


using namespace std;

// prototypes
void sort(int data[], int len);
int binsearch(int target, int data[], int start, int end);

int main(int argc, char *argv[]){
  int target;
  if(argc < 3){
    cout << "Provide a filename of the data to be searched." << endl;
    cout << "And also provide a target number to search for." << endl;
    return 1;
  }
  ifstream datfile(argv[1]);
  if( datfile.fail() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while(! datfile.fail()){
    int temp;
    datfile >> temp;
    if(!datfile.fail()){
      count++;
    }
  }
  //5 integers: 0 1 2 3 4
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to 
  // clear that flag.  Add the appropriate line of code to clear
  // the EOF (and fail) flags.
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  //  Add a call to datfile.seekg() with appropriate arguments 
  //  to ensure the `datfile` stream returns to the beginning of the file
  datfile.seekg(0,ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  
  sort(data, count);

  cout << "Read " << count << " integers from the data file." << endl;
  for(int i=0; i < count; i++){
    cout << data[i] << " ";
  }
  cout << endl;

  target = atoi(argv[2]); 
  cout << "Will now search for: " << target << endl;

  // Call binary search
  int retval = binsearch(target,data,0,count);



  // DO NOT ALTER - Interpret and print the results. 
  cout << "Binary search returned: " << endl;
  cout << retval << endl;

  // Deallocate the data array
  delete [] data;
  return 0;
}


// Returns the index in the data array where target is located
//  or -1 if the target value is not in the list
// Note: start is an inclusive index, while end is exclusive 
//       (i.e. 1 beyond the last data index to consider)
int binsearch(int target, int *data, int start, int end)
{
  if (start>=end)
  {
    return -1;
  }
  else{
    int midd=start + ((end - start) / 2);
    if (target==data[midd])
    {
      return midd;
    }
    else if (target>data[midd]){
      
      return binsearch(target, data, midd + 1, end);
    }
    else if (target<data[midd])
    {
      return binsearch(target, data, start, midd);
    }
  }
}


// implements a selection sort algorithm to sort
//  the integer values in the 'data' array of size 'len'
// You can change the prototype of this function 
//  if you need to pass an extra argument, but
//  you can do it without adding arguments and
//  we encourage you to find such a solution
void sort(int *data, int len)
{
  if (len<=1){
    return;
  }
  else
  {
    int max=0, idx=0;
    for(int i=0; i<len; i++)
    {
      if (data[i]>max)
      {
        max=data[i];
        idx=i;
      }
    }
    swap(data[idx],data[len-1]);
    sort(data,len-1);
  }
}
