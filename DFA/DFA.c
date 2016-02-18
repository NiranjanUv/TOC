/* C program to implement DFA */
/* input file is = dat_test.dat*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2

int nstates,ninpsymbols,nfinal;
int i,start_state,result; 
int transition[10][10];
int final[6];
int symbol[4];

int main(int argc,char *argv[])
{
	FILE *input_file;
 	int tr,tc,alp,tmp;   
	char current_symbol[1],temp[10] = {'0'},a[2] = {0};
	input_file = fopen(argv[1],"r");

   	if(input_file == NULL)
   	{
   		fprintf(stderr,"Enter the input filename\n");
   		exit(0);
   	}

	/* Read Number of states and number of input symbols */
   	fscanf(input_file,"%d",&nstates);
   	fscanf(input_file,"%d",&ninpsymbols);


	/* Read the input symbols */
	for (i = 0; i<ninpsymbols; i++)
   	{
       		fscanf(input_file,"%d",&symbol[i]);
	}

	/* Read the start state and number of final states */
	fscanf(input_file,"%d",&start_state);
	fscanf(input_file,"%d",&nfinal);

	/* Read the final states */
  	for (i = 0; i<nfinal; i++)
   	{
       		fscanf(input_file,"%d",&final[i]);	
   	}

	/* Read the transition table */
	while (fscanf(input_file,"%d %d %d", &tr, &tc, &alp) != EOF)
	{
		transition[tr][tc] = alp;
	}
   	fclose(input_file);
   
   	printf("Enter a string with '0' s and '1's:\n");
	scanf("%s",temp); 

	for(i=0;i<strlen(temp);i++)
	{
		if(temp[i] == '\0') break;
		else 
		{ 
  			a[0] = temp[i];
  			tmp = atoi(a); 		
        		if((result= DFA(tmp))==UNKNOWN_SYMBOL_ERR)
	            	break;  
		}
	}

	switch (result) 
    	{
		case UNKNOWN_SYMBOL_ERR:printf("Given String has Unknown Symbol %s\n\n",current_symbol);  
		break;

		case NOT_REACHED_FINAL_STATE:printf("Given String is Rejected by DFA\n\n"); 
		break;

		case REACHED_FINAL_STATE:printf("Given String is Accepted by DFA\n\n");
		break;

		default: printf("Unknown Error\n");
    	}
}

/* DFA Simulation */
int DFA(int x)
{
    int i,pos;

    for(pos=0;pos<ninpsymbols; pos++)
        if(x==symbol[pos])   
            break;	//stops if any character other than 0 or 1

    if(pos==ninpsymbols)
         return UNKNOWN_SYMBOL_ERR;

    for(i=0;i<nfinal;i++)

 	if((start_state=transition[start_state][pos])==final[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}
