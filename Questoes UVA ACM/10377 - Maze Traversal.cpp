#include <iostream>
using std::cin;
using std::cout;

const int norte = 0, leste = 1, sul = 2, oeste = 3;
char maze[ 61 ][ 61 ];
int qtd_linhas, qtd_colunas;

class Robot{
	public:
		int direcao;
		int linha;
		int coluna;
		
		void andar(){
			switch( direcao ){
			case norte:
				if( maze[ linha - 1 ][ coluna ] != '*' )
					--linha;
			break;
			case sul:
				if( maze[ linha + 1 ][ coluna ] != '*' )
					++linha;
			break;
			case leste:
				if( maze[ linha ][ coluna + 1 ] != '*' )
					++coluna;
			break;
			case oeste:
				if( maze[ linha ][ coluna - 1 ] != '*' )
					--coluna;
			break;
			}
		}
		
		void virar( char arg ){
			if( arg == 'L' ){
				--direcao;
				
				if( direcao < 0 )
					direcao += 4;
			}else{
				++direcao;
				if( direcao > 3 )
					direcao -= 4;
			}
		}
		
}robo;

int main(){
	int vezes;
	char buffer;
	char direcao_final[] = { 'N', 'E', 'S', 'W' };
			
	cin >> vezes;
	while( vezes-- ){
		cin >> qtd_linhas >> qtd_colunas;
		cin.ignore();
		
		for( int i = 1; i <= qtd_linhas; ++i ){
			for( int j = 1; j <= qtd_colunas; ++j )
				cin.get( maze[ i ][ j ] );
			cin.ignore();
		}
		
		robo.direcao = norte;
		cin >> robo.linha >> robo.coluna;
		
		
		while( true ){
			cin.get( buffer );
			
			if( buffer == ' ' || buffer == '\n' )
				continue;
			if( buffer == 'R' || buffer == 'r' )
				robo.virar( 'R' );
			else if( buffer == 'L' || buffer == 'l' )
				robo.virar( 'L' );
			else if( buffer == 'F' || buffer == 'f' )
				robo.andar();
			else if( buffer == 'Q' || buffer == 'q' )
				break;
		}
		
		cout << robo.linha << " " << robo.coluna << " " << direcao_final[ robo.direcao ] << std::endl;
		if( vezes )
			cout << std::endl;
	}
	
	
}

