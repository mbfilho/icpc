#include <cstdio>
#include <algorithm>
using namespace std;

struct Ponto{
	int x, y;
	
	Ponto( int a, int b ){
		x = a;
		y = b;
	}
	
	Ponto(){}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y );
	}
	
	int operator!() const{
		return x * x + y * y;
	}
	
	bool operator==( const Ponto& p )const{
		return x == p.x && y == p.y;
	}
}p1[ 10000 ], p2[ 10000 ], pivot;

int prod( const Ponto& a, const Ponto& b ){
	return a.x * b.y - a.y * b.x;
}

bool comp( const Ponto& a, const Ponto& b ){		
	Ponto aa = a - pivot, bb = b - pivot;
	int ret = prod( a - pivot, b - pivot );
	
	if( ret )
		return ret > 0;
	else
		return !aa < !bb;
}

int pilha[ maxi ], sp, pts;

int scan( Ponto* arg, int qtd, Ponto* res ){
	pivot = arg[ 0 ];
	
	for( int i = 1; i < qtd; ++i ){
		if( arg[ i ].y < pivot.y ){
			pivot = arg[ i ];
		}else if( arg[ i ].y == pivot.y && arg[ i ].x < pivot.x ){
			pivot = arg[ i ];
		}
	}

	sort( arg, arg + qtd, comp );
	
	
	int p;
    for (p = qtd-2; p> 0; p--) {
      if ( prod((arg[p] - pivot), (arg[qtd-1] - pivot))) break;
    }
    reverse(arg + p+1, arg+qtd);
	
	
	pilha[ 0 ] = 0;
	pilha[ 1 ] = 1;
	sp = 1;
	
	int cont = 0;
	for( int i = 2; i < qtd; ++i ){
		while( prod( arg[ i ] - arg[ pilha[sp - 1] ], arg[ pilha[sp] ] - arg[ pilha[sp - 1] ]) > 0 ){
			res[ cont++ ] = arg[ pilha[sp] ];
			--sp;
		}
		pilha[ ++sp ] = i;
	}
	
	return cont;
}

int main(){
	
	while( scanf( "%d", &pts ) && pts ){
		for( int i = 0; i < pts; ++i ){
			scanf( "%d %d", &p1[ i ].x, &p1[ i ].y );
		}
		
		int comp = 0;
		while( pts ){		
			if( comp & 1 ){
				pts = scan( p2, pts, p1 );
			}else{
				pts = scan( p1, pts, p2 );
			}
			
			++comp;
		}
		
	//	printf( "%d\n", comp );
		
		if( comp & 1 )
            printf( "Take this onion to the lab!\n" );
		else
            printf( "Do not take this onion to the lab!\n" );
		
	}
}


