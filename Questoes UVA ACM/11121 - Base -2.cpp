#include <cstdio>

int quo, mod;

int divide( int a ){
	if( a > 0 ){
		quo = a / (-2);
		mod = a - quo * (-2);
	}else{
		a = -a;
		quo = a / 2;
		
		if( quo * 2 < a )
			++quo;
		
		mod = 2 * quo - a;	
	}
	
	return quo;
}


int main(){
	int num, prt, casos;
	char numero[120];
	
	scanf( "%d", &casos );
	
	for( int j = 1; j <= casos; ++j ){
		scanf( "%d", &num );
		prt = 0;
		
		do{
			num = divide( num );
			numero[prt++] = mod + '0';		
		}while( num );
		
		printf( "Case #%d: ", j );
		for( prt = prt - 1; prt >= 0; --prt )
			printf( "%c", numero[prt] );
		printf( "\n" );
	}
	
}
