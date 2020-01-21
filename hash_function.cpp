/* This assignment originated at UC Riverside.*/
/*
 * @file hash_function.cpp
 *   
 * @brief  hash function from  www.partow.net/programming/hashfunctions
 *      
 * @author Javier Pardo
 *
 * @date 4/5/2017
 */         



#include <string>
#include "hash.h"

using std::string;

int Hash::hf(string ins)
{
  //due to the overflowing of int, I had to use unsigned variables
  //so it does not return a negative number (flipping of the 32 bit)
  unsigned int a = 6067;
  unsigned int b = 3373;
  unsigned int hash = 0;
  for(unsigned int i=0; i < ins.size(); i++)
  {
    hash = hash * a + ins[i];
    a = a*b;
  }
  return ((unsigned int) hash % HASH_TABLE_SIZE);
}


/*
int 
Hash::hf ( string ins ) {
    
    // place your hash function here....
   return ( (int) ins[0] ) % HASH_TABLE_SIZE;
}*/

