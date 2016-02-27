#include <iostream>
using namespace std;

//a -> parte real do numero
//b -> parte imaginaria do numero
class Complexo{
	public:
		int a, b;
};

int abs( int a ){
	if( a < 0 )
		return -a;
	return a;
}

bool verifica( Complexo& c, int a, int b ){
	if( (a | b) == 0 )
		return false;

	int norma_quadrado = a * a + b * b;
	if( norma_quadrado == 1 )
		return false;

	//Conjugado!
	b = -b;
	int parte_real, parte_imaginaria;

	parte_real = (c.a * a - c.b * b);
	parte_imaginaria = ( c.a * b + c.b * a );

	if( ( parte_real % norma_quadrado != 0 ) || ( parte_imaginaria % norma_quadrado != 0 ) )
		return false;

	parte_real /= norma_quadrado;
	parte_imaginaria /= norma_quadrado;

	if( ( parte_real * parte_real + parte_imaginaria * parte_imaginaria ) == 1 )
		return false;

	return true;
}

int main(){
	int numeros;
	Complexo lido;

	bool primo;

	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );

	cin >> numeros;

	while( numeros-- ){
		primo = true;
		cin >> lido.a >> lido.b;

		int a, b;

/*		if( lido.a % 2 == 0 && lido.b % 2 == 0 )
			primo = false;
		else if( lido.a % 2 != 0 && lido.b % 2 != 0 )
			primo = false; */
		for( a = -200; a <= 200 && primo; ++a ){
			for( b = -200; b <= 200; ++b ){
				if( verifica( lido, a, b ) ){
					primo = false;
					break;
				}
			}
		}

		if( primo )
			cout << "P" << endl;
		else
			cout << "C" << endl;


	}

}
