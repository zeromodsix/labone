#include<iostream>
#include<string.h>
#include<string>
#define SIZE 4294967297 /* 2^32 + 1 */

int numFiles;

class filecount
{
private:
  unsigned int index;
  unsigned int count;
public:
  filecount()
  {
    count = 0;
  }
  void increase()
  {
    count++;
  }
  int ret_count()
  {
    return (count);
  }
};

class linkedHashEntry
{
private:
  std::string str;
  filecount * fileList;
  linkedHashEntry * next;
public:
  std::string getStr()
  {
    return str;
  }
  filecount getFileList()
  {
    return fileList;
  }
  void setStr(std::string st)
  {
    str = st;
  }
  linkedHashEntry getNext()
  {
    return next;
  }
  
  void setNext(linkedHashEntry *next)
  {
    this->next = next;
  }
  linkedHashEntry()
  {
    str="";
    fileList = new filecount[numFiles];
    next = NULL;
  }
  void change(std::st, unsigned int file);

};

void linkedHashEntry::change(std::st, unsigned int file)
{
  str = st; 
  fileList[file].increase();
}


class hashMap
{
private:
  linkedHashEntry **table;
public:
  unsigned int get(string str);
  void put(std::string str, unsigned int file);
  hashMap()
  {
    table = new linkedHashEntry*[SIZE];
    for(int i = 0; i< SIZE; i++)
      table[i] = NULL;
  }
  unsigned long int hash(const std::string );
};

void hashMap::put(std::string str, unsigned int file)
{
  unsigned long int hash = hash(str);
  if(table[hash] == NULL)
    table[hash] = new linkedHashEntry(str, file);
  else
    {
      linkedHashEntry * entry = table[hash];
      while(entry->getNext() ! = NULL)
	{
	  entry = entry->next;
	}
    }
}

unsigned long int hash(const std::string str)
{
  unsigned long int hash = 5381;
  int c;
  unsigned char *st = new unsigned char[str.size()];
  st[0] = 0;
  strcopy(st, str.c_str());
  while (c = *st++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}


