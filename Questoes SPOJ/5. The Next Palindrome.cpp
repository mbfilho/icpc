#include <cstdio>
#include <string>
#define MAX 1000000
//http://www.spoj.pl/problems/PALIN/

/*
Todo n�mero palindromo � espelhado em rela��o ao seu elemento central. Portanto, dado
um n�mero, para encontrar um palindromo basta espelh�-lo sobre seu eixo. No entanto,
fazer isso pode acabar por gerar um n�mero menor que o original. Agora, se quisessemos
encontrar um n�mero maior que o original, mesmo sem ser palindromo, incrementariamos
o n�mero original certo? Somariamos 1 ao digito menos significativo. Mas, como um 
palindromo � espelhado, esse numero incrementado s� seria um palindromo se o digito
mais significativo tamb�m fosse incrementado (para "casar com o digito menos significativo").
Isso geraria um n�mero muito maior que o original. Perceba que, o menor palindromo 
que ainda � maior que o n�mero original, � encontrado incrementando o n�mero a partir
do seu eixo. Isso se deve justamente porque o palindromo � espelhado. Esse � o algoritmo.
Leia o n�mero e o espelhe em rela��o ao seu eixo ( tome cuidado com o fato do n�mero
de digitos ser par ou impar, claro ). Se o n�mero gerado for maior que o original, pronto
voc� j� encontrou seu palindromo. Se n�o for, incremente o n�mero a partir do digito
central ( mais uma vez, tome cuidado com a paridade do tamanho da string ). Feito isso,
espelhe o n�mero e pronto! Existe um caso especial a ser tratado. � o caso em que
a entrada � um n�mero formado s� de 9's. Nesse caso, o maior palindromo � sempre
o n�mero + 2. Esse caso � sinalizado pela necessidade de se aumentar o n�mero de 
digitos no resultado ( o carry final � 1: "overflow" ). Nesse caso imprima 1 + "k" zeros
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
