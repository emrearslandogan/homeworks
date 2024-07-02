#include <stdio.h>

char converter(char nc1, char nc2, char nc3);

int main(){

  char gene[3001]; char protein[2901]; char finalGene[3001]; int i,j,k; char ch;
  int geneLen, proteinLen, missing_prots;
  int first_intron[2];
  int second_intron[2];

  /* taking inputs for the genetic code and the protein sequence */
  scanf("%c", &ch); gene[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    gene[i] = ch;
  geneLen = i;

  scanf(" %c", &ch); protein[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    protein[i] = ch;
  proteinLen = i;
  
  if (proteinLen *3 > geneLen){
    printf("NONE\n"); return 0;
  }

  /* Converting the genetic code to mRNA code */
  for (i = 0; i < geneLen; i++)
    switch(gene[i]){
      case 'A':   gene[i] = 'U'; break;
      case 'T':   gene[i] = 'A'; break;
      case 'G':   gene[i] = 'C'; break;
      case 'C':   gene[i] = 'G'; break;
    }

  /* Scanning from the beginning, works for sample input */
  for (i = 0; i < proteinLen; i++)
    if (!(converter(gene[3*i], gene[3*i+1], gene[3*i+2]) == protein[i])) break;

  if (i == proteinLen -2 && i != 1) /* we don't want to find all aa's from the first exon */
    first_intron[0] = 3 * (i-1);
  else
    first_intron[0] = 3*i; 
  
  
  /* Scanning from the end, works for sample input */
  for (i = 2; i < proteinLen ; i++){ /* we have stop codon at the end */
    if (!(converter(gene[geneLen - 3*i ], gene[geneLen - 3*i +1], gene[geneLen - 3*i +2]) == protein[proteinLen - i + 1])) break;
  }

  second_intron[1] = geneLen - 3*i +2;
  missing_prots = proteinLen - (first_intron[0]/3 + ((geneLen)-(second_intron[1]+3)+1)/3); /* stop codon's effect */
  
  if (missing_prots == 0){ /* if we don't have any aa left to place inside the third exon, we retract the second one with 3 steps */
    second_intron[1] = second_intron[1] + 3; 
    missing_prots++;
  }
  proteinLen = proteinLen - ((geneLen)-(second_intron[1]+3)+1)/3;


  /* Then, we need to find the third exon */
  for (i = first_intron[0]; i <= second_intron[1]; i++){ 
    for (j = i, k = first_intron[0]/3; j <= second_intron[1] && k < proteinLen; j = j+3){
      if ((converter(gene[j], gene[j+1], gene[j+2]) == protein[k]))  k++;
      else  break;
    }
    if ((j-i)/3 == missing_prots && i-1 >= first_intron[0]){
      first_intron[1] = i-1;
      second_intron[0] = j;
      break;
    }
  }

  /* Output part */
  if (first_intron[0] != 0 && first_intron[0] <= first_intron[1] && second_intron[0] <= second_intron[1]) 
    printf("%d %d %d %d\n", first_intron[0], first_intron[1], second_intron[0], second_intron[1]);
  else if (!(gene[geneLen -3] == 'U' && ((gene[geneLen -2] == 'A' && (gene[geneLen-1] == 'A' || gene[geneLen-1] == 'G')) || (gene[geneLen-2] == 'G' && gene[geneLen-1] == 'A'))))
    printf("NONE\n"); /* stop codon does not exist*/  
  else  printf("NONE\n");

  return 0;
}

char converter(char nc1, char nc2, char nc3){
  /* phe */
  if (nc1 == 'U' && nc2 == 'U' && (nc3 == 'U' || nc3 == 'C')) return 'f';

  /* leu */
  if ((nc1 == 'U' && nc2 == 'U' && (nc3 == 'A' || nc3 == 'G')) || (nc1 == 'C' && nc2 == 'U'))  return 'l';

  /* ile */
  if (nc1 == 'A' && nc2 == 'U' && !(nc3 == 'G'))  return 'i';

  /* met */
  if (nc1 == 'A' && nc2 == 'U' && nc3 == 'G')  return 'm';

  /* val */
  if (nc1 == 'G' && nc2 == 'U')  return 'v';

  /* pro */
  if (nc1 == 'C' && nc2 == 'C')  return 'p';

  /* thr */
  if (nc1 == 'A' && nc2 == 'C')  return 't';

  /* ala */
  if (nc1 == 'G' && nc2 == 'C')  return 'a';

  /* tyr */
  if (nc1 == 'U' && nc2 == 'A' && (nc3 == 'U' || nc3 == 'C'))  return 'y';

  /* his */
  if (nc1 == 'C' && nc2 == 'A' && (nc3 == 'U' || nc3 == 'C'))  return 'h';

  /* gln */
  if (nc1 == 'C' && nc2 == 'A' && (nc3 == 'A' || nc3 == 'G'))  return 'q';

  /* asn */
  if (nc1 == 'A' && nc2 == 'A' && (nc3 == 'U' || nc3 == 'C'))  return 'n';

  /* lys */
  if (nc1 == 'A' && nc2 == 'A' && (nc3 == 'A' || nc3 == 'G'))  return 'k';

  /* asp */
  if (nc1 == 'G' && nc2 == 'A' && (nc3 == 'U' || nc3 == 'C'))  return 'd';

  /* glu */
  if (nc1 == 'G' && nc2 == 'A' && (nc3 == 'A' || nc3 == 'G'))  return 'e';

  /* cys */
  if (nc1 == 'U' && nc2 == 'G' && (nc3 == 'U' || nc3 == 'C'))  return 'c';

  /* trp */
  if (nc1 == 'U' && nc2 == 'G' && nc3 == 'G')  return 'w';

  /* arg */
  if ((nc1 == 'C' && nc2 == 'G') || (nc1 == 'A' && nc2 == 'G' && (nc3 == 'A' || nc3 == 'G')))  return 'r';

  /* ser */
  if ((nc1 == 'U' && nc2 == 'C') || (nc1 == 'A' && nc2 == 'G' && (nc3 == 'U' || nc3 == 'C')))  return 's';

  /* gly */
  if (nc1 == 'G' && nc2 == 'G')  return 'g';    

}