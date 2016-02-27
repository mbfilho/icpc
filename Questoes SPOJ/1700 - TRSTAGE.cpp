#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define inf 9999999.0
#define mp make_pair
// Spoj
int n, horses[ 8 ];

int m;
vector< pair<int,int> > adj[ 31 ];

int a, b;

double dist[ 31 ][ 1 << 9 ];
bool mark[ 31 ][ 1 << 9 ];

struct Terno{
	int no, mask;
	double dist;
	
	Terno(){}
	
	Terno( int a, double d, int m ){
		no = a;
		dist = d;
		mask = m;
	}
	
	bool operator<( const Terno& t ) const{
		return !(dist < t.dist);
	}
};

void dij(){
	priority_queue<Terno> heap;
	
	for( int i = 1; i <= m; ++i ){
		for( int j = 0; j < ( 1 << n ); ++j ){
			mark[ i ][ j ] = false;
			dist[ i ][ j ] = inf;
		}
	}
	
	dist[ a ][ (1 << n) - 1 ] = 0.0;
	
	heap.push( Terno( a, 0.0, ( 1 << n ) - 1 ) );
			
	Terno temp;
	while( heap.empty() == false ){
		temp = heap.top();
		heap.pop();
		
		if(	mark[ temp.no ][ temp.mask ] )	continue;
		
		mark[ temp.no ][ temp.mask ] = true;
		
		int next;
		double custo;
		for( int i = adj[ temp.no ].size() - 1; i >= 0; --i ){
			for( int j = 0, pot = 1; j < n; ++j, pot *= 2 ){
				next = adj[ temp.no ][ i ].first;
				
				if( ( temp.mask & pot ) == 0 ) continue;
				
				if( mark[ next ][ temp.mask & (~pot) ] ) continue;
				
				custo = dist[ temp.no ][ temp.mask ] + double( adj[ temp.no ][ i ].second ) / horses[ j ];

				if( dist[ next ][ temp.mask & (~pot) ] > custo ){
					dist[ next ][ temp.mask & (~pot) ] = custo;
					heap.push( Terno( next, custo, temp.mask & (~pot) ) );
				}
			}
		}
	}
	
	double menor = inf;
	
	for( int i = 0; i < ( 1 << n ); ++i ){
		if( mark[ b ][ i ] ){
			menor = min( menor, dist[ b ][ i ] );
		}
	}
	
	if( menor < inf )
		printf( "%.5lf\n", menor );
	else
		printf( "Impossible\n" );
}

int main(){
	int p;
	
	while( scanf( "%d %d %d %d %d", &n, &m, &p, &a, &b ) && ( n | m | p | a | b ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", horses + i );
		
		for( int i = 1; i <= m; ++i )
			adj[ i ].clear();
		
		int u, v, peso;
		for( int i = 0; i < p; ++i ){
			scanf( "%d %d %d", &u, &v, &peso );
			adj[ u ].push_back( mp( v, peso ) );
			adj[ v ].push_back( mp( u, peso ) );
		}
	
		dij();
	}
}


