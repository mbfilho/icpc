#include <iostream>
#include <algorithm>
using namespace std;

class Doll{
public:
	int alt, larg;
	
	bool operator<( const Doll& outra ) const{
		if( larg < outra.larg )
			return true;
		else if( larg == outra.larg )
			return outra.alt < alt;
		else
			return false;
	}
};

int busca( int val ){
}

int main(){

	Doll bonecas[ 20001 ];
	int solucao[ 20001 ];
	int cont;
	
	int casos, qtd_b;
	bool achou;
	bonecas[ 0 ].alt = bonecas[ 0 ].larg = -1;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	
	while( casos-- ){
		cont = 0;
		cin >> qtd_b;
		
		for( int i = 1; i <= qtd_b; ++i )
			cin >> bonecas[ i ].larg >> bonecas[ i ].alt;
		
		sort( bonecas, bonecas + qtd_b + 1 );
		
		solucao[ cont++ ] = bonecas[ 1 ].alt;
		
		for( int i = 2; i <= qtd_b; ++i ){
			achou = false;
			//Busca a maior boneca
			for( int j = 0; j < cont; ++j ){
				if( solucao[ j ] < bonecas[ i ].alt ){
					solucao[ j ] = bonecas[ i ].alt;
					achou = true;
					j = cont;
				}
			}
			
			if( achou == false )
				solucao[ cont++ ] = bonecas[ i ].alt;
		}
		
		cout << (cont) << endl;
	}
}
