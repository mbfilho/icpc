#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 10100

double tam[ N ], slope[ N ], vel[ N ];
double a, b, vmax, f;
int n;

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%lf %lf %lf %lf", &a, &b, &vmax, &f );
		scanf( "%d", &n );
		
		double x, y;
		bool tem = false;
		for( int i = 0; i < n; ++i ){
			scanf( "%lf %lf", &x, &y );
			tam[ i ] = sqrt( x * x + y * y ) / 1000;
			slope[ i ] = y / x;
			//c = tam * max( av + bs )
			if( slope[ i ] < 0 )
				vel[ i ] = min( vmax, -b * slope[ i ] / a );
			else{
				tem = true;
				vel[ i ] = 0;
				f -= tam[ i ] * b * slope[ i ];
			}
		}
		
		if( f < 0 || ( f == 0.0 && tem ) )
			printf( "IMPOSSIBLE\n" );
		else{
			double ini = 0, fim = vmax, meio, tempo = 1e9;
			for( int i = 0; i < 50; ++i ){
				meio = ( ini + fim ) / 2;
				double rest = f, temp = 0;
				
				for( int j = 0; j < n; ++j ){
					if( meio > vel[ j ] ){
						rest -= tam[ j ] * ( meio - vel[ j ] ) * a;
						temp += tam[ j ] / meio;
					}else{
						temp += tam[ j ] / vel[ j ];
					}
				}
				
				if( rest >= 0 ){
					ini = meio;
					tempo = min( temp, tempo );
				}else
					fim = meio;
			}
			
			printf( "%.6lf\n", tempo );
		}
	}
}

