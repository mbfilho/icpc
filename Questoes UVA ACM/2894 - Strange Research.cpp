#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

map<string, pair<string,int> > maior;
map<string,string> menor;

int main(){
	string ori, ord;
	map<string,pair<string,int> >::iterator it;
	map<string,string>::iterator it2;
	
	int qtd;
	
	scanf( "%d", &qtd );
	
	char nome[80];
	
	while( qtd-- ){
		scanf( "%s", nome );
		ori = string( nome );
		
		if( ori.size() > 1 )
			sort( nome + 1, nome + ori.size() - 1 );
		ord = string( nome );
		
		if( (it = maior.find( ord )) != maior.end() ){
			++(it -> second).second;

			if( (it -> second).first < ori )
				(it -> second).first = ori;
			
			it2 = menor.find( ord );
			if( ori < ( it2 -> second ) )
				it2 -> second = ori;
		}else{
			maior[ ord ] = make_pair( ori, 1 );
			menor[ ord ] = ori;
		}
	}
	
	scanf( "%d", &qtd );
	string pal;
	while( qtd-- ){
		scanf( "%s", nome );
		
		if( strlen( nome ) > 1 )
			sort( nome + 1, nome + strlen( nome ) - 1 );
		pal = string( nome );
		
		if( (it = maior.find(pal) ) != maior.end() )
			cout << (it -> second).second << " " << menor[ pal ] << " " << (it -> second).first << endl;
		else
			cout << "0" << endl;
	}
	

}
