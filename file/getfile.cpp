#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>

unsigned int Lines(std::ifstream &inp);

int main()
{
  /* Provided, that files.txt is not a valid one */ 
  system("ls *.txt> /tmp/files.txt");
  std::ifstream fin("/tmp/files.txt");
  unsigned int numlines = Lines(fin);
  std::string *fNames = new std::string[numlines];
  for(int i =0; i< numlines; i++)
    {
      std::getline(fin, fNames[i]);
    }
  for(int i =0; i< numlines; i++)
    {
      std::cout<<fNames[i]<<std::endl;
    }
   return 0;
}

unsigned int Lines(std::ifstream &inp)
{
  unsigned int count = 0;
  std::string temp;
  while(std::getline(inp, temp))
    count++;
  inp.clear();
  inp.seekg(0, std::ios::beg); /* Back to the beggining of the file */
  return count;
}
