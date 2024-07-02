#include <stdio.h>

void convert_to_protein(char gene[]);

int main(void){

  char gene[3001]; char proteins[2901]; char finalGene[3001]; int i; char ch;

  int geneLen, proteinLen;

  /* taking inputs for the genetic code and the protein sequence */
  scanf("%c", &ch); gene[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    gene[i] = ch;
  geneLen = ++i;

  scanf("%c", &ch); proteins[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    proteins[i] = ch;
  proteinLen = ++i;


  return 0;
}

char prot_from_gene[1001];
void convert_to_protein(char gene[]){ 
  


}

