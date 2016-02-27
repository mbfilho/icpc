#include <cstdio>
#include <algorithm>
using namespace std;

int buf[ 200000 ];
int n;

int main(){
	int ca;
	scanf( "%d", &ca );
	
	
	while( ca-- ){
		int id;
		scanf( "%d %d", &id, &n );
		for( int i = 0; i < n; ++i )
			scanf( "%d", buf + i );
		
		int sum = 0, prt = 0;
		bool ft = true;
		
		while( prt < n ){
			sum += buf[ prt++ ];
			
			int ini = prt;
			bool dm = false;
			while( !dm && ini < n ){
				int soma = 0;
				while( ini < n && soma < sum )
					soma += buf[ ini++ ];
				if( soma != sum ) dm = true;
			}
			
			if( !dm ) break;
		}
		
		printf( "%d %d\n", id, sum );
	}
}




