#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;
    char gap = '-';
    int numberGap=0;

    if (file == NULL)
        return NULL; //could not open file

    code = malloc(1000);
    char texto[1000];
    while ((c = fgetc(file)) != EOF)
    {
        // code[n++] = (char) c;
        // printf("%c", c);
        if (c == gap){
            numberGap++;
            //printf("Gap: %c --> NumberGap: %i\n", c, numberGap);
        }else{            
            if (numberGap!=0){
                sprintf(texto, "%d", numberGap);
                strcat(code, texto);
                //printf("::inside:: %s\n",code);
                // code[n++]= texto;
                // printf("Insert gap integer: %s <<-->> %s\n", texto,code);
                numberGap=0;
                for (int i=1; i<=strlen(texto); i++){
                    n=n+1;
                }
            }
            code[n++] = (char) c;
            //printf("Char: %c\n", c);
        }
    }

    // don't forget to terminate with the null character
    code[n] = '\0';

    //printf("There are %i gaps\n", numberGap);
    printf("Final alignment: %s\n", code);
    return code;
}
int printFile(char *filename){

    FILE *fptr; 
    char c;

    // Open file 
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr); 
    return 0; 
}
void convertFasta(char * file){
    char *code;
    size_t n = 0;
    int c;
    char gap = '-';
    int numberGap=0;
    code = malloc(1000);
    char texto[1000];

    while ((c = file)!= EOF)
    {
        // code[n++] = (char) c;
        // printf("%c", c);
        if (c == gap){
            numberGap++;
            //printf("Gap: %c --> NumberGap: %i\n", c, numberGap);
        }else{            
            if (numberGap!=0){
                sprintf(texto, "%d", numberGap);
                strcat(code, texto);
                //printf("::inside:: %s\n",code);
                // code[n++]= texto;
                printf("Insert gap integer: %s <<-->> %s\n", texto,code);
                numberGap=0;
                for (int i=1; i<=strlen(texto); i++){
                    n=n+1;
                }
            }
            code[n++] = (char) c;
            //printf("Char: %c\n", c);
        }
    }

}
int readFasta(char *filename)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
 
	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
 
	int state = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		/* Delete trailing newline */
		if (line[read - 1] == '\n')
			line[read - 1] = 0;
		/* Handle comment lines*/
		if (line[0] == '>') {
			if (state == 1)
				printf("\n");
			printf("%s: ", line+1);
			state = 1;
		} else {
			/* Print everything else */
			printf("%s", line);
            convertFasta(line);
		}
	}
	printf("\n");
 
	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}
int main()
{
   readFile("test.fa");
   printFile("test.fa");
   return 0;
}