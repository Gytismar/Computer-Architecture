#include <stdio.h>
#include <iostream>
#include <string.h>

int main(int argc, char** argv) {

	int iLettersCount;
	char* argv1 = argv[1];

	if (argc < 2) {
		printf("Nepateiktas parametras\n");
		return(0);
	}

	int nr;
	bool perdaug = false;
	bool neskaicius = false; // flagai jei per didelis skaicius (negu leidzia int) ir ar paduotas skaicius, o ne kiti simboliai
	__asm {

		push eax // ah ir al registrams
		push ebx // laikyti turimam skaiciui
		push ecx // eiti pro string charus
		push edx // laikyti skaiciu int formate


		mov edx, 0
		mov ecx, argv1
		sub ecx, 1


		main_ciklas:
		xor eax, eax // nunulinamas eax
			inc ecx
			mov al, byte ptr[ecx] // imamamas kitas string simbolis
			cmp al, 0 // tikrina ar nesibaige failas
			je pabaiga
			cmp al, 47
			jbe ne_skaicius
			cmp al, 58
			jae ne_skaicius // tikrina, ar tai skaicius
			mov ah, 47
			xor ebx, ebx // nunulinamas ebx ir ah paverciamas 47 (veliau bus padidintas iki 48, kas yra ASCII = 0)
			jmp ciklas

		ciklas :
		add ebx, 1
		add ah, 1
		cmp ah, al // tikrinamas, ar ah == al
		je irasyti // jei taip, irasoma
		jmp ciklas // jei ne, griztame prie ciklas ir didiname ah ir vel tikriname

		irasyti :
		sub ebx, 1   // sumaziname ebx, kad gautumeme reikiama skaiciu
		imul edx, 10 // padauginame turima skaiciu 10
		jo overflow  // tikriname, ar neisejome is int ribu
		add edx, ebx // pridedame nauja skaiciu prie senu
		jmp main_ciklas

		overflow :
		mov perdaug, 1

		ne_skaicius :
		mov neskaicius, 1

		pabaiga :
		mov nr, edx

		pop eax
		pop ebx
		pop ecx
		pop edx
	};

	if (!perdaug && !neskaicius)
		std::cout << nr;
	else if (perdaug)
		std::cout << "Per didelis";
	else if (neskaicius)
		std::cout << "Neskaicius";

	return(0);
}
