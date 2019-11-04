#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char * inputFasta = "test.fa";
char * outputFileFA2Gap = "resultF2G.gap";
char * outputFileGap2FA = "resultG2F.fa";
FILE *outFileFa2Gap;
FILE *outFileGap2Fa;
bool gaps;
char gap = '-';

int writeChar2File(FILE *outFile, char char2write){
    int i;
    if (outFile != NULL) {
       fputc (char2write, outFile);		
   }
   else {
  	  printf("\n Unable to Create or Open the Sample.txt File");
   }
   return 0;
}
void printString(FILE * filePoint, char *string2print){
    int len = strlen(string2print);
    int i;
    
    for (i = 0; i < len; i++) {
        writeChar2File(filePoint,string2print[i]);
	}
}
void convert_final_digit(int digit){
    int i;
    for( i = 0; i < digit; i = i + 1 ){
        writeChar2File(outFileGap2Fa,gap);
    }
}
void convertGaps (char *line){
    char *c;
    char aux[100];  //number of digits for gaps... posibility of ERROR
    char nn; 
    int numberGap=0;
    
    for (c=line; *c; c++) {
        nn = *c;
        if (nn == gap)  {            // gap found
            numberGap++;
        }else{            
            if (numberGap!=0){      // 1st non-gap after gap
                //print number of gaps
                //****printf("%d", numberGap);
                sprintf(aux, "%d", numberGap);  //convert int to char*
                printString(outFileFa2Gap,aux);
                //reset counter
                numberGap=0;
            }
            //print nucleotide
            //****printf("%c", nn);
            writeChar2File(outFileFa2Gap,nn);

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
                //****printf("%c",nn);
                writeChar2File(outFileGap2Fa,nn);
                }else{          //first time to nucelotide after digit
                    //printf("auxDigit: : : %i",auxDigit);
                    convert_final_digit(auxDigit);
                    check=0;
                    //printf("total gaps: %d \nfirst neuclotide %c\n", auxDigit,nn);
                    //****printf("%c",nn);
                    writeChar2File(outFileGap2Fa,nn);
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
            //****printf(">%s: \n", line+1);
            if (gaps){  //choose wich is the output file
                printString(outFileFa2Gap,">");
                printString(outFileFa2Gap,line+1);
                printString(outFileFa2Gap,"\n");
            }else{
                printString(outFileGap2Fa,">");
                printString(outFileGap2Fa,line+1);
                printString(outFileGap2Fa,"\n");
            }
            state = 1;
        } else {
            /* Print everything else */
            if (gaps){  //fasta >> gaps
                convertGaps(line);
                printString(outFileFa2Gap,"\n");
            }else {     // gaps >> fasta
                convertFasta(line);
                printString(outFileGap2Fa,"\n");
            }
        }
    }
    fclose(fp);
    if (line)
        free(line);
}
void convert2Fasta(char *filename){
    gaps = false;
    readFasta(filename);
}
void convert2Gap(char *filename){
    gaps = true;
    readFasta(filename);
}
FILE *openResultFile(char *fileName){
    FILE *fileAddress = fopen(fileName, "w");
    return fileAddress;
}
int closeResultFile(FILE *outFile){
    // printf("\nWe have written the file successfully\n");
	fclose(outFile);	
}
int main(){

    //open result files
    outFileFa2Gap = openResultFile(outputFileFA2Gap);
    outFileGap2Fa = openResultFile(outputFileGap2FA);

    printf("## FASTA TO GAP ##\n    Input file: %s\n    Output file: %s\n",inputFasta,outputFileFA2Gap);
    convert2Gap(inputFasta);
    closeResultFile(outFileFa2Gap);

    printf("\n## GAP TO FASTA ##\n    Input file: %s\n    Output file: %s\n",outputFileFA2Gap,outputFileGap2FA);
    convert2Fasta(outputFileFA2Gap);
    closeResultFile(outFileGap2Fa);

    return 0;
}
