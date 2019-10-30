#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool gaps;

void convert_final_digit(){

}
void convertGaps (char *line){
    char *c;
    char gap = '-';
    int numberGap=0;
    char nn; 

    for (c=line; *c; c++) {

        nn = *c;
        if (nn == gap)  {            // gap found
            numberGap++;
        }else{            
            if (numberGap!=0){      // 1st non-gap after gap
                //print number of gaps
                printf("%d", numberGap);
                //reset counter
                numberGap=0;
            }
            //print nucleotide
            printf("%c", nn);
        }
    }
}
void convertFasta (char *line){
    char *c;
    int numberGap=0;
    char nn; 
    int check=0;
    int auxDigit=0;
    char *aux;

    for (c=line; *c; c++) {

        nn = *c;
        //printf("** what we have: %c\n",nn);

        if (!isdigit(nn)){  //it's a nucleotide
            printf("nucleotide: %c\n",nn);
            if (check==0){  //digit already covnerted
                //printf("%c",nn);    //print nn
            }else{          //first time to nucelotide after digit
                //printf("auxDigit: : : %i",auxDigit);
                convert_final_digit();
                check=0;
                //printf("%c",nn);
            }
        }else{              //its a digit
            printf(">> number: %c\n",nn);
            //TODO -> append nn
            //auxDigit= atoi(aux);  //apend digit to gapNumber
            printf("<< digit %s",aux);
            check=1;        //need to convert auxDigit to int
        }   
    }
}

void readFasta(char *fileName){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
 
    fp = fopen(fileName, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
 
    int state = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        /* Delete trailing newline */
        if (line[read - 1] == '\n')
            line[read - 1] = 0;
        /* Handle comment lines*/
        if (line[0] == '>') {
            if (state == 1){
                //printf("\n");
            }
            printf("%s: \n", line+1);
            state = 1;
        } else {
            /* Print everything else */
            if (gaps){  //fasta >> gaps
                convertGaps(line);
            }else {     // gaps >> fasta
                convertFasta(line);
            }
            printf("\n");
            //printf("%s\n", line);
        }
    }
 
    fclose(fp);
    if (line)
        free(line);
    //exit(EXIT_SUCCESS);
}

void convert2Fasta(char *filename){
    gaps = false;
    readFasta(filename);
}
void convert2Gap(char *filename){
    gaps = true;
    readFasta(filename);
}



int main(){
    printf("## FASTA TO GAP ##\n\n");
    convert2Gap("test.fa");

    printf("\n## GAP TO FASTA ##\n\n");
    convert2Fasta("test.gap");

    printf("## ## ## ## ##\n\n");

    return 0;
}
