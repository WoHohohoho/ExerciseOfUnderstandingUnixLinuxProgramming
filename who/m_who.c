#include <utmpx.h>
#include <stdio.h>

void show_info( struct utmpx *login_info_entry );
void show_time( struct utmpx *login_info_entry );

int main(){
	struct utmpx *login_info_entry;

	while( (login_info_entry = getutxent()) != NULL )
		show_info( login_info_entry );

	endutxent();
	
	return 0;
}

void show_info( struct utmpx *login_info_entry ){
	if( login_info_entry->ut_type != USER_PROCESS )
		return;

	printf( "%-8.8s", login_info_entry->ut_user );
	printf( " " );
	printf( "%-8.8s", login_info_entry->ut_line );
	printf( " " );
	show_time( login_info_entry );
	printf( " " );
	printf( "(%s)", login_info_entry->ut_host );
	printf( "\n" );
}


void show_time( struct utmpx *login_info_entry ){
	char *time = ctime( &((login_info_entry->ut_tv).tv_sec) );
	printf( "%-12.12s", time+4 );
}
