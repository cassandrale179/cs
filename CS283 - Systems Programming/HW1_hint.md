## HW1
- **Q1**: 
  - Create a 2D array and store each line of code in the 2D array 
  - Then print the 2D array backward 
  ```c
    // Store line of code in a 2D char array 
    if (fp == NULL) return -1; 
    while(fgets(arr[k], SIZE, fp) != NULL){
        k++; 
    }
   ``` 
   
- **Q2**: This is a well documented code on Stack Overflow to create an array arr that stores binary value of decimal x  

  ```c
  void get_bin(int *arr, int x)
  {

      // x & 1 is equivalent to x % 2 
      // x >> 1 is equivalent to x / 2 
      int i;
      for (i = sizeof x * CHAR_BIT - 1; i >= 0; --i)
          *arr++ = x >> i & 1;
  }
  ``` 


- **Q3**: for this problem, have two pointers (start and end)
  -  The first pointer points to location of the int (&a)
  - The second pointer points to the end of the int (&a + 1)
  - Find the difference between the two pointers and multiply by 8 
  
  
