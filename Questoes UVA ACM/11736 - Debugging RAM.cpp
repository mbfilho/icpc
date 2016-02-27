#include <iostream>
#include <string>
#include <map>
using namespace std;

string nomes[ 400 ];
int bytes[ 400 ];
typedef unsigned long long ull;

int qtd;

ull getNumero( string& s ){
	ull retorno = 0;
	ull aux = 1;
	
	for( int i = s.size() - 1; i >= 0; --i ){
		if( s[ i ] == '1' )
			retorno |= aux;
		aux = aux << 1;
	}
	
	return retorno;
}

int main(){
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	int b, v;
	int qtd = 0;
	string buffer, num;
	int tam;
	int quer;
	map<string,ull>::iterator it;
	
	while( cin >> b >> v ){
		map<string,ull> mapa;
		for( qtd = 0; qtd < v; ++qtd )
			cin >> nomes[ qtd ] >> bytes[ qtd ];
		
		for( int i = 0; i < qtd; ++i ){
			num = "";
			for( int j = 0; j < bytes[ i ]; ++j ){
				cin >> buffer;
				num += buffer;
			}
			unsigned long long numero = getNumero( num );
		//	cout << num << " " << numero << endl;
			mapa[ nomes[ i ] ] = numero;
		}
		
		cin >> quer;
		for( int i = 0; i < quer; ++i ){
			cin >> buffer;
			it = mapa.find( buffer );
			if( it == mapa.end() )
				cout << buffer << "=" << endl;
			else
				cout << buffer << "=" << it -> second << endl;
		}
	}
	
	
	
}
