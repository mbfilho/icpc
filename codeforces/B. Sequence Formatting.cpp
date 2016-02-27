#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <list>
#include <iostream>
using namespace std;
#define mp(x,y) make_pair(x,y)
typedef long long ll;

bool ehDigito( char c ){
	return c >= '0' && c <= '9';
}

int main(){
	string saida = "";
	string in;
	bool primeiro = true;
	string linha;
	
	getline( cin, linha );
	
	int tam = linha.size();
	bool esp = false;
	for( int i = 0; i < tam; ++i ){
		if( linha[ i ] == ',' ){
			saida += ", ";
		}else if( linha[ i ] == '.' ){
			if( !saida.size() || saida[ saida.size() - 1 ] == ' ' ){
				saida += "...";
			}else{
				saida += " ...";
			}
			i += 2;
		}else if( ehDigito( linha[ i ] ) ){
			if( saida.size() && ehDigito( saida[ saida.size() - 1 ] ) ){
				if( esp ){
					saida += " ";
					saida += linha[ i ];
				}else
					saida += linha[ i ];
			}else
				saida += linha[ i ];
		}else if( linha[ i ] == ' ' ){
			esp = true;
			continue;
		}
		esp = false;			
	}
	
	if( saida.size() ){
		if( saida[ 0 ] == ' ' ){
			saida = saida.substr( 1, saida.size() - 1 );
		}
		if( saida.size() ){
			if( saida[ saida.size() - 1 ] == ' ' ){
				int s = saida.size() - 1;
				for( int i = 0; i < s; ++i )
					cout << saida[ i ];
				cout << endl;
			}else
				cout << saida << endl;			
		}else
			cout << endl;
	}else
		cout << endl;
}

