//============================================================================
// Name        : test2.cpp
// Author      : Vardanyan Andranik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "fosfitkinetika.h"
#include "gen.h"
using namespace std;
int cmpfunc (const void *, const void *);
int choice_parent(double **, double, int);
void mutation(double *, int, int, int, int, int);
double create_roulette(double **, double **, double *, int);
void krossover(double **, double **, double **, double, int, int, int, int, int, int);
void algoritm(int N, int M, int KOL_POKOLENIY, int ALL_P_MUTATION_DOWN, int ALL_P_MUTATION_UP, int P_MUTATION_DOWN, int P_MUTATION_UP){
    gen w;
    double ** roulette = new double*[M];
    double ** population = new double*[M];
    double ** new_population = new double*[M];
    double * fitness = new double[M];
    for(int i = 0; i < M; i++){
        population[i] = new double[N];
        new_population[i] = new double[N];
        roulette[i] = new double[2];
    }

    ifstream file("gran.txt");
    ofstream file_save("population.txt");
    if (file.fail()){
       cout << "РћС€РёР±РєР° РѕС‚РєСЂС‹С‚РёСЏ gran.txt" << endl;
       exit(1);
    }
    double gran[N][4];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < 4; j++)
            file >> gran[i][j];
    file.close();

    srand(time(0));
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++)
            population[i][j] = gran[j][0] * pow(10,gran[j][1]) + rand() * (gran[j][2] * pow(10,gran[j][3]) - gran[j][0] * pow(10,gran[j][1])) /(double)RAND_MAX;
    }

    for(int j = 0; j < KOL_POKOLENIY; j++){
        file_save << "pokolenie: " << j + 1 << endl;
        for(int i = 0; i < M; i++){
            for(int k = 0; k < N; k++)
                file_save << population[i][k] << " ";
           file_save << endl;
        }
        file_save << endl;
        double roulette_sum = 0;
        roulette_sum = create_roulette(roulette, population, fitness, M);
        krossover(population, new_population, roulette, roulette_sum, M, N, ALL_P_MUTATION_DOWN, ALL_P_MUTATION_UP, P_MUTATION_DOWN, P_MUTATION_UP);
    }
    file_save.close();

    for(int i = 0; i < M; i++){
        delete []population[i];
        delete []roulette[i];
        delete []new_population[i];
    }
    QMessageBox msgBox;
    msgBox.setText("РљРѕРЅРµС† СЂР°СЃС‡РµС‚Р°");
    msgBox.exec();
    delete []new_population;
    delete []roulette;
    delete []population;
    delete []fitness;
}
int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
double create_roulette(double ** roulette, double ** population, double * fitness, int M){
    double roulette_sum = 0;
    for(int i = 0; i < M; i++){
        fitness[i] = F_SUM(population[i]);
        roulette_sum += fitness[i];
    }
    qsort(fitness, M , sizeof(double), cmpfunc);
    for(int i = 0; i < M; i++){
        roulette[i][0] = fitness[i];
        roulette[i][1] = fitness[i + 1];
    }
    return roulette_sum;
}
int choice_parent(double ** roulette, double x, int M){
    for(int i = 0; i < M; i++)
        if((x >= roulette[i][0]) && (x < roulette[i][1]))
            return i;
    return 0;
}
void mutation(double * population, int N, int ALL_P_MUTATION_DOWN, int ALL_P_MUTATION_UP, int P_MUTATION_DOWN, int P_MUTATION_UP){
    int all_p_mutation = rand() % 100;
    if((all_p_mutation > ALL_P_MUTATION_DOWN) && (all_p_mutation <= ALL_P_MUTATION_UP)){
        for(int b = 0; b < N; b++){
            int p_mutation = rand() % 100;
            if((p_mutation > P_MUTATION_DOWN) && (p_mutation <= P_MUTATION_UP)){
                double a = (population[b] - population[b] * 5 / 100.0);
                double c = (population[b] + population[b] * 5 / 100.0);
                if(a < c)
                    population[b] = a + rand() * (c - a) / (double)RAND_MAX;
                else
                    population[b] = c + rand() * (a - c) / (double)RAND_MAX;
            }
        }
    }
}
void krossover(double ** population, double ** new_population, double ** roulette, double roulette_sum, int M, int N, int ALL_P_MUTATION_DOWN, int ALL_P_MUTATION_UP, int P_MUTATION_DOWN, int P_MUTATION_UP){
    for(int g = 0; g < M; g += 2){
        int x_dad = rand() % int(roulette_sum), x_mom = rand() % int(roulette_sum), dad = choice_parent(roulette, x_dad, M), mom = choice_parent(roulette, x_mom, M), krossover_variant;
        double parents[2][N], child[2][N];
        krossover_variant = rand() % 3;
        for(int b = 0; b < N; b++){
            parents[0][b] = population[dad][b];
            parents[1][b] = population[mom][b];
        }
        switch (krossover_variant){
        case 0:
            for(int b = 0; b < N / 2; b++){
                child[0][b] = parents[1][b];
                child[1][b] = parents[0][b];
            }
            for(int b = N / 2; b < N; b++){
                child[0][b] = parents[0][b];
                child[1][b] = parents[1][b];
            }
            break;
        case 1:
            for(int b = 0; b < N; b++){
                if(b % 2 == 0){
                    child[0][b] = parents[0][b];
                    child[1][b] = parents[1][b];
                }
                else {
                    child[1][b] = parents[0][b];
                    child[0][b] = parents[1][b];
                }
            }
            break;
        case 2:
            int point_division = rand() % N;
            for(int b = 0; b < point_division; b++){
                child[0][b] = parents[0][b];
                child[1][b] = parents[1][b];
            }
            for(int b = point_division; b < N; b++){
                child[0][b] = parents[1][b];
                child[1][b] = parents[0][b];
            }
            break;
        }
        for(int i = 0; i < 2; i++)
            mutation(child[i], N, ALL_P_MUTATION_DOWN, ALL_P_MUTATION_UP, P_MUTATION_DOWN, P_MUTATION_UP);
        for(int i = 0; i < N; i++){
            new_population[g][i] = child[0][i];
            new_population[g + 1][i] = child[1][i];
        }
    }
    for(int i = 0; i < M; i++)
        for(int k = 0; k < N; k++)
            population[i][k] = new_population[i][k];
}
