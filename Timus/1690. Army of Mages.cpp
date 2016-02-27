/*
Army of Mages

O problema d� um conjunto de 5*n pontos e pede que vc escolha n pontos tais que,
o segmento tendo quaisquer 2 pontos desse conjunto como extremidades contenha pelo menos
um ponto de coordenadas inteiras ( ou seja, todos eles se "respeitam" ).
Todos os pontos dados possuem coordenadas inteiras e n�o existem pontos iguais.

O n�mero de pontos de coordenadas inteiras em um segmento AB, com A = (x1, y1)
e B = (x2,y2) � dado por gcd( x1 - x2, y1 - y2 ) + 1. Como temos que excluir as extremidades
fica: gcd( x1 - x2, y1 - y2 ) - 1. Para que haja pelo menos um desses pontos em AB, 
gcd() tem de ser pelo menos 2. Se a e b s�o pares, ent�o gcd( a, b ) >= 2. Para que a
diferen�a de dois numeros seja par, eles devem ter a mesma paridade. Com essa ideia, pode-se
dividir os pontos em 4 conjuntos:
(x Par, y Par)
(x Impar, y Impar)
(x Par, y Impar)
(x Impar, y Par)

De forma que quaisquer 2 pontos de um mesmo conjunto se "respeitam".

Temos 5*n pontos particionados em 4 conjuntos. Pelo principio da casa dos pombos,
certamente 1 dessas parti��es ter� pelo menos n pontos. 
Da�, a id�ia � ir inserindo os pontos no conjunto apropriado. No final, pegar um conjunto
que possua pelo menos n elementos para imprim�-los. Qualquer conjunto vale e qualquer 
ordem de impressao tb. 
*/

#include <cstdio>

int n;
int tdpar[ 25100 ], tdimpar[ 25100 ], xpar[ 25100 ], ximpar[ 25100 ];
int contP, contI, contXP, contXI;

void print( int ar[] ){
	printf( "OK\n%d", ar[ 0 ] );
	
	for( int i = 1; i < n; ++i )
		printf( " %d", ar[ i ] );
	printf( "\n" );
}

int main(){
	int x, y;
	contP = contXP = contXI = contI = 0;
	
	scanf( "%d", &n );
	for( int i = 1; i <= 5 * n; ++i ){
		scanf( "%d %d", &x, &y );
		
		if( (x & 1) && (y & 1) )
			tdimpar[ contI++ ] = i;
		else if( ((x & 1) == 0) && ((y & 1) == 0) )
			tdpar[ contP++ ] = i;
		else if( (x & 1) )
			xpar[ contXP++ ] = i;
		else
			ximpar[ contXI++ ] = i;
		
		if( contI >= n || contP >= n || contXP >= n || contXI >= n )
			break;
	}
	
	if( contP >= n )
		print( tdpar );
	else if( contXP >= n )
		print( xpar );
	else if( contXI >= n )
		print( ximpar );
	else
		print( tdimpar );
}
