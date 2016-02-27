#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
#define N 30

struct No{
	double x, y, r;
	
	No( double a, double b, double rr ){
		x = a;
		y = b;
		r = rr;
	}
	
	No(){}
}tow[ N ];

int n;

double quad( double b ){
	return b * b;
}

int main(){
	
	while( scanf( "%d", &n ) != EOF && n ){
		srand( n );
		
		for( int i = 0; i < n; ++i )
			scanf( "%lf %lf %lf", &tow[ i ].x, &tow[ i ].y, &tow[ i ].r );
		
		int dentro = 0, total = 0;
		double old = 1e50;
		int check = 40000;
		while( total < 1000000 ){
			double x = tow[ 0 ].x + ( 2 * tow[ 0 ].r * ( rand() % 10000 ) / 10000.0 ) - tow[ 0 ].r;
			double y = tow[ 0 ].y + ( 2 * tow[ 0 ].r * ( rand() % 10000 ) / 10000.0 ) - tow[ 0 ].r;
			
			if( quad( x - tow[ 0 ].x ) + quad( y - tow[ 0 ].y ) > quad( tow[ 0 ].r ) ) continue;
			
			bool esta = false;
			for( int i = 1; !esta && i < n; ++i ){
				if( quad( x - tow[ i ].x ) + quad( y - tow[ i ].y ) <= quad( tow[ i ].r ) )
					esta = true;
			}
			
			if( esta )
				++dentro;
			++total;
			
			if( total == check ){
				double nova = double( dentro ) / total;
				if( abs( old - nova ) < 0.01 * ( nova + old ) / 2.0 ) break;
				old = nova;
				check = 2 * total;
			}
		}
		
		printf( "%.2lf\n", double( dentro ) / total );
	}
}


