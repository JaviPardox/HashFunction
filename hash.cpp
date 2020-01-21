/*
 * @file hash_function.cpp
 *   
 * @brief  hash function from  www.partow.net/programming/hashfunctions
 *      
 * @author Javier Pardo
 *
 * @date 2/5/2017
 */         


#include"hash.h"
#include<iostream>
#include<fstream>

using std::cout;
using std::ios;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ws;

/*
 * @param None.
 *   
 * @brief Hash constructor, initializes all variables. 
 *      
 * @return Nothing.
 */
Hash::Hash()
{
  collisions = 0;
  longestList = 0;
  runningAvgListLength = 0;
}

/*
 * @param None.
 *   
 * @brief Print the whole hash table. 
 *      
 * @return Nothing.
 */
void Hash::print()
{
  list<string>::iterator it;
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    cout << i << ":\t";
    for(it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      cout << *it << ", ";
    }
    cout << endl;
  }
}

/*
 * @param Name of the file being open.
 *   
 * @brief Gets the content of the file as input and stores it in the 
 *        hash table. 
 *      
 * @return Nothing.
 */
void Hash::processFile(string ipFile)
{
  ifstream myFile(ipFile, ios::in);
  string word;
  double currentAvgListLen = 0;
  int index;
  while(!myFile.eof())
  {
    getline(myFile, word);
    myFile >> ws;
    index = hf(word);
    hashTable[index].push_back(word);
    if(hashTable[index].size() >= 2) 
      collisions++;
    if(hashTable[index].size() > longestList)
      longestList = hashTable[index].size();
    currentAvgListLen = (double)totalElements()/numOfLists();
    runningAvgListLength = (currentAvgListLen + runningAvgListLength)/2.0;
  }
}

/*
 * @param Word being searched.
 *   
 * @brief Searches for the desired word. 
 *      
 * @return True if the word was found, false otherwise.
 */
bool Hash::search(string word)
{
  list<string>::iterator it;
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    for(it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      if(*it == word)
        return true;
    }
  }
  return false;
}

/*
 * @param Word being removed.
 *   
 * @brief Removes the desired word from the list. 
 *      
 * @return Nothing.
 */
void Hash::remove(string word)
{
  double currentAvgListLen = 0;
  list<string>::iterator it;
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    for(it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      if(*it == word)
      {
        hashTable[i].erase(it);
        currentAvgListLen = (double)totalElements()/numOfLists();
        runningAvgListLength = (currentAvgListLen + runningAvgListLength)/2.0;
        return;
      }
    }
  }
}

/*
 * @param Output file.
 *   
 * @brief Outputs the whole hash table in a file. 
 *      
 * @return Nothing.
 */
void Hash::output(string opFile)
{
  list<string>::iterator it;
  ofstream OutFile(opFile, ios::out);
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    OutFile << i << ":\t";
    for(it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      OutFile << *it << ", ";
    }
  }
  OutFile << endl;
}

/*
 * @param None.
 *   
 * @brief Displays all the statistics. 
 *      
 * @return Nothing.
 */
void Hash::printStats()
{
  cout << "Total Collisions = " << collisions << endl;
  cout << "Longest List Ever = " << longestList << endl;
  cout << "Average List Length Over Time = " << runningAvgListLength << endl;
  cout << "Load Factor = " << (double)totalElements()/HASH_TABLE_SIZE << endl;
}

/*
 * @param None.
 *   
 * @brief This function counts the number of non-empty lists in the
 *        hash table. 
 *      
 * @return Counter.
 */
int Hash::numOfLists()
{
  int counter = 0;
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    if(hashTable[i].size() != 0)
      counter++;
  }
  return counter;
}

/*
 * @param None.
 *   
 * @brief This functions counts the number of elements 
 *        in the hash table. 
 *      
 * @return Counter.
 */
int Hash::totalElements()
{
  int counter = 0;
  for(int i=0; i < HASH_TABLE_SIZE; i++)
  {
    counter = counter + hashTable[i].size();
  }
  return counter;
}
/*
double Hash::RunningAvgListLength()
{
  double currentAvgListLen = totalElements()/numOfLists();
  runningAvgListLength = (currentAvgListLen + runningAvgListLength)/2.0;
  return runningAvgListLength;
}*/


