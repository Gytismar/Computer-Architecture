#include <iostream>
#include <stdlib.h> 

using namespace std;

int XORAS (int a, int b){
  return ((~a) & b) | (a & (~b));
}

void HalfSUM(int a, int b, int &sum, int &carry)
{
  sum = (XORAS(a,b));
  carry = (a & b);
}

void FULLSUM(int a, int b, int CIN, int& COUT, int& SUM){ // CIN = carry in, COUT = carry out
  int sum1, sum2, carry1, carry2;
  HalfSUM(a,b,sum1,carry1);
  HalfSUM(sum1,CIN,sum2,carry2);
  COUT = carry1 | carry2;
  SUM = sum2;

  cout << SUM << " " << COUT;
}

void Sandauga(int a, int b){
  int mask = 1;
  int skaiciai[10000];

  for (int i = 0; i < b; i++){
    
  }
}


int main(int argc, char** argv) 
{
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  int XOR1 = ((~a) & b) | (a & (~b));
  int XOR2 = (a | b) & (~(a & b));
  int XOR3 = (a | b) & ((~a) | (~b));
  int XOR4 = ~((~(a&(~(a&b)))) & (~(b & (~(a&b)))));
}