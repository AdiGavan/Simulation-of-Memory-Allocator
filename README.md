Nume: Gavan Adrian George

Grupa: 314CA

Tema 3: Alocator de memorie

Informatii generale:
====================

- Asa cum s-a aflat acum 2 saptamani, locuitorii din Codeland sunt in razboi 
deschis cu barbarii din Common Town. Aceștia din urmă sunt însă cei care, cu 
mulți ani înainte de trecerea la un stil de viață beligerant, erau recunoscuți 
pentru înclinația lor către știință. Aceea a fost perioada în care au scris 
biblioteca stdlib. Odată cu începerea războiului, locuitorii din Codeland s-au 
văzut nevoiți să renunțe la folosirea acestei biblioteci. Totuși, pentru a 
putea efectua calculele necesare pentru viața de zi cu zi, ei sunt obligați de 
împrejurări să își scrie ei înșiși funcțiile de care au nevoie. Momentan, 
prioritatea o reprezintă funcțiile pentru alocarea dinamică a memoriei. Ajutați-i 
pe locuitorii din Codeland să implementeze funcțiile de care au nevoie.
-Programul reprezinta solutia cautata de cei din Codeland, pentru ca simuleaza 
un sistem de alocare de memorie. Programul primeste la intrare diverse comenzi 
(alocare, alterare, afisare si eliberare de memorie), iar programul furnizeaza 
la iesire rezultatul fiecarei comenzi.

Prezentarea implementarii:
==========================

- Functiile folosite pentru implementarea temei:
1) Functie pentru determinarea valorii intregului aflat la index:
int CI(int index);
2) Functie care verifica daca este spatiu intre blocuri:
int Is_Space(int index, int alloc_size, int N);
3) Funtia pentru comanda INITIALIZE:
void initialize(int numar);
4) Functie pentru comanda FINALIZE:
void finalize();
5) Functie pentru comanda DUMP:
void dump(int numar);
6) Functie pentru comanda ALLOC:
void alloc(int N, int alloc_size);
7) Functie pentru comanda FREE:
void FREE(int index);
8) Functie pentru comanda FILL:
void FILL(int index, int fill_size, int fill_value);
9) Functie pentru comanda SHOW (FREE/USAGE/ALLOCATIONS):
void SHOW(int N, char show_info[]);

- Pentru simplitatea codului si usurinta de citire se va folosi o variabila globala:
unsigned char *arena;

Algoritm:
- Se dau antetele functiilor.
- Se declara variabilele folosite in main().
- Se creeaza un loop infinit care citeste comenzile date la intrate.
- Prima data se va citi comanda INITIALIZE <N> ce va aloca dinamic memorie;
- In functie de comanda primita programul va intra pe unda din ramurile specificate
in main().
- Programul va executa functia respectiva comenzii apelate.
- Cand se va citit FINALIZE se va iesi din program, eliberandu-se memoria.
- Comanda DUMP va afisa in functie de conditiile cerintei toti octetii din memorie.
Se foloseste un for, iar pentru ultimele 2 linii se afiseaza separat, pentru ca penultima 
linie poate sa nu aiba un numar de 16 octeti, iar ultima linie reprezinta memoria 
alocata.
- Comand ALLOC adauga un numar dat de octeti in memorie. Se are in vedere faptul ca
trebuie afisat indexul sectiunii de date din noul bloc. Se intalnesc 4 cazuri:
cand arena este goala, cand se adauga un bloc la final, daca este loc intre blocul
indexului de start si primul bloc, daca este loc intre 2 blocuri.
Indexul se va incrementa, sarind la urmatorul bloc.
- Comanda FREE elibereaza un bloc de memorie, modificand datele de gestiune ale
blocului anderior si urmator. De asemenea, se intalnesc 2 cazuri: pentru cand 
este sau nu este ultimul bloc.
- Comanda FILL seteaza un numar de octeti consecutivi din arena. Aceasta functie 
poate modifica si datele de gestiune, dar print textul temei se asigura ca datele 
de intrare nu vor corupe arena.
- Comanda SHOW contine 3 parti: FREE, USAGE, ALLOCATIONS. S-a realizat o sigura 
functie care contine toate cele 3 parti, functia avand 4 cazuri (arena goala, 
ultimul bloc, pentru indexul de start, orice bloc intermediar) care asigura 
faptul ca se vor afisa doar datele cerute de catre functia data la intrare.
- Functiile CI si Is_Space sunt functii realizate pentru a usura modul de scriere 
al programului. Prima intoarce o valoare intreaga corespunzatoare indexului curent 
si functia Is_Space verifica (indiferent de caz) daca este suficient spatiu pentru 
blocul ce trebuie adaugat.

Conditii impuse de tema:
========================

- Nu se va  înlocui sistemul standard malloc() şi free(), ci se va baza pe el, 
alocând la început un bloc mare de memorie, şi apoi presupunând că acela 
reprezintă toată “memoria”, care trebuie gestionata.
- Programul nu va trebui să afişeze nimic altceva în afara formatului specificat 
(de exemplu, nu trebuie să afişati mesaje de tipul “Introduceţi comanda: ”).
- Se va implementa executia fiecarei comenzi intr-o functie.

