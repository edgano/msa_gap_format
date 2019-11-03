#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool gaps;
char gap = '-';

void convert_final_digit(int digit){
    int i;
    for( i = 0; i < digit; i = i + 1 ){
        printf("%c", gap);
    }
}
void convertGaps (char *line){
    char *c;
    char nn; 
    int numberGap=0;
    
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
    char nn; 
    int check=0;
    int auxDigit;

    for (c=line; *c; c++) {
        nn = *c;
        if (!isdigit(nn) || check==1){  //it's a nucleotide or non the first digit
            if(isdigit(nn)){
                //second or more digits in a row
                //nothing to do... it's already captured in the ATOI()
            }else{
                if (check==0){  //digit already covnerted
                //printf("nucleotide: %c\n",nn);
                printf("%c",nn);
                }else{          //first time to nucelotide after digit
                    //printf("auxDigit: : : %i",auxDigit);
                    convert_final_digit(auxDigit);
                    check=0;
                    //printf("total gaps: %d \nfirst neuclotide %c\n", auxDigit,nn);
                    printf("%c",nn);
                }
            }
        }else{              //its the FIRST digit
            //it graps all the digirs in teh auxDigit 
            //but the pointer in the char* not... it will
            //go in the if bellow with CHECK==1...
            auxDigit= atoi(c);
            //printf("<< digit %d\n",auxDigit);
            check=1;
            //TODO -> check if its just 0 --> ERROR
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
            printf(">%s: \n", line+1);
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
