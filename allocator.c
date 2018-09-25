//Nume: Gavan Adrian George
//Grupa: 314CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char *arena; //Pentru simplitatea codului si usurinta de citire se va folosi o variabila globala

//Antete functii  
int CI(int index);					//Functie pentru valoarea intregului de la index
int Is_Space(int index, int alloc_size, int N);		//Functie care verifica daca este spatiu intre blocuri
void initialize(int numar);				//Funtia pentru comanda INITIALIZE
void finalize();					//Functie pentru comanda FINALIZE
void dump(int numar);					//Functie pentru comanda DUMP
void alloc(int N, int alloc_size);			//Functie pentru comanda ALLOC
void FREE(int index);					//Functie pentru comanda FREE
void FILL(int index, int fill_size, int fill_value);	//Functie pentru comanda FILL
void SHOW(int N, char show_info[]);			//Functie pentru comanda SHOW (FREE/USAGE/ALLOCATIONS)

int main()
{
	char comanda[30];	//Variabila ce retine comanda
	char show_info[30];	//Variabila ce contine al doilea cuvand al comenzii SHOW
	int N = 0;		//Variabila pentru parametrul functiei INITIALIZE 
	int alloc_size, index, fill_size, fill_value;	//Variabile pentru parametri functiilor
	while(1){
		scanf("%s", comanda);
		//Programul va intra pe ramura corespunzatoare functiei date
		if(strcmp(comanda, "INITIALIZE") == 0){
			scanf("%d", &N);
			initialize(N);	
		}
		if(strcmp(comanda, "FINALIZE") == 0){
			finalize();
			break;			
		}
		if(strcmp(comanda, "DUMP") == 0){
			dump(N);
		}
		if(strcmp(comanda, "ALLOC") == 0){
			scanf("%d", &alloc_size);
			alloc(N, alloc_size);
		}
		if(strcmp(comanda, "FREE") == 0){
			scanf("%d", &index);
			FREE(index);
		}
		if(strcmp(comanda, "FILL") ==0){
			scanf("%d", &index);
			scanf("%d", &fill_size);
			scanf("%d", &fill_value);
			FILL(index, fill_size, fill_value);
		}
		if(strcmp(comanda, "SHOW") == 0){
			scanf("%s", show_info);
			SHOW(N,show_info);
		}
		
	}
	return 0;
}

//Functia CI
int CI(int index){
	int valoare;
	valoare = *((int*)(arena + index));
	return valoare;
}

//Functia care verifica daca este spatiu
int Is_Space(int index, int alloc_size, int N){
	if(CI(index) == 0){
		if(index == 0){ 			//Cand arena este goala
			if(alloc_size + 16 > N){
				return 0;
			}else{
				return 1;
			}
		}else{					//Pentru bloc final
			if(N - index - CI(index + 8) < alloc_size + 12){
				return 0;
			}else{
				return 1;
			}
		}
	}else{
		if(index == 0){				//Pentru inceput si primul bloc
			if(CI(0) >= alloc_size + 16){
				return 1;
			}else{
				return 0;

			}
		}else{					//Pentru 2 blocuri
			if(CI(index) - index - CI(index + 8) >= alloc_size + 12){
				return 1;
			}else{
				return 0;
			}
		}
	}
	return 0;
}

//Functia INITIALIZE			
void initialize(int numar){
	int i = 0;
	arena = malloc(numar * sizeof(unsigned char));	//Alocam numar octeti
	for(i = 0; i < numar; i++){			//Initializam cu 0
		arena[i] = 0;
	}
}

//Functia FINALIZE
void finalize(){
	free(arena);	//Eliberam memoria alocata dinamic
}

//Functia DUMP
void dump(int numar){
	int i, j;
	unsigned char *p;
	p = arena;
	for(i = 0; i < numar - 16; i = i + 16){
		printf("%08X\t", i);			//Indicele curent
		for(j = i; j < i + 16; j++){
			if(j == i + 8 ) {		//Intre octetii 8-9 sa bage spatiu
				printf(" ");
			}
			printf("%02X ", *(p + j));	//Cei 16 octeti
		}
		printf("\n");
	}
	printf("%08X\t", i);		//Pentru penultima linie care poate nu contine 16 octeti
	while(i < numar){
		printf("%02X ", *(p + i));
		i++;
	}
	printf("\n%08X\n", numar);	//Pentru ultima linie, ce afiseaza dimensiunea
}

//Functia ALLOC
void alloc(int N, int alloc_size){
	int index;
	index = 0; 
	while(index < N){
		if(CI(index) == 0){		
			if(index == 0){		//Daca arena este goala
				if(Is_Space(index, alloc_size, N) == 1){
					*((int*)(arena + 0)) = 4;					
					*((int*)(arena + 4)) = 0;
					*((int*)(arena + 8)) = 0;
					*((int*)(arena + 12)) = alloc_size + 12;
					printf("%d\n",16);
					return;
				}else{		//Arena este goala dar cu spatiu insuficient
					printf("0\n");
					return;
				}
			}else{			//Adauga bloc la final
				if(Is_Space(index, alloc_size, N) == 1){
					*((int*)(arena + index + CI(index + 8))) = 0;
					*((int*)(arena + index + 4 + CI(index + 8))) = index;
					*((int*)(arena + index + 8 + CI(index + 8))) = alloc_size + 12;
					*((int*)(arena + index)) = index +CI(index + 8);
					printf("%d\n",index + CI(index + 8) + 12);
					return;
				}else{		//Daca nu e loc la final
					printf("0\n");
					return;
				}
			}
		}else{
			if(index == 0){
				if(Is_Space(index, alloc_size, N) == 1){  //Daca e loc intre inceput si primul bloc
					*((int*)(arena + 4)) = CI(0); 
					*((int*)(arena + 0)) = 4;
					*((int*)(arena + 8)) = 0;
					*((int*)(arena + 12)) = alloc_size + 12;
					*((int*)(arena + CI(4) + 4)) = 4; 
					printf("%d\n",16);
					return;
				}
			}else{
				if(Is_Space(index, alloc_size, N) == 1){  //Daca e loc intre 2 blocuri
					*((int*)(arena + index + CI(index + 8))) = CI(index);
					*((int*)(arena + index + 4 + CI(index + 8))) = index;
					*((int*)(arena + index + 8 + CI(index + 8))) = alloc_size + 12;
					*((int*)(arena + CI(index) + 4)) = index + CI(index + 8);
					*((int*)(arena + index)) = index + CI(index + 8);
					printf("%d\n", index + CI(index + 8) + 12);
					return;
				}
			}

		}			

	index = CI(index); //Incrementam index (sare la urmatorul bloc)
	}	
	return;
}

//Functia FREE
void FREE(int index){
	if(CI(index - 12) == 0){ 
		if(index == 0){ //Pentru indexul de start
			return;
		}else{		//Ultimul bloc
			*((int*)(arena + CI(index - 8))) = 0;
			return;
		}
	}else{			//Pentru celelalte	
		*((int*)(arena + CI(index - 8))) = *((int*)(arena+index-12)); 
		*((int*)(arena + CI(index - 12) + 4)) = *((int*)(arena+index-8)); 
		return;
	}
}

//Functia FILL
void FILL(int index, int fill_size, int fill_value){
	int i = 0;
	for(i = index; i < fill_size + index; i++){
		 arena[i] = fill_value;
	}
	
}

//Functia SHOW
void SHOW(int N, char show_info[]){
	int index, b_liberi = 0;
	int nblocks = 0;	//Numarul de blocuri libere din arena
	int nbytes = 0;		//Numarul de octeti liberi din arena

	int ublocks = 0;	//Numarul de blocuri din arena
	int ubytes = 0;		//Numarul de octeti folositi din arena (pentru date)
	int eff = 0;		//Variabila pentru eficienta
	int fragm = 0;		//Variabila pentru fragmentare

	int oalloc = 0;		//Variabila pentru octeti ocupati
	int falloc = 0;		//Variabila pentru octeti free
	index = 0;
	if(strcmp(show_info, "ALLOCATIONS") == 0){
		printf("OCCUPIED 4 bytes\n");
	}
	while(index < N){
		if(CI(index) == 0){
			if(index == 0){     //Daca arena este goala
				nblocks = 1;
				nbytes = N - 4;
				oalloc = 4;
				falloc = N - 4;
				ubytes = 0;
				if(strcmp(show_info, "FREE") == 0){
					printf("%d blocks (%d bytes) free\n", nblocks, nbytes);
					return;
				}
				if(strcmp(show_info, "USAGE") == 0){
					printf("%d blocks (%d bytes) used\n", ublocks, ubytes);
					printf("%d%% efficiency\n", eff);
					printf("%d%% fragmentation\n", fragm);
					return;
				}
				if(strcmp(show_info, "ALLOCATIONS") == 0){
					//printf("OCCUPIED %d bytes\n", oalloc);
					printf("FREE %d bytes\n", falloc);
					return;
				}
			}else{			//Daca este ultimul bloc
				b_liberi = N - index - CI(index + 8);
				ublocks = ublocks + 1;
				ubytes = ubytes + CI(index + 8) - 12;
				eff = ((ubytes * 100) / (ubytes + (ublocks * 12) + 4));
				if(b_liberi > 0){
					nblocks = nblocks + 1;
					nbytes = nbytes + b_liberi;
				}
				fragm = 100 * (nblocks - 1) / ublocks;
				oalloc = CI(index + 8);
				if(strcmp(show_info, "FREE") == 0){
					printf("%d blocks (%d bytes) free\n", nblocks, nbytes);
					return;
				}
				if(strcmp(show_info, "USAGE") == 0){
					printf("%d blocks (%d bytes) used\n", ublocks, ubytes);
					printf("%d%% efficiency\n", eff);
					printf("%d%% fragmentation\n", fragm);
					return;
				}
				if(strcmp(show_info, "ALLOCATIONS") == 0){
					printf("OCCUPIED %d bytes\n", oalloc);
					if(b_liberi > 0){
						printf("FREE %d bytes\n", b_liberi);
					}
					return;
				}
			}
		}else{
			if(index == 0){		//Pentru blocul indexului de start
				b_liberi = CI(index) - 4;
				if(b_liberi > 0){
					nblocks = nblocks + 1;
					nbytes = nbytes + b_liberi;
				}
				if(strcmp(show_info, "ALLOCATIONS") == 0){
					if(b_liberi > 0){
						printf("FREE %d bytes\n", b_liberi);
					}
				}
			}else{			//Pentru orice bloc intermadiar intre index 0 si ultimul bloc			
				b_liberi = CI(index) - index - CI(index + 8);
				if(b_liberi > 0){
					nblocks = nblocks + 1;
					nbytes = nbytes + b_liberi;
				}
				ublocks = ublocks + 1;
				ubytes = ubytes + CI(index + 8) - 12;
				oalloc = CI(index + 8);
				if(strcmp(show_info, "ALLOCATIONS") == 0){
					printf("OCCUPIED %d bytes\n", oalloc);
					if(b_liberi > 0){
						printf("FREE %d bytes\n", b_liberi);
					}
				}
			}
		}
	index = CI(index);		//Sare la urmatorul bloc
	}
}
