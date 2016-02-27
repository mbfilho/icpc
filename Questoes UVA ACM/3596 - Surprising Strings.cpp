#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <set>
using namespace std;


int main(){
	int tam;
	bool dm;
	string nome;
	set<string> conj;
	
	while( cin >> nome && nome != "*"  ){		
		tam = nome.size();
		dm = false;
		
		for( int p = 0; p <= tam - 2 && !dm; ++p ){
			conj.clear();
			for( int i = 0; i + p + 1 < tam && !dm; ++i ){
				string temp = "";
				temp += nome[ i ];
				temp += nome[ i + p + 1 ];
				
				if( conj.find( temp ) != conj.end() )
					dm = true;
				else
					conj.insert( temp );
			}
		}
		
		if( dm )
			cout << nome << " is NOT surprising.";
		else
			cout << nome << " is surprising.";
		cout << endl;
	}
	
	
	
	
	
}

