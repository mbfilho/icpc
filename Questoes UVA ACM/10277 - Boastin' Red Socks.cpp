#include <iostream>
#include <cmath>
using namespace std;

typedef unsigned long long ull;

/*
	r
*/

ull p, q, red, total;

ull gcd( ull a, ull b ){
	ull menor;
	
	while( b ){
		menor = a % b;
		a = b;
		b = menor;
	}
	
	return a;
}

int main(){
	int razao;
	bool achou;
	
	while( cin >> p >> q && ( p | q ) ){
		achou = false;
		
		if( p == 0 ){
			cout << "0 2" << endl;
			continue;
		}
		/*else if( p == q ){
			cout << "2 0" << endl;
			continue;
		}*/
		
		ull mdc = gcd( q, p );
		
		p /= mdc;
		q /= mdc;
		
		for( total = 2; total <= 50000; ++total ){
			if( ( total * total - total ) > q ){
				if( ( total * total - total ) % q == 0 ){
					razao = ( total * total - total ) / q;
					ull delta = 1 + 4 * razao * p;
					ull temp = (ull) sqrt( double( delta ) );
					if( temp * temp == delta && temp % 2 == 1 ){
						red = ( 1 + temp ) / 2;
						if( red > 1 && red <= total ){
							achou = true;
							break;
						}
					}
				}
			}else{
				if( q % ( total * total - total ) == 0 ){
					razao = q / (total * total - total);
					if( p % razao == 0 ){
						ull temp = p / razao;
						ull delta = 1 + 4 * temp;
						ull aux = (ull) sqrt( double( delta ) );
						if( aux * aux == delta && aux % 2 == 1 ){
							red = ( 1 + aux ) / 2;
							if( red > 1 && red <= total ){
								achou = true;
								break;
							}
						}
					}
				}
			}
		}
		
		if( achou )
			cout << red << " " << (total - red) << endl;
		else
			cout << "impossible" << endl;
	}
}
