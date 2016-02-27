#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 2000
#define mp make_pair

struct No{
	int first, second, id;
	int room;
}nos[ N ];

int quartos[ N ];
vector< pair<int,int> > aux;
int n;

bool snd( const No& a, const No& b ){
	return a.second < b.second;
} 

bool porId( const No& a, const No& b ){
	return a.id < b.id;
}

int main(){
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i ){
		scanf( "%d", &quartos[ i ] );
		aux.push_back( mp( quartos[ i ], i ) );
	}
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d %d", &nos[ i ].first, &nos[ i ].second );
		nos[i].id = i;
	}
	
	sort( aux.begin(), aux.end() );
	sort( nos, nos + n, snd );
	
	bool dm = false;
	for( int i = 0; i < n && !dm; ++i ){
		int ini = 0, fim = aux.size() - 1, meio, resp = -1;
		while( ini <= fim ){
			meio = ( ini + fim ) / 2;
			if( aux[ meio ].first < nos[ i ].first )
				ini = meio + 1;
			else if( aux[ meio ].first > nos[ i ].second )
				fim = meio - 1;
			else{
				resp = meio;
				fim = meio - 1;
			}
		}
		if( resp != -1 ){
			nos[ i ].room = aux[ resp ].second;
			aux.erase( aux.begin() + resp );
		}else dm = true;
	}
	
	
	if( !dm ){
		sort( nos, nos + n, porId );
		bool pode = false;
		for( int i = 1; !pode && i < n; ++i ){
			for( int j = 0; !pode && j < i; ++j ){
				if( quartos[ nos[i].room ] >= nos[ j ].first && quartos[ nos[i].room ] <= nos[ j ].second ){
					if( quartos[ nos[j].room ] >= nos[ i ].first && quartos[ nos[j].room ] <= nos[ i ].second ) pode = true;
				}
			}
		}
		
		if( pode ) printf( "Ask Shiftman for help.\n" );
		else{
			printf( "Perfect!\n" );
			printf( "%d", nos[ 0 ].room + 1 );
			for( int i = 1; i < n; ++i )
				printf( " %d", nos[ i ].room + 1 );
			printf( "\n" );
		}
	}else
		printf( "Let's search for another office.\n" );
}

