#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  unsigned char regs[16]; // 16 registrų
  unsigned char progMemory[256] = {0}; // programos atmintis
  bool eof = false;
  bool zero = false;

  ifstream binary ("decryptor.bin",ios::binary);
  ifstream ctext ("q1_encr.txt"); // encrypted tekstas
  ofstream text ("text.txt"); // decrypted tekstas

  int kiekis = 0; // komandų kiekis (32)
  char temp; // naudojamas skaitymui iš failo

  for (int i = 0; i < 256; i++){
    binary.get(temp);
    progMemory[i] = temp;

    if (progMemory[i] != 0){ // kad nebūtų įrašomi tarpai
      kiekis++;
    } 
  }
  kiekis++; // 31 vietoj 32, 32*8 = 256

  unsigned char kom; // komandos char
  unsigned int i = 0; // nustato kur programos atmintyje reikia skaityt
  unsigned int Rx, Ry; // registrų numerių kintamieji

  while (true){
    kom = progMemory[i]; // gaunamas komandos kodas
    Rx = progMemory[i + 1] & 0b1111; // skaitomas antras numeris hex skaičiuje (buvo 32, gavome 2)
    Ry = progMemory[i + 1] >> 4; // išstumiamas paskutinis skaitmuo, gaunas pirmas (buvo 32, liko 3)

    if (kom == 1) // INC, padidina Rx registra 1
      regs[Rx]++;
    else if (kom == 2) // DEC, pamazina Rx registra 1
      regs[Rx]--;
    else if (kom == 3) // MOV, kopijuoja tarp registru
      regs[Rx] = regs[Ry];
    else if (kom == 4) // MOV, kopijuoja į R0
      regs[0] = progMemory[i+1];
    else if (kom == 5) // LSL, pastumia registra i kaire per bita
      regs[Rx] <<= 1;
    else if (kom == 6) // LSR, pastumia registra i desine per bita
      regs[Rx] >>= 1; 
    else if (kom == 7){ // JMP, šoka nuo dabartinės komandos iki dabartinės + šuolio tolis
      if (i + progMemory[i+1] > kiekis)// jeigu bandome šokti toliau už atminties (komandų kiekio), peršokus iki galo, pradedame šokti nuo 0
      {
        i = (i + progMemory[i+1]) - 256;
      }
      else
        i = (i + progMemory[i+1]);

      continue; // kad nebūtų pridedamas i += 2
    }
    else if (kom == 8){ // JZ, tas pats kaip JMP, tačiau tiktais jei zero yra true
      if (zero){
        if (i + progMemory[i+1] > kiekis)
        {
          i = (i + progMemory[i+1]) - 256;
        }
        else
          i = (i + progMemory[i+1]);

        zero = false;
        continue;
      }
    }
    else if (kom == 9){ // JNZ, tas pats kaip JMP, tačiau tiktais jei zero yra false
      if (!zero){
        if (i + progMemory[i+1] > kiekis)
        {
          i = (i + progMemory[i+1]) - 256;
        }
        else
          i = (i + progMemory[i+1]);

        continue;
      }
    }
    else if (kom == 10 ){ // JFE, tas pats kaip JMP, tačiau jei eof yra true
      if (eof){
        if (i + progMemory[i+1] > kiekis)
        {
          i = (i + progMemory[i+1]) - 256;
        }
        else
          i = (i + progMemory[i+1]);

        eof = false;
        continue;
      }
    }
    else if (kom == 11)// RET, uzbaigiame virtualia masina (sustabdomas while loop)
      return 0;
    else if (kom == 12) // ADD, prie registro Rx pridedame registą Ry
      regs[Rx] += regs[Ry];
    else if (kom == 13) // SUB, is registro Rx atimame registra Ry
      regs[Rx] -= regs[Ry];
    else if (kom == 14) // XOR, XOR tarp registro Rx ir registro Ry
      regs[Rx] = regs[Rx] ^ regs[Ry];
    else if (kom == 15) // OR, OR tarp registro Rx ir registro Ry
      regs[Rx] = regs[Rx] | regs[Ry];
    else if (kom == 16){ // IN, skaito iš failo baitą, priskiria Rx registrui ir žiūri, ar baigėsi failas
      ctext >> temp;
      eof = ctext.eof(); // įsijungia eof flag, jei ctext pasibaigė
      regs[progMemory[i + 1]] = temp;
    }
    else if (kom == 17) // OUT, įrašo registrą Rx į failą
      text << regs[Rx];


    i += 2; // šoka per du skaičius
  }

  binary.close();
  ctext.close();
  text.close();

  return 0;
}