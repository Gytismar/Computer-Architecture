#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct Komanda
{
  char nsim; // naujas simbolis
  char krypt;// kryptis
  string bus = "";// kita busena

};

void turingas(string failas)
{
  bool halt = false; // skirta sustabdyti programą
  int priezastis;
  char testi = '?';

  ifstream Input (failas);

  map <string, map<char, Komanda>> komandos; // komandu konteineris, pirma ieškoma pagal būseną, tada pagal simbolį ir tikrina pagal Komandos struct ką daryti

  string juosta = ""; 
  Input >> juosta; // įdedama pradinė juosta

  if (juosta == "")
  {
    halt = true;
    priezastis = 1;
  }

  int pradine;
  Input >> pradine; // pradinė galvutės pozicija


  string s_temp; char c_temp; // laikini kintamieji
  while(!Input.eof() && !halt)
  {
    Input >> s_temp >> c_temp; // gaunama komandos būsena ir ieškomas simbolis
    Input >> komandos[s_temp][c_temp].nsim; // naujas simbolis
    Input >> komandos[s_temp][c_temp].krypt;// kryptis
    Input >> komandos[s_temp][c_temp].bus;  // kita būsena (būsima)
  }

  int x = pradine-1; // -1 nes masyvai prasideda nuo 0

  for (int i = 0; i < juosta.size() && !halt; i++) //parasoma pradine juosta
  {
    if (x == i)
        cout << "\033[31m" << juosta[i]; // raudona spalva
      else
        cout << "\033[0m" << juosta[i]; //  grįžtama į juodą

  }
  cout << endl;

  string dabartinis = "0"; // nustatoma pradine busena į 0
  

  char n, k; // naujas simbolis ir kryptis
  string b;  // kita būsena

  int temp = 0; // laikini kintamieji, skirti tikrinti, ar programa nėra infinite loop
  string temp_string; 
  string temp_busena;
  char temp_kryp;

  while(!halt)
  {
    n = komandos[dabartinis][juosta[x]].nsim;
    k = komandos[dabartinis][juosta[x]].krypt;
    b = komandos[dabartinis][juosta[x]].bus;

    if (juosta == temp_string && temp_busena == b && temp_kryp == k && testi == '?') // tikrina ar nesikarto ta pati juosta su ta pacia busena ir kryptimi
    {
      halt = true;
    
      cout << "Programa galimai nesibaigiančiame cikle, ar noretumete testi? y/n ";
      cin >> testi;

      if (testi == 'y' || testi == 'Y')
        halt = false;
      else if (testi == 'n' || testi == 'N')
        priezastis = 5;
      else
        priezastis = 4;
    }
    else if (temp == 10000 && testi == '?')
      temp = 0;
    else if (testi == '?')
      temp++;

    if (temp == 0 && testi == '?') // kas 10000 žingsnių yra įkeliama nauja laikina juosta, busena ir kryptis
    {
      temp_string = juosta;
      temp_busena = b;
      temp_kryp = k;
    }
    

    juosta[x] = n; // juostoje senas simbolis pakeičiamas nauju

    if (k == 'L') // judinama galvutė juostoje
      x--;
    else
      x++;
    
    dabartinis = b; // pakeičiama dabartinė būsena
    
    for (int i = 0; i < juosta.size() && !(priezastis == 4 || priezastis == 5); i++) // spausdinama juosta
    {
      if (x == i)
        cout << "\033[31m" << juosta[i];
      else
        cout << "\033[0m" << juosta[i];
    }
    
    if (komandos[dabartinis].size() == 0) // jei dabartinėje būsenoje nėra jokių komandų
    { 
      priezastis = 2;
      halt = true;
    }
    else if (komandos[dabartinis][juosta[x]].bus == "") // jei dabartinėje būsenoje esąmam simboliui nėra 
    {
      priezastis = 3;
      halt = true;
    }
    cout << endl;
  }

  switch (priezastis)
  {
    case 1:
      cout << "Blogas arba neegzistuojantis failas" << endl;
      break;
    case 2:
      cout << "Busena " << dabartinis << " neturi komandu" << endl;
      break;
    case 3:
      if(juosta[x] == '\0')
        juosta[x] = '_';
      cout << "Simbolio " << juosta[x] << " būsenoje " << dabartinis << " nėra" << endl;
      break;
    case 4:
      cout << "Netinkamas pasirinkimas, programa terminuojama" << endl;
      break;
    case 5:
      cout << "Programa terminuota vartotojo pasirinkimu" << endl;
      break;
  }

}

int main(int argc, char** argv)
{
  turingas(argv[1]);
}