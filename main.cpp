#include <bits/stdc++.h>
using namespace std;

int main()
{

  ofstream file("matrixs.txt");
  int T = 14;
  int N[] = {100, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000};
  file << T << "\n";
  for (int i = 0; i < T; i++)
  {
    file << N[i] << "\n";
    for (int j = 0; j < N[i]; j++)
    {
      for (int k = 0; k < N[i]; k++)
      {
        file << 1 + rand() % 100 << " ";
      }
      file << "\n";
    }

    file << "\n";

    for (int j = 0; j < N[i]; j++)
    {
      for (int k = 0; k < N[i]; k++)
      {
        file << 1 + rand() % 100 << " ";
      }
      file << "\n";
    }

    file << "\n";
  }

  return 0;
}