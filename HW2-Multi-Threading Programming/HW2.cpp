# include <iostream>
# include <thread>
# include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
# define MAX 500
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
int row = 0;
int q = 10;
pthread_mutex_t count_mutex;

void* a_m(void* arg){
    // Multiplication -> matD
    int i;
    int flag = 0;
    while(1){
        pthread_mutex_lock(&count_mutex);
        i = row++;
        if(row > 500){
            flag = 1;
        }
        pthread_mutex_unlock(&count_mutex);
        if(flag){
            break;
        }
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            matC[i][j] = matA[i][j] + matB[i][j];
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }     
    }
    pthread_exit(NULL);
}

int main(){
    cin.tie(0);
	cin.sync_with_stdio(0);
    // get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }
    pthread_t t[q];
    for(int i = 0; i < q; i++){
        pthread_create(&t[i], NULL, a_m, &i);
    }
    for(int i = 0; i < q; i++){
        pthread_join(t[i], NULL);  
    }
    //cout<<"thread number: "<<q<<"\n";
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C +=  matC[i][j];     
    }
    cout << sum_C << "\n";
    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    cout << sum_D << "\n";
    return 0;
}