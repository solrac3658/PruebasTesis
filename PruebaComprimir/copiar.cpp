#include <iostream>     // std::cout
#include <fstream>      // std::ifstream



int main () {
  std::ifstream is ("contractdbNew.zip", std::ifstream::binary);
  std::ofstream salida ("contractdbNew2.zip", std::ifstream::binary);
  
  
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];

    // read data as a block:
    is.read (buffer,length);

    is.close();

    // print content:
    //std::cout.write (buffer,length);

    salida.write(buffer, length);

    delete[] buffer;
    salida.close();
    //salida.close();
  }

  return 0;
}