#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 20
#define LINELEN 512

int print_lines( FILE *input, int length );
int wait_response();

int main ( int ac, char *av[] ){
	FILE *input;
	// Get the input file if exist, or make the standard input as input
	if ( ac == 1)	
		input = stdin;
	else{
		if ( (input = fopen( *++av, "r")) == NULL) 
			exit(1);
	}
		
	int length = PAGELEN;
	while (1){
		// Read 20 lines of content and print to the screen
		if ( 0 != print_lines( input, length) )
			// print the prompt
			printf("\033[7m more? \033[m");
		// wait for the response
		length = wait_response();
		// continue the program according to the response
		if ( length == 0 )	
			exit(1);
	}
	return 0;
}

int print_lines( FILE *input, int length ){
	int count = 0;
	char line[LINELEN];
	while ( length-- && fgets( line, LINELEN, input) != NULL ){
		if ( fputs( line, stdout ) == EOF )	
			exit(1);
		count++;
	}
	return count;
}

int wait_response(){
	int c = 0;
	while ( (c = getchar()) != EOF ){
		if ( c == 'q' ) return 0;
		if ( c == ' ' ) return PAGELEN;
		if ( c == '\n' ) return 1;
	}
}
