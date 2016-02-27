/*
Dado um intervalo [a,b] e um número N, é fácil encontrar a soma de todos os multiplos
de N nesse intervalo, utilizando a fórmula de soma da P.A. Faço isso no método resolver.
A dificuldade desse problema está na aplicação do principio da inclusão-exclusao.
Imagine que são dados os números 2 e 4. Os números 4, 8, 16 ... serão incluídos 2 vezes
na soma. É preciso retirar os repetidos, mas como? Embora seja tentador retirar os 
multiplos do produto ( 2 * 4 ), isso está claramente errado. Voce deve retirar os
multiplos do mmc [ mmc( 2, 4 ) =P ]. Para achar o mmc de forma eficiente, utilize
a identidade: mmc( a, b ) * mdc( a, b ) = a * b. No método 'incExc' eu gero todas as
combinações dos números ( dois a dois, tres a tres ... ) para aplicar o principio
da inclusão - exclusão. Retire as combinações pares ( dois a dois, quatro a quatro...)
e soma de volta as combinações impares.
*/


#include <iostream>
using namespace std;
#define max( a, b ) (a) < (b)? (a) : (b)
#define mod 1300031

long long ini, fim;
typedef long long ll;

int array[ 20 ];
int tam;
int auxiliar[ 21 ];

ll resolver( ll y ){
	if( y > fim )
		return 0;
	
	ll a1, an, n;
	ll soma = 0;

	ll modulo = ini % y;
	a1 = ini;
	if( modulo != 0 )
		a1 += ( y - modulo );

	an = fim - ( fim % y );
	n = 1 + ( an - a1 ) / y;

	if( a1 > an )
		return 0;
	soma = a1 + an;

	if( soma % 2 == 0 )
		soma = soma / 2;
	else
		n = n / 2;
	soma = soma % mod;
	soma = ( soma * ( n % mod ) ) % mod;

	return soma;
}

ll euclides( ll a, ll b ){
	ll menor;
	while( b ){
		menor = a % b;
		a = b;
		b = menor;
	}
	
	return a;
}

ll mdc( ll a, ll b ){
	return a * b / euclides( a, b );
}

ll incExc( int ordem ){
	for( int i = 1; i <= tam; ++i )
		auxiliar[ i ] = i;
		
	ll soma = 0;
	ll prod;
	
	while( true ){
		prod = 1;
		for( int i = 1; i <= ordem; ++i )
			prod = mdc( prod, array[ auxiliar[ i ] - 1 ] );
		soma += resolver( prod );
		
		
		int j = ordem;
		while( j && auxiliar[ j ] == ( tam - ordem + j ) )
			--j;
		if( j == 0 )
			break;
			
		++auxiliar[ j ];
		
		for( j = j + 1; j <= ordem; ++j )
			auxiliar[ j ] = auxiliar[ j - 1 ] + 1;
		
	}
	
	return soma;
}
 
int main(){
	int casos;
	ll resposta;
	cin >> casos;

	while( casos-- ){
		resposta = 0;
		cin >> ini >> fim >> tam;	
		
		for( int i = 0; i < tam; ++i ){
			cin >> array[ i ];
			//resposta += resolver( array[ i ] ) % mod;
		}
		
		bool soma = true;
		ll temp;
		for( int i = 1; i <= tam; ++i ){
			temp = incExc( i );
			if( temp == 0 )
				break;
			if( soma )
				 resposta = ( resposta + temp ) % mod;
			else{
				resposta -= temp;
				while( resposta < 0 )
					resposta += mod;
			}
			soma = !soma;
		}
		
		cout << resposta << endl;
	}
}
