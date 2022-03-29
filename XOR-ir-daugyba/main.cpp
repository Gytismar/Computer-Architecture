#include <iostream>
#include <stdlib.h> 

using namespace std;

int XORAS (int a, int b){
  return ((~a) & b) | (a & (~b));
}

int Suma(int a, int b){
  int carry = 0;

  while (b != 0){
    carry = a & b;
    a = XORAS(a,b);
    b = carry << 1;

    cout << carry << " " << a << " " << b << endl;
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

  cout << Sandauga(a,b);
}