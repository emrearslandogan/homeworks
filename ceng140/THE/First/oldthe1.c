#include <stdio.h>

int main(void){

  char gene[3001]; char proteins[2901]; char finalGene[3001]; int i,j, k; char ch;
  int geneLen, proteinLen, missing_prots, control;
  char searched_aa;
  int first_intron[2];
  int second_intron[2];

  /* taking inputs for the genetic code and the protein sequence */
  scanf("%c", &ch); gene[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    gene[i] = ch;
  geneLen = ++i;

  scanf(" %c", &ch); proteins[0] = ch;
  for (i = 1; scanf(" %c", &ch), ch != '.'; i++)
    proteins[i] = ch;
  proteinLen = ++i;
  
  /*##
  for (i = 0; i < proteinLen; i++)
    printf("%c,", proteins[i]);
  printf("\n");
  */

  control = 1;
  /* Converting the genetic code to mRNA code */
  for (i = 0; i < geneLen; i++)
    switch(gene[i]){
      case 'A':
        gene[i] = 'U'; break;
      
      case 'T':
        gene[i] = 'A'; break;

      case 'G':
        gene[i] = 'C'; break;

      case 'C':
        gene[i] = 'G'; break;
    }
  

  
  /* Comparing the genetic code and protein sequence from the beginning */
  for (i = 0; i < proteinLen; i++){
    /*## printf("(%c%c%c) %c\n", gene[3*i], gene[3*i+1], gene[3*i+2], proteins[i]);*/
    if (proteins[i] == 'f') /* phe */
      if (!(gene[3*i] == 'U' && gene[3*i+1] == 'U' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'l') /* leu */
      if (!((gene[3*i] == 'U' && gene[3*i+1] == 'U' && (gene[3*i+2] == 'A' || gene[3*i+2] == 'G')) ||
           (gene[3*i] == 'C' && gene[3*i+1] == 'U')))
        break;

    if (proteins[i] == 'i') /* ile */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'U' && !(gene[3*i+2] == 'G')))
        break;

    if (proteins[i] == 'm') /* met */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'U' && gene[3*i+2] == 'G'))
        break;

    if (proteins[i] == 'v') /* val */
      if (!(gene[3*i] == 'G' && gene[3*i+1] == 'U'))
        break;

    if (proteins[i] == 'p') /* pro */
      if (!(gene[3*i] == 'C' && gene[3*i+1] == 'C'))
        break;

    if (proteins[i] == 't') /* thr */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'C'))
        break;

    if (proteins[i] == 'a') /* ala */
      if (!(gene[3*i] == 'G' && gene[3*i+1] == 'C'))
        break;

    if (proteins[i] == 'y') /* tyr */
      if (!(gene[3*i] == 'U' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'h') /* his */
      if (!(gene[3*i] == 'C' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'q') /* gln */
      if (!(gene[3*i] == 'C' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'A' || gene[3*i+2] == 'G')))
        break;

    if (proteins[i] == 'n') /* asn */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'k') /* lys */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'A' || gene[3*i+2] == 'G')))
        break;

    if (proteins[i] == 'd') /* asp */
      if (!(gene[3*i] == 'G' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'e') /* glu */
      if (!(gene[3*i] == 'G' && gene[3*i+1] == 'A' && (gene[3*i+2] == 'A' || gene[3*i+2] == 'G')))
        break;

    if (proteins[i] == 'c') /* cys */
      if (!(gene[3*i] == 'U' && gene[3*i+1] == 'G' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'w') /* trp */
      if (!(gene[3*i] == 'U' && gene[3*i+1] == 'G' && gene[3*i+2] == 'G'))
        break;

    if (proteins[i] == 'r') /* arg */
      if (!((gene[3*i] == 'C' && gene[3*i+1] == 'G') || (gene[3*i] == 'A' && gene[3*i+1] == 'G' && (gene[3*i+2] == 'A' || gene[3*i+2] == 'G'))))
        break;

    if (proteins[i] == 's') /* ser */
      if (!(gene[3*i] == 'A' && gene[3*i+1] == 'G' && (gene[3*i+2] == 'U' || gene[3*i+2] == 'C')))
        break;

    if (proteins[i] == 'g') /* gly */
      if (!(gene[3*i] == 'G' && gene[3*i+1] == 'G'))
        break;
    
    }

  



  /* Finding the first exons ending, resulting i gives us this.*/
  first_intron[0] = 3*i;
  if (i == 0)
      control = 0;

  /* Comparing the genetic code and protein sequence from the end, in order to find the ending point of the second intron*/
  for (i = geneLen-7, j = proteinLen-2; i > 0; i = i-3, j--){ /*it's 7 bcs we don't want to deal with stop codon. If we would, it needs to be 4*/
    /*## printf("(%c%c%c) %c\n", gene[i], gene[i+1], gene[i+2], proteins[j]);*/
    if (proteins[j] == 'f') /* phe */
      if (!(gene[i] == 'U' && gene[i+1] == 'U' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'l') /* leu */
      if (!((gene[i] == 'U' && gene[i+1] == 'U' && (gene[i+2] == 'A' || gene[i+2] == 'G')) ||
           (gene[i] == 'C' && gene[i+1] == 'U')))
        break;

    if (proteins[j] == 'i') /* ile */
      if (!(gene[i] == 'A' && gene[i+1] == 'U' && !(gene[i+2] == 'G')))
        break;

    if (proteins[j] == 'm') /* met */
      if (!(gene[i] == 'A' && gene[i+1] == 'U' && gene[i+2] == 'G'))
        break;

    if (proteins[j] == 'v') /* val */
      if (!(gene[i] == 'G' && gene[i+1] == 'U'))
        break;

    if (proteins[j] == 'p') /* pro */
      if (!(gene[i] == 'C' && gene[i+1] == 'C'))
        break;

    if (proteins[j] == 't') /* thr */
      if (!(gene[i] == 'A' && gene[i+1] == 'C'))
        break;

    if (proteins[j] == 'a') /* ala */
      if (!(gene[i] == 'G' && gene[i+1] == 'C'))
        break;

    if (proteins[j] == 'y') /* tyr */
      if (!(gene[i] == 'U' && gene[i+1] == 'A' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'h') /* his */
      if (!(gene[i] == 'C' && gene[i+1] == 'A' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'q') /* gln */
      if (!(gene[i] == 'C' && gene[i+1] == 'A' && (gene[i+2] == 'A' || gene[i+2] == 'G')))
        break;

    if (proteins[j] == 'n') /* asn */
      if (!(gene[i] == 'A' && gene[i+1] == 'A' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'k') /* lys */
      if (!(gene[i] == 'A' && gene[i+1] == 'A' && (gene[i+2] == 'A' || gene[i+2] == 'G')))
        break;

    if (proteins[j] == 'd') /* asp */
      if (!(gene[i] == 'G' && gene[i+1] == 'A' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'e') /* glu */
      if (!(gene[i] == 'G' && gene[i+1] == 'A' && (gene[i+2] == 'A' || gene[i+2] == 'G')))
        break;

    if (proteins[j] == 'c') /* cys */
      if (!(gene[i] == 'U' && gene[i+1] == 'G' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'w') /* trp */
      if (!(gene[i] == 'U' && gene[i+1] == 'G' && gene[i+2] == 'G'))
        break;

    if (proteins[j] == 'r') /* arg */
      if (!((gene[i] == 'C' && gene[i+1] == 'G') || (gene[i] == 'A' && gene[i+1] == 'G' && (gene[i+2] == 'A' || gene[i+2] == 'G'))))
        break;

    if (proteins[j] == 's') /* ser */
      if (!(gene[i] == 'A' && gene[i+1] == 'G' && (gene[i+2] == 'U' || gene[i+2] == 'C')))
        break;

    if (proteins[j] == 'g') /* gly */
      if (!(gene[i] == 'G' && gene[i+1] == 'G'))
        break;    
    }
  
  second_intron[1] = i+2; /* All these ugly numbers occured because I wanted to decrease code by code instead of codon by codon while coming from back  */

  /* we can finally move into the task of finding the middle exon */
  /*printf("(%d %d)\n", geneLen, proteinLen);*/


  /* we are trying to find the first aminoacid that we couldn't get from first exon*/
  /*searched_aa = proteins[first_intron[0] /3];
  for (i = first_intron[0]; i < second_intron[1]; i+1){
  }  
*/
  
  missing_prots = (proteinLen-1) - (first_intron[0]/3 + ((geneLen-1)-(second_intron[1])+1)/3);
  /*printf("(%d, %d, %d, %d, %d, %d)", second_intron[1], geneLen, proteinLen, first_intron[0]/3 + ((geneLen-1)-(second_intron[1]+1))/3,((geneLen-1)-(second_intron[1]+1))%3, missing_prots);*/
  /* true numbers of proteins and gene is one less than geneLen and proteinLen. But it crashes compeletly when I try to change the initialization.*/
                                                                    
  /*printf("{%d}", missing_prots);*/

  /* It checks the gibberish sequence we have, and tries to find the first amino acid representation in it. After finding it, it goes until the gene and protein sequece doesn't match */
  /* If the total number of aa's found is less than needed, it starts from a different representation of the first amino acid*/

  for (i = first_intron[0]; i < second_intron[1]; i++){
    for (j = i, k = first_intron[0]/3; j < second_intron[1]; j = j+3, k++){
      /*printf("[%c%c%c, %c]", gene[j], gene[j+1], gene[j+2], proteins[k]);*/
      if (proteins[k] == 'f') /* phe */
        if (!(gene[j] == 'U' && gene[j+1] == 'U' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'l') /* leu */
        if (!((gene[j] == 'U' && gene[j+1] == 'U' && (gene[j+2] == 'A' || gene[j+2] == 'G')) ||
            (gene[j] == 'C' && gene[j+1] == 'U')))
          break;

      if (proteins[k] == 'i') /* ile */
        if (!(gene[j] == 'A' && gene[j+1] == 'U' && !(gene[j+2] == 'G')))
          break;

      if (proteins[k] == 'm') /* met */
        if (!(gene[j] == 'A' && gene[j+1] == 'U' && gene[j+2] == 'G'))
          break;

      if (proteins[k] == 'v') /* val */
        if (!(gene[j] == 'G' && gene[j+1] == 'U'))
          break;

      if (proteins[k] == 'p') /* pro */
        if (!(gene[j] == 'C' && gene[j+1] == 'C'))
          break;

      if (proteins[k] == 't') /* thr */
        if (!(gene[j] == 'A' && gene[j+1] == 'C'))
          break;

      if (proteins[k] == 'a') /* ala */
        if (!(gene[j] == 'G' && gene[j+1] == 'C'))
          break;

      if (proteins[k] == 'y') /* tyr */
        if (!(gene[j] == 'U' && gene[j+1] == 'A' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'h') /* his */
        if (!(gene[j] == 'C' && gene[j+1] == 'A' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'q') /* gln */
        if (!(gene[j] == 'C' && gene[j+1] == 'A' && (gene[j+2] == 'A' || gene[j+2] == 'G')))
          break;

      if (proteins[k] == 'n') /* asn */
        if (!(gene[j] == 'A' && gene[j+1] == 'A' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'k') /* lys */
        if (!(gene[j] == 'A' && gene[j+1] == 'A' && (gene[j+2] == 'A' || gene[j+2] == 'G')))
          break;

      if (proteins[k] == 'd') /* asp */
        if (!(gene[j] == 'G' && gene[j+1] == 'A' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'e') /* glu */
        if (!(gene[j] == 'G' && gene[j+1] == 'A' && (gene[j+2] == 'A' || gene[j+2] == 'G')))
          break;

      if (proteins[k] == 'c') /* cys */
        if (!(gene[j] == 'U' && gene[j+1] == 'G' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'w') /* trp */
        if (!(gene[j] == 'U' && gene[j+1] == 'G' && gene[j+2] == 'G'))
          break;

      if (proteins[k] == 'r') /* arg */
        if (!((gene[j] == 'C' && gene[j+1] == 'G') || (gene[j] == 'A' && gene[j+1] == 'G' && (gene[j+2] == 'A' || gene[j+2] == 'G'))))
          break;

      if (proteins[k] == 's') /* ser */
        if (!(gene[j] == 'A' && gene[j+1] == 'G' && (gene[j+2] == 'U' || gene[j+2] == 'C')))
          break;

      if (proteins[k] == 'g') /* gly */
        if (!(gene[j] == 'G' && gene[j+1] == 'G'))
          break;
      
    }
    /*checking if it's the sequence we're looking for*/
    /*printf("((%d, %d))", (j-i), missing_prots);*/
    if ((j-i)/3 >= missing_prots){
      first_intron[1] = i-1;
      second_intron[0] = j+3;
      break;
    }

  }

  printf("\n%d %d %d %d\n", first_intron[0], first_intron[1], second_intron[0], second_intron[1]);
  if (control != 0 && first_intron[1] > first_intron[0] && second_intron[1] > second_intron[0])
    printf("\n%d %d %d %d\n", first_intron[0], first_intron[1], second_intron[0], second_intron[1]);
  else
    printf("NONE\n");

  return 0;
}



