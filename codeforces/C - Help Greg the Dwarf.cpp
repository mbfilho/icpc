#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define EPS 1e-7
#define oo 1e30

struct Ponto{
	double x, y;
	
	Ponto( double a, double b ){
		x = a;
		y = b;
	}
	
	double operator*( const Ponto& p ) const{
		return x * p.x + y * p.y;
	}
	
	Ponto operator*( const double& b ) const{
		return Ponto( x * b, y * b );
	}
	
	double operator!(){
		return sqrt( x * x + y * y );
	}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y );
	}
	
	double operator%( const Ponto& p ) const{
		return x * p.y - y * p.x;
	}
};

int a, b, l;

//distancia do ponto p3 ao segmento p1-p2 OBS: p1 ta no Oy e p2 no Ox
double dist( Ponto p1, Ponto p2, const Ponto& p3 ){
	Ponto seg = p1 - p2, vet = p3 - p2;
	
	if( vet % seg < 0 )
		return -100.0;
	
	Ponto dist = vet - seg * ( ( vet * seg ) / ( seg * seg ) );
	return !dist;
}

//ternary search na funcao da distancia entre o segmento do lado do caixao com e o corner do L 
double ts(){
	double ini = 0, fim = l;
	Ponto corner( b, a );
	while( true ){
		if( fim - ini < EPS ){
			double x = ( ini + fim ) / 2;
			return dist( Ponto( 0, sqrt( l * l - x * x ) ), Ponto( x, 0 ), corner );
		}
		
		double left = ( 2 * ini + fim ) / 3, right = ( ini + 2 * fim ) / 3;
		double fleft = dist( Ponto( 0, sqrt( l * l - left * left ) ), Ponto( left, 0 ), corner ); 
		double fright = dist( Ponto( 0, sqrt( l * l - right * right ) ), Ponto( right, 0 ), corner );

		if( fleft < 0 || fright < 0 ) return -100;
		
		if( fleft < fright )
			fim = right;
		else
			ini = left;
	}
}

int main(){
	scanf( "%d %d %d", &a, &b, &l );
	
	int temp = min( a, b );
	b = max( a, b );
	a = temp;
	
	if( l < a )
		printf( "%.7lf\n", double( l ) );
	else if( l >= a && l <= b )
		printf( "%.7lf\n", double( a ) );
	else{
		double val = ts();
		if( val < 0 )
			printf( "My poor head =(\n" );
		else
			printf( "%.7lf\n", val );
	}
}




