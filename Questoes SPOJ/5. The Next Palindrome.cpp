#include <cstdio>
#include <string>
#define MAX 1000000
//http://www.spoj.pl/problems/PALIN/

/*
Todo número palindromo é espelhado em relação ao seu elemento central. Portanto, dado
um número, para encontrar um palindromo basta espelhá-lo sobre seu eixo. No entanto,
fazer isso pode acabar por gerar um número menor que o original. Agora, se quisessemos
encontrar um número maior que o original, mesmo sem ser palindromo, incrementariamos
o número original certo? Somariamos 1 ao digito menos significativo. Mas, como um 
palindromo é espelhado, esse numero incrementado só seria um palindromo se o digito
mais significativo também fosse incrementado (para "casar com o digito menos significativo").
Isso geraria um número muito maior que o original. Perceba que, o menor palindromo 
que ainda é maior que o número original, é encontrado incrementando o número a partir
do seu eixo. Isso se deve justamente porque o palindromo é espelhado. Esse é o algoritmo.
Leia o número e o espelhe em relação ao seu eixo ( tome cuidado com o fato do número
de digitos ser par ou impar, claro ). Se o número gerado for maior que o original, pronto
você já encontrou seu palindromo. Se não for, incremente o número a partir do digito
central ( mais uma vez, tome cuidado com a paridade do tamanho da string ). Feito isso,
espelhe o número e pronto! Existe um caso especial a ser tratado. É o caso em que
a entrada é um número formado só de 9's. Nesse caso, o maior palindromo é sempre
o número + 2. Esse caso é sinalizado pela necessidade de se aumentar o número de 
digitos no resultado ( o carry final é 1: "overflow" ). Nesse caso imprima 1 + "k" zeros
+ 1. Conta simples: k = tam + 1 - 2 = tam - 1.
*/

char num[ MAX + 10 ];
int tam;
bool cuidado;

void resolver(){
	cuidado = false;
	
	int meio = tam / 2 - 1;
	bool maior = false;
	
	for( int i = meio; i >= 0; --i ){
		if( num[i] < num[tam - i - 1] )
			break;
		if( num[i] > num[tam - i - 1] ){
			maior = true;
			break;
		}
	}
	
	if( maior )
		return;
	
	if( tam % 2 == 1 )
		++meio;
		
	int carry = 1;	
	
	for( int i = meio; i >= 0; --i ){
		num[i] += carry;
		if( num[i] - '0' >= 10 ){
			carry = 1;
			num[i] -= 10;
		}else{
			carry = 0;
			break;
		}
	}
	cuidado = (carry == 1);	
}

void print(){
	if( cuidado ){
		int zeros = tam - 1;
		printf( "1" );
		for( int i = 0; i < zeros; ++i )
			printf( "0" );
		printf( "1\n" );
	}else{
		int meio = tam / 2 - 1;

		for( int i = 0; i <= meio; ++i )
			printf( "%c", num[i] );
		if( tam % 2 == 1 )
			printf( "%c", num[meio + 1] );
		for( int i = meio; i >= 0; --i )
			printf( "%c", num[i] );
	
		printf( "\n" );	
	}
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s", num );
		tam = strlen( num );
		resolver();
		print();
	}
}
