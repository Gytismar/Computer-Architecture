#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

string BIN(string hex){ //is hex i binary
  string temp = "";
  
  for (int i = 0; i < 2; i++){
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

int DEC(string hex){ // is binary i decimal
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

string Bit2(string bin){ // jei 2 bytes
  string temp = bitset<16>(0).to_string();
  temp[0] = '1';
  temp[1] = '1';
  temp[2] = '0';
  temp[3] = bin[5];
  temp[4] = bin[6];
  temp[5] = bin[7];
  temp[6] = bin[8];
  temp[7] = bin[9];
  temp[8] = '1';
  temp[9] = '0';
  temp[10] = bin[10];
  temp[11] = bin[11];
  temp[12] = bin[12];
  temp[13] = bin[13];
  temp[14] = bin[14];
  temp[15] = bin[15];
  
  return temp;
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

string Bit4(string bin){ // jei 4 bytes
  string temp = bitset<32>(0).to_string();

  temp[0] = '1';
  temp[1] = '1';
  temp[2] = '1';
  temp[3] = '1';
  temp[4] = '0';
  temp[5] = bin[11];
  temp[6] = bin[12];
  temp[7] = bin[13];
  temp[8] = '1';
  temp[9] = '0';
  temp[10] = bin[14];
  temp[11] = bin[15];
  temp[12] = bin[16];
  temp[13] = bin[17];
  temp[14] = bin[18];
  temp[15] = bin[19];
  temp[16] = '1';
  temp[17] = '0';
  temp[18] = bin[20];
  temp[19] = bin[21];
  temp[20] = bin[22];
  temp[21] = bin[23];
  temp[22] = bin[24];
  temp[23] = bin[25];
  temp[24] = '1';
  temp[25] = '0';
  temp[26] = bin[26];
  temp[27] = bin[27];
  temp[28] = bin[28];
  temp[29] = bin[29];
  temp[30] = bin[30];
  temp[31] = bin[31];

  return temp;
}

void Output(string UNI, string UTF){
  int kiekis = 0;
  char simbolis[8];
  
  string temp;
  for (int i = 0; i < UTF.size(); i += 2){ // skirta simboliui sudaryti
    temp = ""; 
    temp += UTF[i];
    temp += UTF[i+1];
    
    simbolis[kiekis] = DEC(temp);
    kiekis++;
  }

  string UNI2 = "";
  bool t = false;
  if (UNI.size() > 4){
    for (int i = 0; i < UNI.size(); i++){
      if (UNI[i] != '0' && !t){
        t = true;
        UNI2 += UNI[i];
      }
      else if (t){
        UNI2 += UNI[i];
      }
    }
  }
  else if (UNI.size() == 4){
    UNI2 = UNI;
  }
  else if (UNI.size() < 4){
    for (int i = 0; i < 4-UNI.size(); i++)
      UNI2 += '0';

    UNI2 += UNI;
  }
  
  
  
  simbolis[kiekis] = 0;

  cout << "UNICODE: U+" << UNI2 << endl;
  cout << "UTF-8: " << UTF << endl;
  cout << "CHAR: " << (char*)simbolis << endl;
}

void Unicode(string numeris){
  int nr = stoi(numeris);
  int temp = 0;

  string bin;
  string UNI = "";
  string UTF = "";
  
  if (nr <= 127){
    bin = bitset<8>(nr).to_string();

    UNI = HEXA(8,bin);
    UTF = UNI;
  }
  else if (nr >= 128 && nr <= 2047){
    bin = bitset<16>(nr).to_string();
    UNI = HEXA(16,bin);
    
    bin = Bit2(bin);
    UTF = HEXA(16,bin); 
  }
  else if (nr >= 2048 && nr <= 65535){
    bin = bitset<24>(nr).to_string();
    UNI = HEXA(24,bin);
    
    bin = Bit3(bin);
    UTF = HEXA(24,bin);
  }
  else if (nr >= 65536 && nr <= 1114111){
    bin = bitset<32>(nr).to_string();
    UNI = HEXA(32,bin);

    bin = Bit4(bin);
    UTF = HEXA(32,bin);
  }

  Output(UNI,UTF);
}

int main(int argc, char** argv)
{
  for (int i = 1; i < argc; i++){
    Unicode(argv[i]);
  }
}