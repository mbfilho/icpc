/*
*Comece a construir a resposta a partir do bit mais significativo.
*Construir de maneira 'ótima' significa colocar bit 1 somente nas posições
*onde N possuir bit 0, desde que essa operação não faça a resposta passar o upper bound.
*É seguro ( respeita os limites ) fazer isso desde o bit
*da resposta correspondente ao bit mais sgnificativo do upper bound até o MSB do
*lower bound. Se algum bit for setado nesse intervalo, a resposta com certeza será
*maior que o lower bound. Além disso, cada vez que se seta um bit, deve ser verificado
*se a resposta está menor que o upper. Daí, tem-se duas situações. Você setou um bit
*no intervalo descrito ou não. Se você setou, continue construindo de maneira ótima
*o restante da resposta, ou seja, seta um bit sse o bit correspondente em N for 0 e
*setar o bit não faz a resposta ultrapassar o upper ( como descrito acima =P ). Mas se
*você não setou, perigo: a resposta pode ficar menor que o lower. Para tratar isso, você
*pode comerçar a setar bits mesmo que o o bit correspondente em N seja 1. Proceda assim:
*Se o bit correspondente em N for 0 e setar o bit na resposta não ultrapassa upper, sete
*o bit e pronto ( construção ótima!! ) SENÃO você vai setar o bit somente se não setar o
*bit significa fazer a resposta ficar obrigatoriamente menor que o lower. Para
verificar isso, basta observar se, mesmo setando todos os bits posteriores da resposta
vai gerar um número menor que o lower. 
*/


#include <cstdio>
#include <iostream>
#define maior( a, b ) (a) > (b) ? (a) : (b)
using namespace std;

typedef unsigned int ui;

ui n, l, u;

ui pot[ 32 ];

int tam( ui a ){
	for( int i = 31; i >= 0; --i ){
		if( a & pot[ i ] )
			return ( i + 1 );
	}
	
	return 0;
}

ui responder(){
	ui retorno = 0;
	int sizeU = tam( u ), sizeL = tam( l );
	
	//Comeca de maneira ótima, no intervalo 'seguro'
	for( int i = sizeU - 1; i >= sizeL; --i ){
		if( ( pot[ i ] & n ) == 0 ){
			if( ( retorno | pot[ i ] ) <= u )
				retorno |= pot[ i ];
		}
	}
	
	//Verifica se eu setei um bit no intervalo seguro
	if( retorno < l ){
		//Não setei, por isso devo parar de construir de maneira ótima.
		for( int i = sizeL - 1; i >= 0; --i ){
			//Seto o bit se isso é construir de maneira ótima
			if( (n & pot[ i ]) == 0 && ( retorno | pot[ i ] ) <= u )
				retorno = retorno | pot[ i ];
			//Ou se eu tenho de setar!
			/*Vc pode se perguntar pq o else if não checa o upper. Veja bem, se
			setar esse bit significa estourar o upper então não setar esse bit e setar
			todos os outros, no mínimo, faz a resposta ficar igual ao upper. Nesse caso,
			com certeza eu posso fazer a resposta ficar >= lower com os bits restantes.
			*/
			else if( (retorno | (pot[i] - 1)) < l  )
				retorno = retorno | pot[ i ];
		} 
	}else{
	//Setei um bit no intervalo seguro. Assim, posso continuar construindo otimamente.
		for( int i = sizeL - 1; i >= 0; --i ){
			if( ( n & pot[ i ]) == 0 ){
				if( ( retorno | pot[ i ]) <= u )
					retorno = retorno | pot[ i ];
			}
		}
	}
	 
	return retorno;
}

int main(){
	pot[ 0 ] = 1;
	for( int i = 1; i < 32; ++i )
		pot[ i ] = ( pot[ i - 1 ] << 1 );
	
	while( scanf( "%u %u %u", &n, &l, &u ) != EOF ){
	//Não é necessário tratar esse caso especial, mas poupa trabalho desnecessario
		if( l == u )
			printf( "%u\n", l );
		else
			printf( "%u\n", responder() );
	}
}
