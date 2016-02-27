/*
Idéia: parece facil à primeira vista, mas tem um detalhe importante! O conjunto 
de pontos da entrada não é, necessariamente, o resultado do Graham Scann. Isso porque
o Graham elimina (3+) pontos colineares ( forma o convex hull com o menor numero
de pontos possivel ), mas esse problema pode conter na entrada (3+) pontos colineares!
Tendo em vista isso, basta fazer a ordenação polar como no graham scann. Mas, quando 3
pontos são colineares ( produto vetorial = 0 ) existe um caso especial de desempate.
É preciso verificar se o ponto sendo analisado está à direita ou à esquerda ( em termos
de coordenadas polares ) do vetor direcionado do ponto mais baixo para o ponto mais alto
do conjunto. Se ele estiver à direita ordene por X crescente, senão, por X decrescente.
( Atente para o fato de que um ponto é menor do que outro se ele é impresso antes ).
Após isso a impressao é trivial!!
OBS: Embora as coordenadas dos pontos caibam em 32bits, o calculo do produto vetorial
pode ( leia-se "vai!!" ) estourar. 

*/


#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAX 100001
#define quad( x ) (x)*(x)
class Ponto{
public:
	long long x, y;

}origem, alto, pontos[ MAX ];

int n;

//O menor é aquele que sera impresso antes!
bool operator<( const Ponto& a, const Ponto& b ){
// a x b

	long long produto = ( a.x - origem.x ) * ( b.y - origem.y )
			- ( a.y - origem.y )* ( b.x - origem.x );

	if( produto != 0 )
		return produto > 0;

	long long dista = quad( a.x - origem.x ) + quad( a.y - origem.y );
	long long distb = quad( b.x - origem.x ) + quad( b.y - origem.y );

	
	long long produto2 = ( alto.x - origem.x ) * ( a.y - origem.y )
			- ( alto.y - origem.y )* ( a.x - origem.x );
			
	//Pontos à direita do mais alto
	if( produto2 < 0 )
		return dista < distb;
	//Pontos à esquerda do mais alto ou com mesmo angulo
		return dista > distb;
}

void ler(){
	int cont = 0;
	char b;
	int x, y;
	for( int i = 0; i < n; ++i ){
		cin >> pontos[ cont ].x >> pontos[ cont ].y >> b;
	//	scanf( "%d %d %c", &pontos[ cont ].x, &pontos[ cont ].y, &b );
		if( b == 'Y' )
			++cont;
	}
	n = cont;
}


void responder(){
	int maiory = 0, menory = 0, menorx = 0;
	
	for( int i = 1; i < n; ++i ){
		if( pontos[ i ].y < pontos[ menory ].y )
			menory = i;
		else if( pontos[ i ].y == pontos[ menory ].y && pontos[ i ].x < pontos[ menory ].x )
			menory = i;
	}
	origem = pontos[ menory ];
	pontos[ menory ] = pontos[ 0 ];
	pontos[ 0 ] = origem;
	
	for( int i = 1; i < n; ++i ){
		if( pontos[ i ].y > pontos[ maiory ].y )
			maiory = i;
		else if( pontos[ i ].y == pontos[ maiory ].y && pontos[ i ].x > pontos[ maiory ].x )
			maiory = i;
	}
	alto = pontos[ maiory ];
	
	sort( pontos + 1, pontos + n );
	for( int i = 1; i < n; ++i ){
		if( pontos[ i ].x < pontos[ menorx ].x )
			menorx = i;
		else if( pontos[ i ].x == pontos[ menorx ].x && pontos[ i ].y < pontos[ menorx ].y )
			menorx = i;
	}
	
	printf( "%d\n", n );
	for( int i = 0; i < n; ++i ){
		cout << pontos[ menorx ].x << " " << pontos[ menorx ].y << endl;
	//	printf( "%ld %ld\n", pontos[ menorx ].x, pontos[ menorx ].y );
		menorx = ( menorx + 1 ) % n;
	}

}

int main(){
	int casos;
	freopen( "in.txt", "r", stdin );
	scanf( "%d", &casos );

	while( casos-- ){
		scanf( "%d", &n );
		ler();
		responder();
	}

}


