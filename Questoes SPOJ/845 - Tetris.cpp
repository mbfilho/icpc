#include <iostream>
#include <algorithm>
using namespace std;


class Jog{
	public:
		string nome;
		int pontos[ 12 ];
		int pontuacao;
		
	bool operator<( const Jog& outro ) const{
		if( pontuacao > outro.pontuacao )
			return true;
		else if( pontuacao < outro.pontuacao )
			return false;
		else
			return ( nome < outro.nome );
	}
};

int main(){
	Jog jogs[ 1000 ];
	int jog;
	int teste = 1;
	
	cin >> jog;
	while( jog ){
		for( int k = 0; k < jog; ++k ){
			cin >> jogs[ k ].nome;
			for( int x = 0; x < 12; ++x )
				cin >> jogs[ k ].pontos[ x ];
		}
		
		for( int i = 0; i < jog; ++i ){
			sort( jogs[ i ].pontos, jogs[ i ].pontos + 12 );
			jogs[ i ].pontuacao = 0;
			for( int j = 1; j < 11; ++j )
				jogs[ i ].pontuacao += jogs[ i ].pontos[ j ];
		}
		
		cout << "Teste " << teste++ << endl;
		sort( jogs, jogs + jog );
		int posicao = 0;
		int p = 1;
		for( int u = 1; u <= jog; ++u ){
			if( u == 1 || jogs[ u - 2 ].pontuacao > jogs[ u - 1 ].pontuacao ){
				( posicao += p );
				cout << posicao;
				p = 1;
			}else{
				cout << posicao;
				++p;
			}
			cout << " " << jogs[ u - 1 ].pontuacao << " " << jogs[ u - 1 ].nome << endl;
		}
		
		cout << endl;
	
		cin >> jog;
	}
	
	
}