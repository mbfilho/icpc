#include <cstdio>
#include <list>
#include <queue>
using namespace std;

class Ares{
public:
	int b, peso;
	
	Ares( int b, int p ){
		this -> b =  b;
		this -> peso = p;
	}
};

class No{
public:
	list<Ares> adj;
	bool marcado;
	int dist;
}nos[ 1000 ];

class noh{
public:
	int id;
	int dist;
	
	noh(){}
	
	noh( int id, int di ){
		this -> id = id;
		dist = di;
	}
	
	bool operator<( const noh& a ) const{
		return !( dist < a.dist );
	}
};


void dij( int ini ){
	nos[ ini ].dist = 0;
	priority_queue<noh> heap;
	heap.push( noh( ini, 0 ) );
	noh temp;
	list<Ares>::iterator it;
	
	while( heap.empty() == false ){
		temp = heap.top();
		heap.pop();
		
		if( nos[ temp.id ].marcado == true )
			continue;
		nos[ temp.id ].marcado = true;
		nos[ temp.id ].dist = temp.dist;
		
		for( it = nos[ temp.id ].adj.begin(); it != nos[ temp.id ].adj.end(); ++it ){
			//cout << (nos[ it -> b ].dist) << " " << (nos[ temp.id ].dist + it -> peso) << endl;
			if( nos[ it -> b ].marcado == false && nos[ it -> b ].dist > (nos[ temp.id ].dist + it -> peso) ){
				nos[ it -> b ].dist = (nos[ temp.id ].dist + it -> peso);
				heap.push( noh( it -> b, nos[ it -> b ].dist ) );
			}
		}
		
	}
}

int main(){

	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	

	int casos, n, m, saida, tempo;
	
	scanf( "%d", &casos );
	
	for( int u = 1; u <= casos; ++u ){
		scanf( "%d %d %d %d", &n, &saida, &tempo, &m );
		
		int a, b, p;
		
		for( int i = 1; i <= n; ++i )
				nos[ i ].adj.clear();
				
		for( int i = 1; i <= m; ++i ){
			scanf( "%d %d %d", &a, &b, &p );
			nos[ b ].adj.push_back( Ares( a, p ) );
		}

		int cont = 1;


		for( int i = 1; i <= n; ++i ){
			nos[ i ].marcado = false;
			nos[ i ].dist = 0x7fffffff;
		}
		dij( saida );
		for( int j = 1; j <= n; ++j ){
			if( j == saida )
				continue;
			if( nos[ j ].dist <= tempo )
				++cont;
		}
		
		printf( "%d\n", cont );
		if( u != casos )
			printf( "\n" );
	}
}
