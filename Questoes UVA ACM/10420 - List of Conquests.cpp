#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main(){
	int n, contp;
	map<string,int> pais;
	set<string> qtd[ 3000 ];
	char mulher[ 3000 ], nome[ 3000 ];
	
	scanf( "%d", &n );
	contp = 0;
	while( n-- ){
		scanf( "%s", nome );
		if( pais.find( nome ) == pais.end() ){
			pais[ nome ] = contp;
			qtd[ contp ].clear();
			++contp;
		}
		
		gets( mulher );
		char* aux = mulher;
		while( *aux == ' ' ) ++aux;
		
		qtd[ pais[ nome ] ].insert( aux ).second;
	}
	
	for( map<string,int>::iterator it = pais.begin(); it != pais.end(); ++it ){
		cout << it -> first << " " << qtd[ it -> second ].size()  << endl;
	}
}




