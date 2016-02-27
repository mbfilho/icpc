#include <cstdio>
#include <cmath>


class Ponto{
public:
	double x, y;
	
	Ponto operator-( const Ponto& a ){
		Ponto ret;
		
		ret.x = x - a.x;
		ret.y = y - a.y;
		return ret;
	}
}c, a1, b1, c1, d1;

double inter( Ponto a, Ponto b ){
	return a.x * b.x + a.y * b.y;
}

double vetor( Ponto a, Ponto b ){
	return a.x * b.y - a.y * b.x;
}

int main(){
	int casos;
	double razao, cosse, seno;
	Ponto diagonal;
	
	scanf( "%d", &casos );
	while( casos-- ){	
		scanf( "%lf %lf", &c.x, &c.y );
		scanf( "%lf %lf", &a1.x, &a1.y );
		scanf( "%lf %lf", &b1.x, &b1.y );
		scanf( "%lf %lf", &c1.x, &c1.y );
		scanf( "%lf %lf", &d1.x, &d1.y );
		
		diagonal = c1 - a1;
		razao = sqrt( inter( diagonal, diagonal ) / ( inter( c, c ) ) );
		
		cosse = inter( diagonal, c );
		cosse /=  sqrt( inter( diagonal, diagonal ) * inter( c, c ) );
		seno = sqrt( 1 - cosse * cosse );
		
		double x, y;
		
		if( vetor( diagonal, c ) < 0 )
			seno = -seno;
		
		y = ( -a1.x * razao * seno ) / pow( razao * cosse - 1, 2 );
		y -= a1.y / ( razao * cosse - 1 );
		y *= ( 1 / ( 1 + ( pow( razao * seno, 2 ) / pow( razao * cosse - 1, 2 ) ) ) );	
		
		x = ( razao * y * seno + a1.x ) / ( 1 - razao * cosse );

			
		printf( "%.4lf %.4lf\n", x, y );
	}
}

