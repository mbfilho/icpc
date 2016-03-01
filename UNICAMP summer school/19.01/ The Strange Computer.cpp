#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll obj;

struct No{
	int i, j, op;
	
	void set( int a, int b, int c ){
		i = a;
		j = b;
		op = c;
	}
}ret[ 100 ];
int prt;

int ADD = 0, SUB = 1, SHI = 2;

ll pot[ 43 ];

bool rec( ll mask, int l ){
	if( (mask & obj) == obj ) return true; 
	if( !l ) return false;
	if( __builtin_popcountll( obj & (~mask) ) > l ) return false;
	
	for( int i = 1; i <= 42; ++i ){
		if( mask & pot[ i ] ){
			for( int j = 1, k = 2; k * i <= 42; ++j, k *= 2 ){
				if( mask & pot[ i * k ] ) continue;
			
				if( rec( mask | pot[ i*k ], l - 1 ) ){
					ret[ prt++ ].set( i, j, SHI );
					return true;
				}
			}
			
			for( int j = i; i + j <= 42; ++j ){
				if( mask & pot[ j ] ){
//					if( mask & pot[ j + i ] ) continue;
					
					if( rec( mask | pot[ i + j ], l - 1 ) ){
						ret[ prt++ ].set( i, j, ADD );
						return true;
					}
				}
			}
			
			for( int j = 1; i - j > 1; ++j ){
				if( mask & pot[ j ] ){
//					if( mask & pot[ i - j ] ) continue;
					
					if( rec( mask | pot[ i - j ], l - 1 ) ){
						ret[ prt++ ].set( i, j, SUB );
						return true;
					}
				}
			}
			
		}
	}
	
	return false;	
}

int main(){
	pot[0] = 1;
	for( int i = 1; i <= 42; ++i ) pot[i] = 2LL * pot[i-1];
	
	int n;
	freopen( "japan.in", "r", stdin );
	freopen( "japan.out", "w", stdout );
//	
	scanf( "%d", &n );
	obj = 0;
	
	for( int i = 0; i < n; ++i ){
		int tmp;
		scanf( "%d", &tmp );
		
		obj |= ( 1LL << tmp );
	}
	
	for( int i = n; i <= 42; ++i ){
//		printf( "%d\n", i );
//		int i = 4;
		prt = 0;
//		printf( "Going %d\n", i );
		if( rec( 2, i ) ){
			printf( "%d\n", i );
			
			for( int j = i - 1; j >= 0; --j ){
				printf( "%d", ret[j].i );

				if( ret[j].op == ADD ) printf( "+" );
				else if( ret[j].op == SUB ) printf( "-" );
				else printf( "<<" );
			
				printf( "%d\n", ret[j].j );
			}
			break;
		}
	}
}





