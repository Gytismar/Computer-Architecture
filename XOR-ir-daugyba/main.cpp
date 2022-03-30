#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int XORAS (int a, int b){
  return ((~a) & b) | (a & (~b));
}

int Suma(int a, int b){
  unsigned int carry = 0;
  
  while (b != 0){
    carry = a & b;
    a = XORAS(a,b);
    b = carry << 1;
  }

  return a;
}

int Sandauga(int a, int b){
  int x = 0;

  while (b != 0){
    if (b & 1){
      x = Suma(x,a);
    }
    b = b >> 1;
    a = a << 1;
  }

  return x;
}


int main(int argc, char** argv) 
{
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  int XOR1 = ((~a) & b) | (a & (~b));
  int XOR2 = (a | b) & (~(a & b));
  int XOR3 = (a | b) & ((~a) | (~b));
  int XOR4 = ~((~(a&(~(a&b)))) & (~(b & (~(a&b)))));
  
  ofstream failas ("Rez.csv",std::ios::in | std::ios::out | std::ios::ate); 
//atidaryti skaitymui (in), atidaryti rašymui (out), eit į galą(ate)

  failas << XOR1 << ";" << XOR2 << ";" << XOR3 << ";" << XOR4 << ";" << Sandauga(a,b) << endl;
  // Visi XOR ir tada sandauga
}