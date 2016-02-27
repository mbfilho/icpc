#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 10100
#define EPS 1e-5
typedef long long ll;

struct Ponto{
	
	ll x, y;
	
	Ponto(){}
	
	Ponto( ll a, ll b ){
		x = a;
		y = b;
	}
	
	ll operator*( const Ponto p ) const{
		return x * p.y - y * p.x;
	}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y );
	}
	
	Ponto operator*( const double b ) const{
		return Ponto( x * b, y * b );
	}
	
	ll operator%( const Ponto& p ) const{
		return x * p.x + y * p.y;
	}
	
	double operator!() const{
		return sqrt( double( x * x + y * y ) );
	}

};

Ponto p;

bool operator<( const Ponto& a, const Ponto& b ){
	Ponto aa = a - p, bb = b - p;
	ll ret = aa * bb;
	if( ret )
		return ret > 0;
	return (aa%aa) < (bb%bb); 
}

Ponto pts[ N ];
int pilha[ N ], sp;
int n;

void graham(){
	p = pts[ 0 ];
	for( int i = 1; i < n; ++i ){
		if( p.y > pts[ i ].y )
			p = pts[ i ];
		else if( p.y == pts[ i ].y && p.x > pts[ i ].x  )
			p = pts[ i ];
	}
	
	sort( pts, pts + n );

	pilha[ 0 ] = 0;
	pilha[ 1 ] = 1;
	sp = 2;
	
	for( int i = 2; i < n; ++i ){
		while( sp > 1 && ( ( pts[ i ] - pts[ pilha[sp-2] ] ) * ( pts[ pilha[sp-1] ] - pts[ pilha[sp-2] ] ) > 0 )  ) --sp;
		pilha[ sp++ ] = i;
	}
	
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int caso = 1; caso <= casos; ++caso ){
		scanf( "%d", &n );
		ll somax = 0, somay = 0;
		for( int i = 0; i < n; ++i ){
			scanf( "%lld %lld", &pts[ i ].x, &pts[ i ].y );
			somax += pts[ i ].x;
			somay += pts[ i ].y;
		}

		graham();
		double best = 1e50;
		for( int i = 0; i < sp; ++i ){
		// Essa eca de codigo e pra calcular a distancia do ponto para a reta
			Ponto u = pts[ pilha[(i+1)%sp] ] - pts[ pilha[i] ];
			double vx = 1.0 * somax / n - pts[ pilha[i] ].x, vy = 1.0 * somay / n - pts[ pilha[i] ].y;
			
			double prod = vx * u.x + vy * u.y;
			prod /= u % u;
			
			double ux = u.x * prod, uy = u.y * prod;
			
			best = min( best, ( vx - ux ) * ( vx - ux ) + ( vy - uy ) * ( vy - uy ) );			
		}
		printf( "Case #%d: %.3lf\n", caso, sqrt( best ) );

		
	}
}





