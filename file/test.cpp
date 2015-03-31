#include<iostream>
#include<fstream>
#include<string>

int main()
{
  std::ifstream fout("hello.txt");
  std:: string str; 
  fout>>str;
  std::cout<<str<<std::endl;
  fout>>str;
  std::cout<<str;
  fout.close();
}
