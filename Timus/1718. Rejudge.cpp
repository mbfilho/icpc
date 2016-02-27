#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
using namespace std;


set<string> mapa;
set<string> mapa2;

int main(){

	
	int casos, cont = 0, min = 0;
	set<string>::iterator it, it2;
	
	freopen( "in.txt", "r", stdin );
		
	cin >> casos;
	
	string nome, jud;
	int x;
	while( casos-- ){
		cin >> nome >> jud;
		
		int tam = nome.size();
		for( int i = 0; i < tam; ++i ){
			if(nome[i] >= 'A' && nome[i] <= 'Z'){
				nome[i] -= 'A';
				nome[i] += 'a';	
			}	
		}
		
		it = mapa.find( nome );
		if( jud == "AC" ){
			if( it == mapa.end() ){
				++cont;
				mapa.insert( nome );
			}
		}else if( jud != "CE" ){
			cin >> x;
			it2 = mapa2.find( nome );
			
			if( it == mapa.end() && x >= 6 ){
				++cont;
				mapa.insert( nome );
			}
			
			if( it2 == mapa2.end() && x == 7 ){
				++min;
				mapa2.insert( nome );
			}
			
		}
	}
	
	cout <<  min << " " << cont << endl;
	
}

