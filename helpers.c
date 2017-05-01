#include "helpers.h"

void print_table(int** table, char** text1, char** text2, int i, int j)
{
  if (i > 0 && j > 0 && (strcmp(text1[i-1], text2[j-1]) == 0))
  {
    print_table(table, text1, text2, i-1, j-1);
    printf(" %s", text1[i-1]);
  }
  else if (j > 0 && (i == 0 || table[i][j-1] < table[i-1][j]))
  {
    print_table(table, text1, text2, i, j-1);
    printf("+%s\n", text2[j-1]);
  }
  else if(i > 0 && (j == 0 || table[i][j-1] >= table[i-1][j]))
  {
    print_table(table, text1, text2, i-1, j);
    printf("-%s\n", text1[i-1]);
  }
}
