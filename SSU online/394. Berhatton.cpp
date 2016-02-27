#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
#define N 500100
#define TREE 2100000
map<ll,int> mapa;
set<ll> conj;
int n, k;

const int INICIO = -1, FIM = -2;

struct Ponto{
	ll x, y, fim;
	int id;
	
	bool operator<( const Ponto& p ) const{
		if( x != p.x ) return x < p.x;
		
		if( id == INICIO ) return true;
		if( p.id == FIM ) return true;
		
		return false;
	}
	
	void set( ll xx, ll yy, ll ff, int ids ){
		x = xx;
		y = yy;
		fim = ff;
		id = ids;
	}
}nos[ N ];

int tree[ TREE ], op[ TREE ];
int qtd[ N ];

void conserta( int no ){
	tree[ no ] += op[ no ];
	op[ 2 * no ] += op[ no ];
	op[ 2 * no + 1 ] += op[ no ];
	op[ no ] = 0;
}

void build( int no, int ini, int fim ){
	tree[ no ] = op[ no ] = 0;
	if( ini == fim ) return;
	
	int meio = ( ini + fim ) / 2;
	build( 2 * no, ini, meio );
	build( 2 * no + 1, meio + 1, fim );
}

void insert( int no, int ini, int fim, ll y1, ll y2, int val ){
	if( y1 > fim || y2 < ini ) return;
	
	if( y1 <= ini && y2 >= fim ){
		op[ no ] += val;
//		printf( "Inseri inter %lld %lld em %d %d\n", y1, y2, ini, fim );
	}else{
		int meio = ( ini + fim ) / 2;
		insert( 2 * no, ini, meio, y1, y2, val );
		insert( 2 * no + 1, meio + 1, fim, y1, y2, val );
	}
}

int query( int no, int ini, int fim, ll y ){
	if( y < ini || y > fim ) return 0;
	
	conserta( no );
	
	if( ini == fim && ini == y )
		return tree[ no ];
	else{
		int meio = ( ini + fim ) / 2;
		return query( 2 * no, ini, meio, y ) + query( 2 *  no + 1, meio + 1, fim, y );
	}
}

int aux;


int main(){
	mapa.clear();
	conj.clear();
	aux = 1;
	
	scanf( "%d %d", &n, &k );
	int prt = 0;
	for( int i = 0; i < n; ++i ){
		ll x, y;
		ll d;
		scanf( "%lld %lld %lld", &x, &y, &d );
		
		ll x1 = x + y - d, y1 = y - d - x;
		ll x2 = x + y + d, y2 = y - x - d;

		ll temp = x;
		x = x + y;
		y = y - temp;
		
		conj.insert( y1 );
		conj.insert( y2 );
		conj.insert( y1 + 2 * d );
		conj.insert( y2 + 2 * d );
		conj.insert( y );
		
		nos[ prt++ ].set( x1, y1, y1 + 2 * d, INICIO );
		nos[ prt++ ].set( x2, y2, y2 + 2 * d, FIM );
		nos[ prt++ ].set( x, y, -1, i + 1 );
	
	}
	
	for( set<ll>::iterator it = conj.begin(); it != conj.end(); ++it )
		mapa[ *it ] = aux++; 
	
	for( int i = 0; i < prt; ++i ){
		nos[ i ].y = mapa[ nos[i].y ];
		if( nos[ i ].id < 0 )
			nos[ i ].fim = mapa[ nos[i].fim ];
	}
	--aux;
	sort( nos, nos + prt );
	build( 1, 1, aux );
	
	for( int i = 0; i < prt; ++i ){
		if( nos[ i ].id == INICIO ){
			insert( 1, 1, aux, nos[ i ].y, nos[ i ].fim, 1 );
		}else if( nos[ i ].id == FIM ){
			
			insert( 1, 1, aux, nos[ i ].y, nos[ i ].fim, -1 );
		}else{
			qtd[ nos[i].id ] = query( 1, 1, aux, nos[ i ].y );
		}
	}
	vector<int> resp;
	for( int i = 1; i <= n; ++i ){
		if( qtd[ i ] > k ) resp.push_back( i );
	}
	
	printf( "%d\n", resp.size() );
	for( int i = 0; i < resp.size(); ++i )
		printf( "%d%c", resp[ i ], i == resp.size() - 1 ? '\n' : ' ' );
}


