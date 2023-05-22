#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "competition.h"
#include "queue.h"

int n;

bool IsGood(char ch)
{
    return (isalpha(ch) || isdigit(ch) || ch == '%'); /// verificam daca caracterul curent este bun (adica: cifra, litera, sau % )
}

char *get_string(char sep, FILE *f) /// aici: extragem un string si returnam pointerul coresp.
{
    char ch = 0; /// sep = space sau newline, f = file-ul din care citesc string ul

    char *s = calloc(128, sizeof(char)); /// alocam initial un string care are 128 de caractere
    int size = 0, capacity = 128;        /// size = cate caractere am pus pana acum, capacity = [# maxim de caractere suportate in string ]

    while (1)
    {
        fscanf(f, "%c", &ch); /// citim caracter cu caracter
        if (ch == sep)        /// am atins un caracter separator (stop!)
            break;

        if ((++size) > capacity)                                    /// nu e separator, adica avem inca un caracter "bun", de adaugat la string; size > capacity -> e nevoie sa dublam stringul
            capacity *= 2, s = realloc(s, capacity * sizeof(char)); /// dublam stringul, folosim functia realloc()

        s[(size - 1)] = ch; /// se adauga noul caracter procesat (la finalul stringului)
    }

    /// Am remarcat ca unele nume de echipe au mai multe spatii la final (exemplu: "amelie   ", spatiile trebuie taiate):
    if (sep == '\n') /// sep == '\n' inseamna ca acum extrag un nume de echipa (nu nume de player, cand sep va fi egal cu spatiu ' ')
    {
        while ((size - 1) >= 0 && !IsGood(s[(size - 1)])) /// taiem de la final, cat timp se poate, spatii sau caractere care nu se "vad"
            s[(size - 1)] = 0, --size;                    /// scoatem ce nu trebuie, pe rand, de la finalul stringului s[]
    }
    ///

    if ((++size) > capacity)
        capacity *= 2, s = realloc(s, capacity * sizeof(char)); ///  realocam memoria

    for (int x = (size - 1); x < capacity; ++x) /// avem grija ca tot ce este in intervalul [size, ..., capacity] sa fie cu '\000'
        s[x] = 0;
    /// EXEMPLU: daca s a ajuns cu o capacitate de 16, dar eu am doar 11, inseamna ca ultimele 5 caractere trebuie sa fie 0

    return s; /// returnam stringul rezultat (un singur "cuvant": team_name, or first_name, or last_name)
}

void print_string(char *s, FILE *f, bool flag, int var) /// functie ce printeaza corespunzator numele echipelor
{
    int needed_spaces = var - (int)strlen(s); /// cate spatii mai trebuie adaugate
    /// target [# de caractere in total (caractere din numele echipei + spatii)] = var;

    if (!flag)
    {
        fprintf(f, "%s", s);                     /// mai intai, numele echipei
        for (int i = 1; i <= needed_spaces; ++i) /// apoi, multe spatii
            fprintf(f, " ");
    }
    else
    {
        for (int i = 1; i <= needed_spaces; ++i) /// mai intai, multe spatii
            fprintf(f, " ");
        fprintf(f, "%s", s); /// apoi, numele echipei
    }

    return;
}

void print_float(long double X, FILE *f) /// functie ce afiseaza in fisierul "f" float-ul X
{
    fprintf(f, "%.2f", (float)X); /// afisare cu doua zecimale

    return;
}

bool EPutereDeDoi(int n) /// functie ce verifica daca n este putere de doi
{
    while (n % 2 == 0)
        n /= 2;
    if (n == 1)
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *c_file = fopen(argv[1], "r"); /// fisierul "c.in"
    FILE *d_file = fopen(argv[2], "r"); /// fisierul "d.in"
    FILE *e_file = fopen(argv[3], "w"); /// fisierul "r.out"

    int task_1 = 0, task_2 = 0, task_3 = 0, task_4 = 0, task_5 = 0; /// trebuie sa vedem ce cerinta e de rezolvat
    fscanf(c_file, "%d", &task_1);
    fscanf(c_file, "%d", &task_2);
    fscanf(c_file, "%d", &task_3);
    fscanf(c_file, "%d", &task_4);
    fscanf(c_file, "%d", &task_5);

    fscanf(d_file, "%d", &n); /// [# nr de echipe din competitie]

    competition *comp = competition_create(); /// o noua competitie e creata
    comp->n = n;                              /// competitia are (acum) n echipe care participa

    for (int i = 1; i <= n; ++i) /// se citeste fiecare echipa
    {
        team *t = team_create();                /// o noua echipa
        t->next = comp->first, comp->first = t; /// se adauga echipa la inceputul competitiei (care este o lista simplu inlantuita)

        fscanf(d_file, "%d", &(t->n)); /// [# de participanti/players din echipa actuala]

        char ch = 0;
        fscanf(d_file, "%c", &ch); /// se citeste primul spatiu, care este inainte de team name

        t->name = get_string('\n', d_file); /// se citeste numele echipei

        for (int j = 1; j <= (t->n); ++j)
        {
            node *now = node_create();            /// un nou nod (ex: un nou player)
            now->next = t->first, t->first = now; /// ca si in cazul de mai sus: team-competition, aici se adauga un player nou la inceputul listei (simplu) inlantuite ce reprezinta o echipa

            now->X.firstName = get_string(' ', d_file), now->X.secondName = get_string(' ', d_file);
            /// se citesc (doua) nume pentru fiecare player in parte
            fscanf(d_file, "%d", &(now->X.points)); /// se citeste (un int) care sa reprezinte [# de puncte ptr. fiecare player]

            t->sum += (now->X.points); /// t->sum = [# total de puncte ale tuturor jucatorilor din echipa]
        }

        t->avg = (long double)((long double)t->sum) / ((long double)t->n); /// folosim "long double" ptr. ca calculam fractii  (nu sunt mereu intregi)

        fscanf(d_file, "%c", &ch); /// se citeste un newline, care separa doua echipe intre ele
    }

    if (task_2) /// avem de sters din [# de echipe], pana ce (acesta) devine putere de doi
        while (!EPutereDeDoi(comp->n))
            competition_remove_min(comp); /// se sterge din competitie echipa ce are coeff cel mai mic

    if (task_1) /// avem si cerinta 1 activa, prin urmare trebuie afisata lista cu echipele (ramase dupa line #126)
    {
        for (team *i = comp->first; i != NULL; i = i->next) /// se itereaza, one-by-one, prin lista de echipe, si se printeaza numele
            fprintf(e_file, "%s\n", i->name);               /// print name
    }

    if (task_3) /// avem de rezolvat si cerinta 3, se simuleaza tournamentul
    {
        fprintf(e_file, "\n"); /// print newline

        n = comp->n; /// [# de echipe din competitie, initial]

        queue *Q = queue_create(); /// se creeaza o coada

        for (team *i = comp->first; i != NULL; i = i->next) /// se adauga in coada echipele
        {
            nodeq *curr = nodeq_create();
            curr->X = i; /// echipa "curenta" are "valoarea" i: echipa de acum din iterarea prin lista

            queue_enque(Q, curr); /// se adauga in coada echipa
        }

        for (int round = 1; n > 1; ++round) /// jucam pana mai avem o singura echipa
        {
            fprintf(e_file, "--- ROUND NO:%d\n", round); /// [# rundei curente]

            queue *S = queue_create();         /// coada "WINNERS"
            queue *to_delete = queue_create(); /// coada "NOT WINNERS"

            for (int i = 1; i <= (n / 2); ++i) /// luam, in ordine, match-urile
            {
                nodeq *a = queue_deque(Q);               /// prima echipa din match
                print_string(a->X->name, e_file, 0, 33); /// printam numele echipei "a"

                fprintf(e_file, "-"); /// necesar din formatul fisierelor

                nodeq *b = queue_deque(Q);               /// a doua echipa din match
                print_string(b->X->name, e_file, 1, 33); /// printam numele echipei "b"

                fprintf(e_file, "\n");

                if (a->X->avg > b->X->avg) /// team "a" a batut team "b"
                    a->X->avg += (long double)1.0, queue_enque(S, a), queue_enque(to_delete, b);
                else /// team "b" a batut team "a"
                    b->X->avg += (long double)1.0, queue_enque(S, b), queue_enque(to_delete, a);
            }

            fprintf(e_file, "\n");
            fprintf(e_file, "WINNERS OF ROUND NO:%d\n", round); /// se vor afisa castigatorii rundei curente, folosim stiva (implementata ca lista dublu inlantuita)

            for (int j = 1; j <= (n / 2); ++j) /// parcurgem stiva de "WINNERS"
            {
                nodeq *top = queue_pop(S); /// "top" este varful din stiva

                print_string(top->X->name, e_file, 0, 34); /// printam numele echipei de acum (care a castigat)
                fprintf(e_file, "-  ");                    /// caracter de separation intre numele echipei si score-ul ei
                print_float(top->X->avg, e_file);          /// score-ul cu care echipa a castigat (update-ul cu +1 puncte s-a efectuat la lines #197 sau #199)

                fprintf(e_file, "\n"); /// final de linie, means newline

                queue_enque(Q, top); /// se readauga in coada de match-uri de disputat echipa care a castigat (si avanseaza la urmatoarea runda)
            }

            n /= 2; /// din n echipe (putere de doi), mai raman n/2 echipe (tot putere de doi, inductiv)

            if (n > 1)                 /// mai avem runde de jucat
                fprintf(e_file, "\n"); /// afisam un newline

            queue_destroy(S);         /// dezalocam memoria de la stiva cu cei care au castigat
            queue_destroy(to_delete); /// deazlocam memoria de la stiva cu cei care NU au castigat
        }

        queue_destroy(Q); /// dezalocam memoria de la coada cu care am simulat match-urile jucate
    }

    competition_destroy(comp); /// dezalocam memoria de la structura de date cu care am simulat "competitia"

    fclose(c_file), fclose(d_file), fclose(e_file); /// nu uitam sa "inchidem" cele 3 fisiere (2 de input, 1 de output)

    return 0;
}
