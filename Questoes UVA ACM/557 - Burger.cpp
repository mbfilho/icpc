#include <cstdio>
#include <cmath>

/*
Defina os sandwiches como 0 e 1.
O que é muito importante notar nesse problema é que não se trata apenas contar todas as 
combinações de strings ...00 e ...11 e dividir pelo total de combinações. Isso 
porque o problema fala que para TODOS os participantes exceto APENAS Bill e Ben,
a moeda FOI lançada, o que quer dizer que houve escolha e nenhum dos dois tipos
de sandwiches foi esgotado ATÉ a vez de Bill e Ben. Portanto, é mais facil contar
as strings do tipo A: ...01 e B: ...10 porque se o primeiro deles teve uma escolha, então
todos os anteriores também tiveram. A probabilidade de ocorrer a string 'A' é de 
1/2 * (1/2) ^ (n - 2) [ n - 2 dos demais convidados e 1/2 do primeiro entre bill e ben ].
De forma análoga, a string B tem probabilidade 1/2 * (1/2) ^ (n - 2). Somando, a 
probabilidade de A ou B é P( A ou B ) = (1/2) ^ (n - 2). OK, nós sabemos a probabilidade
de 1 sequencia, basta somar todas elas. Quantas sequencias desse tipo existem?
Tirando bill e ben, existem (n - 2) convidados, e n - 2 sandwiches, n/2 - 1 de cada tipo.
Verifique que basta calcular a combinação (n - 2) C (n/2 - 1). Então procuramos pela
fórmula 1 - ( (n - 2) C (n/2 - 1) *   (1/2) ^ (n - 2) ). Agora a parte interessante:
n vai até 100000. Não dá pra calcular os fatoriais necessários para a combinação e
a exponenciação vai gerar um resultado muito pequeno. Para contornar isso, é suficiente
trabalhar com os logaritmos. log(n!) = somatorio( i = 1, i <= n ) log(i)[ obvio ne? ].
Então, a expressao de (n C k) fica: exp( log(n!) - log(n-k!) - log(k!) ). Aplicando
logaritmo à expressao toda, a parte (1/2) ^ (n - 2) se torna -(n - 2)*log(2).
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

