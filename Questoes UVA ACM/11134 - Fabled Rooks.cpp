#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 5001

bool X;

class Rook{
public:
	int id;
	int xl, yl, xr, yr;
	int posX, posY;

	/*
		Usado pelo heap.
		A idéia é para cada quadrado "Q" analisado ( no eixo X ou no Y ) colocar no
		heap todas as torres que podem ser colocadas naquela posicao e dar prioridade
		àquela que possui, a partir de "Q" o menor range, ou seja, aquela que precisa
		ser colocada mais "urgentemente"
	*/
	bool operator<( const Rook& r ) const{
		if( X )
			return !( xr < r.xr );
		else
			return !( yr < r.yr );
	}

}torres[ MAX ], impressao[ MAX ];

bool compX( const Rook& r, const Rook& b ){
	return ( r.xl < b.xl );
}

bool compY( const Rook& r, const Rook& b ){
	return ( r.yl < b.yl );
}

int n;

bool resolverY(){
	X = false;
	sort( torres, torres + n, compY );
	priority_queue<Rook> heap;

	int i = 0;
	for( int posicao = 1; posicao <= n; ++posicao ){
		while( i < n ){
			if( torres[ i ].yl <= posicao && torres[ i ].yr >= posicao ){
				heap.push( torres[ i ] );
			}else{
				break;
			}
			++i;
		}

		if( heap.size() == 0 || heap.top().yr - posicao < 0 )
			return false;
		else{
			impressao[ heap.top().id ].posY = posicao;
			heap.pop();
		}
	}

	return true;
}

bool resolverX(){
	X = true;
	sort( torres, torres + n, compX );

	priority_queue<Rook> heap;
	int i = 0;
	for( int posicao = 1; posicao <= n; ++posicao ){
		while( i < n ){
			if( torres[ i ].xl <= posicao && torres[ i ].xr >= posicao )
				heap.push( torres[ i ] );
			else
				break;
			++i;
		}

		if( heap.size() == 0 || heap.top().xr - posicao < 0 )
			return false;
		else{
			impressao[ heap.top().id ].posX = posicao;
			heap.pop();
		}
	}

	return true;
}

int main(){
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );

	scanf( "%d", &n );

	while( n ){
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d %d %d", &torres[ i ].xl, &torres[ i ].yl, &torres[ i ].xr, &torres[ i ].yr );
			torres[ i ].id = i;
		}

		if( resolverY() && resolverX() ){
			for( int i = 0; i < n; ++i )
				printf( "%d %d\n", impressao[ i ].posX, impressao[ i ].posY );
		}else
				printf( "IMPOSSIBLE\n" );
		

		scanf( "%d", &n );
	}
}


