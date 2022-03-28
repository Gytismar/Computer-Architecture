#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>
#include <math.h>

using namespace std;

string BIN(string hex){ //is hex i binary
  string temp = "";
  
  for (int i = 0; i < hex.size(); i++){
    if (hex[i] == '0')
      temp += "0000";
    if (hex[i] == '1')
      temp += "0001";
    if (hex[i] == '2')
      temp += "0010";
    if (hex[i] == '3')
      temp += "0011";
    if (hex[i] == '4')
      temp += "0100";
    if (hex[i] == '5')
      temp += "0101";
    if (hex[i] == '6')
      temp += "0110";
    if (hex[i] == '7')
      temp += "0111";
    if (hex[i] == '8')
      temp += "1000";
    if (hex[i] == '9')
      temp += "1001";
    if (hex[i] == 'A')
      temp += "1010";
    if (hex[i] == 'B')
      temp += "1011";
    if (hex[i] == 'C')
      temp += "1100";
    if (hex[i] == 'D')
      temp += "1101";
    if (hex[i] == 'E')
      temp += "1110";
    if (hex[i] == 'F')
      temp += "1111"; 
  }
  return temp;
}

int DEC(string hex){ // is hrx i decimal
  int dec = 0;
  string bin = BIN(hex);
  for (int i = bin.size()-1; i >= 0; i--){
    if (bin[i] == '1')
      dec += pow(2,bin.size()-1-i);
  }
  return dec;
}

char HEX(string binary) // is 4 bit i hex
{
  int temp = 0;
  char simbolis;
  
  
  if (binary[0] == '1')
    temp += 8;
  if (binary[1] == '1')
    temp += 4;
  if (binary[2] == '1')
    temp += 2;
  if (binary[3] == '1')
    temp += 1;

  char simboliai [16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E', 'F'};
  simbolis = simboliai[temp];
  return simbolis;
}

string Bit3(string bin){ // jei 3 bytes
  string temp = bitset<24>(0).to_string();
  
  temp[0] = '1';
  temp[1] = '1';
  temp[2] = '1';
  temp[3] = '0';
  temp[4] = bin[8];
  temp[5] = bin[9];
  temp[6] = bin[10];
  temp[7] = bin[11];
  temp[8] = '1';
  temp[9] = '0';
  temp[10] = bin[12];
  temp[11] = bin[13];
  temp[12] = bin[14];
  temp[13] = bin[15];
  temp[14] = bin[16];
  temp[15] = bin[17];
  temp[16] = '1';
  temp[17] = '0';
  temp[18] = bin[18];
  temp[19] = bin[19];
  temp[20] = bin[20];
  temp[21] = bin[21];
  temp[22] = bin[22];
  temp[23] = bin[23];

  return temp;
}

string HEXA(int n, string bin){ // binary ilga i hex
  string hex = "";
  string small_hex = "";
  int temp = 0;
  
  for (int i = 0; i < n; i++){
    small_hex += bin[i];
    if(temp == 3){
      hex += HEX(small_hex);
      temp = 0;
      small_hex = "";
    }
    else
      temp++;
  }
  return hex;
}

int main(int argc, char** argv) {
  string pavadinimas = argv[1];
  ifstream failas (pavadinimas);
  ifstream pakeitimai ("cp437.txt");
  ofstream tekstas ("tekstas.txt");

  map <int, string> simboliai194;
  map <int, string> simboliai195;
  string nr, a, b; // nr yra 194/195 (pirmo gaunamo char int vertė), a antro gaunamo char int vertė hex formatu (paverčiama į dec), b hex kodas UTF-8 reikiamo simbolio

  string bin, UTF; // binary, UTF-8
  while (!pakeitimai.eof()){
    pakeitimai >> nr >> a >> b;
  
    bin = bitset<24>(DEC(b)).to_string(); // sukuriamas iš b dec vertės binary string
    bin = Bit3(bin); // siunciamas paversti i UTF formata binary forma
    UTF = HEXA(24,bin); // paverciamas i hex

    if (nr == "194")
      simboliai194[DEC(a)] = UTF;
    else if (nr == "195")
      simboliai195[DEC(a)] = UTF;
}  
  
  char raide[8]; // simbolis is bytes

  unsigned char temp; // skirta skaityti is failo
  string temp2; // skirta suskaldyti UTF verte

  char temp3;  // skirta simboliui sudaryti
  int kiekis; // kiek bytes tures simbolis
  
  int k; //  laikinas kintamasis ziureti char int vertes
  while (!failas.eof()){
    failas >> noskipws >> temp; // simboliu skaitymas
    k = temp; // priskiriam gauto simbolio verte k intui
    
    if (k == 7 || k == 16 || k == 17 || k == 27 || k == 30 || k == 31){ // unicode control simboliai paverciami tarpais
      raide[0] = 32; // " "
      raide[1] = 0;
    }
    else if (k == 194){
      failas >> noskipws >> temp;
      k = temp;
      
      UTF = simboliai194[k]; // gaunamas UTF hex kodas reikiamo simbolio
      kiekis = 0;
      
      for (int i = 0; i < 8; i++)
        raide[i] = '\0';
      
      for (int b = 0; b < UTF.size(); b += 2){ // skirta simboliui sudaryti
        temp2 = ""; 
        temp2 += UTF[b];
        temp2 += UTF[b+1];
        
        raide[kiekis] = DEC(temp2);
        kiekis++;
      }
      raide[kiekis] = 0;
    }
    else if (k == 195){
      failas >> noskipws >> temp; // skaitomas antra char dalis ir gaunama jo verte
      k = temp;
      
      UTF = simboliai195[k]; // gaunamas UTF hex kodas reikiamo simbolio
      kiekis = 0;
      
      for (int i = 0; i < 8; i++) // raide[] NULLinamas
        raide[i] = '\0';
      
      for (int b = 0; b < UTF.size(); b += 2){ // skirta simboliui sudaryti
        temp2 = ""; 
        temp2 += UTF[b];
        temp2 += UTF[b+1];
        
        raide[kiekis] = DEC(temp2);
        kiekis++;
      }
      raide[kiekis] = 0;
    }
    else{
      raide [0] = k;
      raide [1] = 0;
    }
      

    tekstas << (char*)raide;
  }
  cout << "Completed\n";
}