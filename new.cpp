#include<iostream>
#include<string.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#define SIZE 10000000 /* Need to increase this!! */
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
    if(!table)
      {
	std::cout<<"Not sufficient memory"<<std::endl;
	exit(EXIT_FAILURE);
      }
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

/* djb2 hashing algorithm http://www.cse.yorku.ca/~oz/hash.html */ 
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

  return (hash % SIZE);
}

unsigned int Lines(std::ifstream &inp);
std:: string strip(std::string  str);


int main()
{
  /* currently only works on linux OS */ 
  /* Store files in the folder named "files", where "files" is a subfolder of the folder where file is present */
  system("ls files/*.txt>/tmp/files.txt");
  std::ifstream fin("/tmp/files.txt");
  numFiles = Lines(fin);
  std::string *fNames = new std::string[numFiles];
  for(int i =0; i< numFiles; i++)
    {
      std::getline(fin, fNames[i]);
    }
  std::cout<<"The list of files that are read"<<std::endl;
  for(int i =0; i< numFiles; i++)
    {
      std::cout<<fNames[i]<<std::endl;
    }
  std::string temp; 
  hashMap test;
  for(int i =0; i< numFiles; i++)
    {
      std::ifstream inp(fNames[i].c_str());
      while(inp>>temp)
	{
	  temp = strip(temp);
	  if(temp != "")
	    test.put(temp, i);
	}  
      inp.close();
    }
  std::cout<<"Enter string to search for: ";
  std::cin>>temp;
  temp = strip(temp);
  if(temp == "")
    {
      std::cout<<"Improper search: you searched for \""<<temp<<"\""<<std::endl;
      return 0;
    }
  int flag = test.get(temp);
  if(flag == -1)
    std::cout<<"Not found"<<std::endl;
  else if(flag == 1)
    {
      std::cout<<"String found"<<std::endl;
      std::cout<<"Indexes are the following"<<std::endl;
      for(int i = 0; i<numFiles; i++)
	std::cout<<fNames[i]<<":"<<templist[i].ret_count()<<std::endl;
    }
  fin.close();
  return 0;
}

unsigned int Lines(std::ifstream &inp)
{
  unsigned int count = 0;
  std::string temp;
  while(std::getline(inp, temp))
    count++;
  inp.clear();
  inp.seekg(0, std::ios::beg); /* Back to the beginning of the file */
  return count;
}

std:: string strip(std::string str)
{
  char * s = new char[str.size()];
  char * temp = new char[str.size()];
  strcpy(s,str.c_str());
  int j = 0;
  for(int i = 0; i<str.size(); i++)
    {
      if(('a'<= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z'))
	{
	  if(('A' <= s[i]) && (s[i] <= 'Z'))
	    temp[j++] = s[i]+'a'-'A';
	  else
	    temp[j++] = s[i];
	}
    }
  temp[j] = 0; 
  if(j == 0)
    str.assign("");
  else
    str.assign(temp);
  return str;  
}
