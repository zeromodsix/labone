#include<iostream>
#include<string.h>
#include<string>
#define SIZE 4294 /* Need to increase this */

int numFiles;
class filecount * templist = NULL;

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
  filecount* getFileList()
  {
    return fileList;
  }
  void setStr(std::string st)
  {
    str = st;
  }
  linkedHashEntry* getNext()
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
  void change(std::string st, unsigned int file);
  void fileIncrease(unsigned int file);

};

void linkedHashEntry::change(std::string st, unsigned int file)
{
  str = st; 
  fileList[file].increase();
}

void linkedHashEntry::fileIncrease(unsigned int file)
{
  fileList[file].increase();
}


class hashMap
{
private:
  linkedHashEntry **table;
public:
  unsigned long int hash(const std::string );
  void put(std::string str, unsigned int file);
  int get(std::string str);
  hashMap()
  {
    table = new linkedHashEntry*[SIZE];
    for(int i = 0; i< SIZE; i++)
      table[i] = NULL;
  }
  
};

/* Returns -1 if entry is not present, returns 1 and copies the pointer to list to templist */
int hashMap::get(std:: string str)
{
  unsigned long int hash1 = hash(str);
  if(table[hash1] == NULL)
    return -1;
  else
    {
      linkedHashEntry * entry = table[hash1];
      while(entry != NULL && entry->getStr() != str)
	{
	  entry = entry->getNext();
	}
      if(entry == NULL)
	return -1;
      else
	{
	  templist = entry->getFileList();
	  return 1;
	}
    }
}

void hashMap::put(std::string str, unsigned int file)
{
  unsigned long int hash1 = hash(str);
  if(table[hash1] == NULL)
    {
      table[hash1] = new linkedHashEntry;
      table[hash1]->change(str, file);
    }
  else
    {
      linkedHashEntry * entry = table[hash1];
      while(entry->getNext() != NULL && entry->getStr() != str)
	{
	  entry = entry->getNext();
	}
      if(entry->getStr() == str)
	{
	  entry->fileIncrease(file);
	}
      else
	{
	  linkedHashEntry * temp = new linkedHashEntry;
	  temp->change(str, file);
	  entry->setNext(temp);
	}
    }
}

unsigned long int hashMap::hash(const std::string str) 
{
  unsigned long int hash = 5381;
  int c;
  char *temp = new char[str.size()];
  temp[0] = 0;
  strcpy(temp, str.c_str());
  unsigned char * st = reinterpret_cast<unsigned char *>(temp);
  /* http://stackoverflow.com/questions/5040920/ */
  while (c = *st++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}


int main()
{
  hashMap test;
  return 0;
}
