#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

class Arvore{
public:
	list<int> adj;
}nos[ 100001 ];

int t, qtd;

int resolver( int ind ){
	if( nos[ ind ].adj.size() == 0 )
		return 1;
		
	vector<int> results;

	for( list<int>::iterator it = nos[ ind ].adj.begin(); it != nos[ ind ].adj.end(); ++it )
		results.push_back( resolver( *it ) );
	
	int soma = 0;
	int qtd = ( t * nos[ ind ].adj.size() + 99 ) / 100;
	
	sort( results.begin(), results.end() );
	
	for( int i = 0; i < qtd; ++i )
		soma += results[ i ];
	
	return soma;
}

int main(){
	int pai;
	
	freopen( "in.txt", "r", stdin );
    freopen( "out.txt", "w", stdout );
	
	while( cin >> qtd >> t && ( qtd | t ) ){
		
		for( int i = 1; i <= qtd; ++i ){
			cin >> pai;
			
			nos[ pai ].adj.push_back( i );
		}
		
		cout << resolver( 0 ) << endl;
		
		for( int i = 0; i <= qtd; ++i )
			nos[i].adj.clear();
	}
}
