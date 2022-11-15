#include <bits/stdc++.h>

using namespace std;

int matrixA[10000][10000];
int matrixB[10000][10000];
int answer[10000][10000];
ifstream file("matrixs.txt");
int N;
FILE *fp;
FILE *fs;

void init()
{
  printf("%d", N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      fscanf(fp, "%d", &matrixA[i][j]);

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      fscanf(fp, "%d", &matrixB[i][j]);
}

void suma()
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      answer[i][j] = matrixA[i][j] + matrixB[i][j];
}

void resta()
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      answer[i][j] = matrixA[i][j] - matrixB[i][j];
}

void multiplicacion()
{
  int aux = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N - 1; k++)
        answer[i][j] += matrixA[i][k] * matrixB[k][j];
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
  int T;
  double time;

  fs = fopen("times1.txt", "w");
  if ((fp = fopen("matrixs.txt", "r")) != NULL)
  {
    fscanf(fp, "%d", &T);
    while (T--)
    {
      fscanf(fp, "%d", &N);
      init();
      // _print(matrixA);
      // _print(matrixB);

      t0 = clock();
      suma();
      t1 = clock();
      time = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
      fprintf(fs, "%d %f\n", N, time);
      cout<<N<<" "<<time<<"\n";
      //cout << "Resultado de la Suma(FORMA TRADICIONAL)"<< "\n";
      // _print(answer);

      t0 = clock();
      resta();
      t1 = clock();
      time = (double(t1 - t0)) / CLOCKS_PER_SEC;
      fprintf(fs, "%d %f\n", N, time);
      cout<<N<<" "<<time<<"\n";
      // cout << "Resultado de la Resta(FORMA TRADICIONAL)"
      //      << "\n";
      //_print(answer);

      t0 = clock();
      multiplicacion();
      t1 = clock();
      time = (double(t1 - t0)) / CLOCKS_PER_SEC;
      fprintf(fs, "%d %f\n", N, time);
      cout<<N<<" "<<time<<"\n";
      //cout << "Resultado del Producto(FORMA TRADICIONAL)";
            //<< "\n";
      //_print(answer);
    }
  }

  return 0;
}