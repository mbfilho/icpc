#include <cstdio>
#include <cmath>

/*
Defina os sandwiches como 0 e 1.
O que � muito importante notar nesse problema � que n�o se trata apenas contar todas as 
combina��es de strings ...00 e ...11 e dividir pelo total de combina��es. Isso 
porque o problema fala que para TODOS os participantes exceto APENAS Bill e Ben,
a moeda FOI lan�ada, o que quer dizer que houve escolha e nenhum dos dois tipos
de sandwiches foi esgotado AT� a vez de Bill e Ben. Portanto, � mais facil contar
as strings do tipo A: ...01 e B: ...10 porque se o primeiro deles teve uma escolha, ent�o
todos os anteriores tamb�m tiveram. A probabilidade de ocorrer a string 'A' � de 
1/2 * (1/2) ^ (n - 2) [ n - 2 dos demais convidados e 1/2 do primeiro entre bill e ben ].
De forma an�loga, a string B tem probabilidade 1/2 * (1/2) ^ (n - 2). Somando, a 
probabilidade de A ou B � P( A ou B ) = (1/2) ^ (n - 2). OK, n�s sabemos a probabilidade
de 1 sequencia, basta somar todas elas. Quantas sequencias desse tipo existem?
Tirando bill e ben, existem (n - 2) convidados, e n - 2 sandwiches, n/2 - 1 de cada tipo.
Verifique que basta calcular a combina��o (n - 2) C (n/2 - 1). Ent�o procuramos pela
f�rmula 1 - ( (n - 2) C (n/2 - 1) *   (1/2) ^ (n - 2) ). Agora a parte interessante:
n vai at� 100000. N�o d� pra calcular os fatoriais necess�rios para a combina��o e
a exponencia��o vai gerar um resultado muito pequeno. Para contornar isso, � suficiente
trabalhar com os logaritmos. log(n!) = somatorio( i = 1, i <= n ) log(i)[ obvio ne? ].
Ent�o, a expressao de (n C k) fica: exp( log(n!) - log(n-k!) - log(k!) ). Aplicando
logaritmo � expressao toda, a parte (1/2) ^ (n - 2) se torna -(n - 2)*log(2).
A funcao preencher precalcula todos os logaritmos necessarios e o problema se torna simples.
*/



double fat[100001];

void preencher(){
	fat[ 1 ] = 0.0;
	
	for( int i = 2; i <= 100000; ++i )
		fat[ i ] = fat[ i - 1 ] + log( i );
}


int main(){
	int n, casos;
	const double LOG2 = log( 2 );
	double resp;
	
	preencher();

	scanf( "%d", &casos );	
	while( casos-- ){
		scanf( "%d", &n );
		resp = fat[ n - 2 ] - 2 * fat[ n / 2  - 1 ] - LOG2 * double(n - 2); 
		printf( "%.4lf\n", 1 - exp( resp ) );
	}
}

