#include <cstdio>
#include <algorithm>
using namespace std;

int gcd( int a, int b ){
	int temp;
	
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

int main(){
	int x, y, q2, q5;
	
	scanf( "%d %d", &x, &y );
	
	if( x % y == 0 )
		printf( "0 0\n" );
	else{
		x = x % y;
		q2 = q5 = 0;
		int temp = gcd( x, y );
		
		x = x / temp;
		y = y / temp;
		
		while( y % 2 == 0 ){
			y = y / 2;
			++q2;
		}
		
		while( y % 5 == 0 ){
			y = y / 5;
			++q5;
		}
		
		int k = 0, pot = 1;
		if( y != 1 ){
			while( true ){
				++k;
				pot = ( pot * 10 ) % y;
				
				if( pot == 1 )
					break;
			}
		}
		
		printf( "%d %d\n", max( q2, q5 ), k );
	}
}
