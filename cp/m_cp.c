#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 4096

void oops( char *err_operation, char *filename );

int main(int ac, char *args[]){
    int file_in, file_out, count;
    char buffer[BUFFERSIZE];

    if ( ac != 3 ){
        fprintf(stderr, "Usage: %s source destination\n", args[0]);
        exit(1);
    }

    if ( ( file_in = open(args[1], O_RDONLY) ) == -1 )
        oops("Can't open", args[1]);

    if ( ( file_out = creat(args[2], 0644) ) == -1 )
        oops("Can't create", args[2]);

    while ( (count = read(file_in, buffer, BUFFERSIZE)) > 0 )
        if ( write(file_out, buffer, count) != count )
            oops( "write error to", args[2] );

    if ( count == -1 ) 
        oops( "read error from ", args[1] );

    if ( close(file_in) == -1 || close(file_out) == -1 )
        oops( "error in closing file", "" );
    
	return 0;
}


void oops( char *err_operation, char *filename ){
    fprintf( stderr, "Error: %s ", err_operation );
    perror(filename);
    exit(1);
}
