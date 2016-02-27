#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <queue>
using namespace std;
#define oo 0x7fffffff
#define mp make_pair

set< vector<int> > pd;

int mapa[ 300 ];

int front = 0, back = 1, right = 2, left = 3, top = 4, bottom = 5;
 
vector<int> lado( const vector<int>& d ){
	vector<int> temp( 6, 0 );
	
	temp[ top ] = d[ top ];
	temp[ bottom ] = d[ bottom ];
	
	temp[ front ] = d[ right ];
	temp[ right ] = d[ back ];
	temp[ back ] = d[ left ];
	temp[ left ] = d[ front ];
	
	return temp;
}

vector<int> cima( const vector<int>& d ){
	vector<int> temp( 6, 0 );
	
	temp[ left ] = d[ left ];
	temp[ right ] = d[ right ];
	
	temp[ front ] = d[ bottom ];
	temp[ bottom ] = d[ back ];
	temp[ back ] = d[ top ];
	temp[ top ] = d[ front ];
	
	return temp;
}


int main(){
	pd.clear();
	memset( mapa, -1, sizeof( mapa ) );
	int cont = 0;
	char buf[ 100 ];
	scanf( "%s", buf );
	vector<int> dado;
	
	for( int i = 0; buf[ i ]; ++i ){
		if( mapa[ buf[i] ] == -1 ){
			dado.push_back( cont );
			mapa[ buf[i] ] = cont++;
		}else
			dado.push_back( mapa[ buf[i] ] );
	}
	
	int qtd = 0;
	pd.clear();
	do{
		bool dm = false;
		vector<int> temp = dado;
		for( int i = 0; !dm && i < 4; ++i ){
			for( int j = 0; j < 4; ++j ){
				if( pd.find( temp ) != pd.end() ){
					dm = true;
					break;
				}
				temp = cima( temp );
			}
			temp = lado( temp );
		}

		if( !dm ){
			vector<int> temp = dado;
			for( int i = 0; !dm && i < 4; ++i ){
				for( int j = 0; j < 4; ++j ){
					vector<int> t = temp;
					pd.insert( t );
					temp = cima( temp );
				}
				temp = lado( temp );
			}		
			++qtd;
		}
		
	}while( next_permutation( dado.begin(), dado.end() ) );
	
	printf( "%d\n", qtd );
}

