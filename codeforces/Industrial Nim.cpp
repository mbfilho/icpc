#include <iostream>
using namespace std;

typedef unsigned long long ll;
/*
� um jogo Nim. Tem de fazer o xor entre todos os dumpers e ver o resultado.
Mas os n�meros s�o muito grandes, e por isso n�o d� pra fazer diretamente.
Os dumpers de cada quarry est�o organizados assim: o primeiro tem "a" pedras,
o segundo tem "a+1" pedras e assim sucessivamente at� o ultimo ter b = a + m - 1 pedras.
Fazer um xor de [a..b] � o mesmo de fazer [0..a-1] xor [0..b]. Se conven�a que o xor 
de [0..c], onde c � um multiplo de 4, � o proprio c. Ent�o, para calcular o xor de [0..a]
encontre o multiplo de 4 mais proximo a e fa�a o xor desse mutiplo at� a. N�o s�o mais
que 4 opera��es, idependente do n�mero a. Feito isso, o resto fica facil. Fa�a o xor dos
dumpers e verifique se da 0 ou n�o.
*/
//ll pots[ 64 ];
int n;

/*Funciona, mas o outro � mt mais eficiente!
ll nim( ll k ){
	ll retorno = 0;

	for( int i = 1; i < 63; ++i ){
		if( (k & pots[i]) != 0 && (k % 2 == 0 ) )
			retorno |= pots[i];
		
	}
	
	if( k % 4 == 2 || k % 4 == 1 )
		retorno |= 1;
		
	return retorno;
}
*/

ll nim( ll k ){
	ll retorno = 0;
	
	for( ll i = k - ( k % 4 ); i <= k; ++i )
		retorno = retorno xor i;
	return retorno;
}

int main(){
	/*
	pots[ 0 ] = 1LL;
	for( int i = 1; i < 64; ++i )
		pots[i] = pots[i - 1] * 2;
	*/
	
	ll x, m;
	
	cin >> n;
	
	ll nimsum = 0;
	
	for( int i = 0; i < n; ++i ){
		cin >> x >> m;
		if( m != 1 )
			nimsum = ( ( nimsum ^ nim( x - 1 ) ) ^ nim( x + m - 1LL ) );
		else
			nimsum = nimsum ^ x;
	}
	
	if( nimsum == 0 )
		cout << "bolik" << endl;
	else
		cout << "tolik" << endl; 
}
