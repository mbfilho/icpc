#include <cstdio>
#include <cstring>

bool marcado[200];
bool palavra[200];

char correta[10000], guess[10000];

int main(){
	int round, erradas, restantes, tam;
	
	while( scanf( "%d", &round ) && round != -1 ){
		for( int i = 0; i < 200; ++i )
			marcado[i] = palavra[i] = false;
		
		scanf( "%s %s", correta, guess );
		
		tam = strlen( correta );
		restantes = 0;
		erradas = 0;
		
		for( int i = 0; i < tam; ++i ){
			if( palavra[correta[i]] == false ){
				++restantes;
				palavra[ correta[i] ] = true;
			}
		}
		
		tam = strlen( guess );
		for( int i = 0; i < tam && restantes && erradas < 7; ++i ){
			if( marcado[guess[i]] == false ){
				marcado[guess[i]] = true;
				if( palavra[guess[i]] )
					--restantes;
				else
					++erradas;
			}
		}
		
		printf( "Round %d\n", round );
		if( restantes == 0 )
			printf( "You win.\n" );
		else if( erradas == 7 )
			printf( "You lose.\n" );
		else
			printf( "You chickened out.\n" );
		
	} 
}
