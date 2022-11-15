#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define NUM_PTHREADS 4
int matrixA[10000][10000];
int matrixB[10000][10000];
int answer[10000][10000];
int N;
int cnt;
FILE *fp;
FILE *fs;

void init()
{
  printf("%d", N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      fscanf(fp,"%d",&matrixA[i][j]);

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      fscanf(fp,"%d",&matrixB[i][j]);
}

void *_suma(void *args)
{
  long  i = (long)args;
  for (int k = i; k < i + cnt && k < N; k++){
    for (int j = 0; j < N; j++)
      answer[k][j] = matrixA[k][j] + matrixB[k][j];
  }
}

void *_resta(void *args)
{
  long  i = (long)args;
  for (int k = i; k < i + cnt && k < N; k++){
    for (int j = 0; j < N; j++)
      answer[k][j] = matrixA[k][j] - matrixB[k][j];
  }
}

void *_multiplication(void *args)
{
  long  i = (long) args;
  int aux , fin = i + cnt;
  if(i == (3 * cnt)) fin = N;
    for (int m = i; m < fin && m < N; m++)
    {
      for (int k = 0; k < N ; k++)
      {
        aux = 0;
        for (int j = 0; j < N; j++)
          aux += matrixA[m][j] * matrixB[k][j];
        answer[m][k] = aux;
      }
    }
}

void trasposeMatrix()
{
  for(int i = 0 ; i < (N - 1) ; i++) {
    for(int j = i + 1 ; j < N ; j++) {
      int aux = matrixB[i][j];
      matrixB[i][j] = matrixB[j][i];
      matrixB[j][i] = aux;
    }
  }
}

void _print(int A[][10000])
{
    printf("\n");
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
        printf("%d ", A[i][j]);
      printf("\n");
    }
    printf("\n");
}

int main()
{
  clock_t t0, t1;
  int T , x ;
  long l;
  double time;
  fs = fopen("times2.txt", "w");
  if ((fp = fopen("matrixs.txt", "r")) != NULL)
  {
    fscanf(fp ,"%d" , &T);
    while(T--) {
      fscanf(fp, "%d" , &N);
      init();
      cnt = N / NUM_PTHREADS;
      if(N % NUM_PTHREADS > 2)
        cnt++;

      //------------Adición------------------//
      t0 = clock();
        pthread_t idPlus[NUM_PTHREADS];
        x = 0 , l = -cnt;
        for (long i = 0; i < NUM_PTHREADS; i++)
          pthread_create(&idPlus[x++], NULL, _suma, (void *)(l+=cnt));
        for (long i = 0; i < NUM_PTHREADS; i++)
          pthread_join(idPlus[i], NULL);
      t1 = clock();
      time = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
      fprintf(fs ,"%d %f\n" ,N , time);
      printf("Resultado de la Adición(USANDO HILOS)\n");
      _print(answer);
    
      
      //------------Sustracción---------------//
      t0 = clock();
        pthread_t idMinus[NUM_PTHREADS];
        x = 0, l = -cnt;
        for (long i = 0; i < NUM_PTHREADS; i++)
          pthread_create(&idMinus[x++], NULL, _resta, (void *)(l+=cnt));
       for (long i = 0; i < NUM_PTHREADS; i++)
          pthread_join(idMinus[i], NULL);
      t1 = clock();
      time = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
     fprintf(fs ,"%d %f\n" ,N , time);
     printf("Resultado de la Sustracción(USANDO HILOS)\n");
     _print(answer);

     //------------Multiplicación-------------//
     t0 = clock();
      pthread_t idProduct[NUM_PTHREADS];
      trasposeMatrix();
      x = 0 ,l = -cnt;
      for (long i = 0; i < NUM_PTHREADS; i++)
        pthread_create(&idProduct[x++], NULL, _multiplication, (void *)(l+=cnt));
      for (long i = 0; i < NUM_PTHREADS; i++)
        pthread_join(idProduct[i], NULL);
     t1 = clock();
     time = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
     fprintf(fs, "%d %f\n", N, time);
     printf("Resultado de la Producto(USANDO HILOS)\n");
     _print(answer);
    }
    fclose(fp);
  }
  return 0;
}

