#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define N 2100
#define mp make_pair

struct Ponto{
	int x, y, z;
	
	Ponto( int a, int b, int c ){
		x = a;
		y = b;
		z = c;
	}
	
	Ponto(){}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y, z - p.z );
	}
	
	bool operator<( const Ponto& p ) const{
		if( x != p.x ) return x < p.x;
		if( y != p.y ) return y < p.y;
		return z < p.z;
	}
	
	Ponto operator-() const{
		return Ponto( -x, -y, -z );
	}
}pts[ N ];
int n;

map<Ponto,int> mapa;

int gcd( int a, int b ){
	a = abs( a );
	b = abs( b );
	int temp;
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

int main(){
	scanf( "%d", &n );
	
	for( int i = 0; i < n; ++i )
		scanf( "%d %d %d", &pts[ i ].x, &pts[ i ].y, &pts[ i ].z );
	
	int maior = 1;
	
	map<Ponto,int>::iterator it;
	for( int i = 0; i < n; ++i ){
		mapa.clear();
		for( int j = i + 1; j < n; ++j ){
			Ponto vetor = pts[ j ] - pts[ i ];
			int mdc = gcd( vetor.x, gcd( vetor.y, vetor.z ) );
			vetor.x /= mdc; vetor.y /= mdc; vetor.z /= mdc;

			it = mapa.find( vetor );
			if( it == mapa.end() ){
				it = mapa.find( -vetor );
				vetor = -vetor;
			}
			
			if( it == mapa.end() ){
				mapa[ vetor ] = 2;
				maior = max( maior, 2 );
			}else{
				maior = max( maior, ++mapa[ vetor ] );
			}
		}
	}
	
	//
	printf( "%d\n", maior );
	
}



