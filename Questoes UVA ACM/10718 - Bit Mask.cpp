/*
*Comece a construir a resposta a partir do bit mais significativo.
*Construir de maneira '�tima' significa colocar bit 1 somente nas posi��es
*onde N possuir bit 0, desde que essa opera��o n�o fa�a a resposta passar o upper bound.
*� seguro ( respeita os limites ) fazer isso desde o bit
*da resposta correspondente ao bit mais sgnificativo do upper bound at� o MSB do
*lower bound. Se algum bit for setado nesse intervalo, a resposta com certeza ser�
*maior que o lower bound. Al�m disso, cada vez que se seta um bit, deve ser verificado
*se a resposta est� menor que o upper. Da�, tem-se duas situa��es. Voc� setou um bit
*no intervalo descrito ou n�o. Se voc� setou, continue construindo de maneira �tima
*o restante da resposta, ou seja, seta um bit sse o bit correspondente em N for 0 e
*setar o bit n�o faz a resposta ultrapassar o upper ( como descrito acima =P ). Mas se
*voc� n�o setou, perigo: a resposta pode ficar menor que o lower. Para tratar isso, voc�
*pode comer�ar a setar bits mesmo que o o bit correspondente em N seja 1. Proceda assim:
*Se o bit correspondente em N for 0 e setar o bit na resposta n�o ultrapassa upper, sete
*o bit e pronto ( constru��o �tima!! ) SEN�O voc� vai setar o bit somente se n�o setar o
*bit significa fazer a resposta ficar obrigatoriamente menor que o lower. Para
verificar isso, basta observar se, mesmo setando todos os bits posteriores da resposta
vai gerar um n�mero menor que o lower. 
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
	
	//Comeca de maneira �tima, no intervalo 'seguro'
	for( int i = sizeU - 1; i >= sizeL; --i ){
		if( ( pot[ i ] & n ) == 0 ){
			if( ( retorno | pot[ i ] ) <= u )
				retorno |= pot[ i ];
		}
	}
	
	//Verifica se eu setei um bit no intervalo seguro
	if( retorno < l ){
		//N�o setei, por isso devo parar de construir de maneira �tima.
		for( int i = sizeL - 1; i >= 0; --i ){
			//Seto o bit se isso � construir de maneira �tima
			if( (n & pot[ i ]) == 0 && ( retorno | pot[ i ] ) <= u )
				retorno = retorno | pot[ i ];
			//Ou se eu tenho de setar!
			/*Vc pode se perguntar pq o else if n�o checa o upper. Veja bem, se
			setar esse bit significa estourar o upper ent�o n�o setar esse bit e setar
			todos os outros, no m�nimo, faz a resposta ficar igual ao upper. Nesse caso,
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
	//N�o � necess�rio tratar esse caso especial, mas poupa trabalho desnecessario
		if( l == u )
			printf( "%u\n", l );
		else
			printf( "%u\n", responder() );
	}
}
