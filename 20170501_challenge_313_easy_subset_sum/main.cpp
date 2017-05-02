#include <stdio.h>

const int INPUT_LEN = 18;
const int INPUT_COUNT = 6;

int input[INPUT_COUNT][INPUT_LEN] = {
   {1, 2, 3},
   {-5, -3, -1, 2, 4, 6},
   {},
   { -1, 1 },
   { -97364, -71561, -69336, 19675, 71561, 97863 },
   { -53974, -39140, -36561, -23935, -15680, 0 }
};

bool ProcessInput(int * in)
{
   for (int j = 0; j < INPUT_LEN; j++)
   {
      for (int k = j; k < INPUT_LEN; k++)
      {
         if (j != k && in[j] + in[k] == 0 && in[j] != 0)
            return true;
      }
   }

   return false;
}

void main()
{
   for (int i = 0; i < INPUT_COUNT; i++)
   {
      if (ProcessInput(input[i])) { printf("true\n"); }
      else { printf("false\n"); }
   }

   getchar();
}