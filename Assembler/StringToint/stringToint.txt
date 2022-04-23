#include <stdio.h>
#include <iostream>
#include <string.h>

int main(int argc, char** argv) {

	int iLettersCount;
	char* argv1 = argv[1];

	if( argc < 2 ) {
		printf("Nepateiktas parametras*/\n");
		return( 0 );
	}

	int nr;
	bool perdaug = false;
	bool neskaicius = false;
	__asm { 

		push eax
		push ebx
		push ecx
		push edx


		mov edx, 0
		mov ecx, argv1
		sub ecx, 1
		
		
		main_ciklas:
		xor eax, eax
		inc ecx
		mov al, byte ptr[ecx]
		cmp al, 0
		je pabaiga
		cmp al, 47
		jbe ne_skaicius
		cmp al, 58
		jae ne_skaicius
		mov ah, 47
		xor ebx, ebx
		jmp ciklas

		ciklas:
		add ebx, 1
		add ah, 1
		cmp ah, al
		je irasyti
		jmp ciklas

		irasyti:
		sub ebx, 1
		mov eax, edx
		imul eax, 10
		jo overflow
		mov edx, eax
		add edx, ebx
		jmp main_ciklas

		overflow:
		mov perdaug, 1

		ne_skaicius:
		mov neskaicius, 1

		pabaiga:
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
