#include <cstdio>
#include <cstring>
#define MAX 1010

/*
*	A idéia é encontrar os caracteres comuns entre a string original e a string 
*invertida. Esses caracteres em comum serão inseridos na string original para formar
*o palindromo. Como queremos o menor palindromo, temos de achar a maior sequencia em 
*comum: lcs!. O algoritmo tem de, além de calcular o tamanho da maior sequencia,
*guarda informação que possibilite reconstruí-la. Para isso existe a classe "No". 
*Fazer isso é bem simples, veja o método lcs() para entender melhor.
*Feito isso, vamos construir o palindromo. O primeiro while do metodo responder
*"reconstroi" a lcs, guardando num array de "Paradas" os caracteres emparelhados.
*(os indices dos caracteres emparelhados no sequencia original e sequencia invertida).
*Feito isso, basta imprimir. Percorra cada uma das "Paradas". Imprima todos os
*caracteres da string original até o caracter em comum ( salvo no array matchs ).
*Depois faço o mesmo com a string invertida. Depois imprima o caracter em comum. 
*Pronto, é só isso! Teoricamente, pode-se começar a imprimir os caracteres da string
*invertida, depois os caracteres da string original e depois o caracter em comum.
*Isso porque o problema diz que qualquer palindromo serve.
*/

char s1[ MAX ];
char invert[ MAX ];
char impressao[ 2 * MAX ];
int tam;

class Paradas{
public:
	int ori, invert;
}matchs[ 2 * MAX ];

class No{
public:
	int qtd, i, j;
}pd[ MAX ][ MAX ];

void lcs(){
	for( int i = 1; i <= tam; ++i ){
		for( int j = 1; j <= tam; ++j ){
			if( s1[ i - 1 ] == invert[ j - 1 ] ){
				pd[ i ][ j ].qtd = pd[ i - 1 ][ j - 1 ].qtd + 1;
				pd[ i ][ j ].i = i - 1;
				pd[ i ][ j ].j = j - 1;
			}else{
				if( pd[ i - 1 ][ j ].qtd > pd[ i ][ j - 1 ].qtd ){
					pd[ i ][ j ].qtd = pd[ i - 1 ][ j ].qtd;
					pd[ i ][ j ].i = i - 1;
					pd[ i ][ j ].j = j;
				}else{
					pd[ i ][ j ].qtd = pd[ i ][ j - 1 ].qtd;
					pd[ i ][ j ].i = i;
					pd[ i ][ j ].j = j - 1;
				}
			}
		}
	}
}


void responder(){
	tam = strlen( s1 );
	for( int i = 0; i < tam; ++i )
		invert[ i ] = s1[ tam - 1 - i ];

	lcs();
	
	int maior = tam - pd[ tam ][ tam ].qtd;
	int i = tam, j = tam;
	int cont = 0;
	int aux;
	
	/*
		Essa verificação não é necessária, mas evita trabalho desnecessário
	*/
	if( maior == 0 ){
		printf( "%d %s\n", 0, s1 );
		return;
	}
	
	while( i != 0 && j != 0 ){
		if( s1[ i - 1 ] == invert[ j - 1 ] ){
			matchs[ cont ].invert = j - 1;
			matchs[ cont ].ori = i - 1;
			++cont;
		}
		
		aux = i;
		i = pd[ aux ][ j ].i;
		j = pd[ aux ][ j ].j;
	}

	i = j = aux = 0;
	for( cont = cont - 1; cont >= 0; --cont ){
		for( ; i < matchs[ cont ].ori; ++i )
			impressao[ aux++ ] = s1[ i ];
		for( ; j < matchs[ cont ].invert; ++j )
			impressao[ aux++ ] = invert[ j ];
			
		impressao[ aux++ ] = s1[ matchs[ cont ].ori ];
		i = matchs[ cont ].ori + 1;
		j = matchs[ cont ].invert + 1;
	}
	for( ; i < tam; ++i )
		impressao[ aux++ ] = s1[ i ];
	for( ; j < tam; ++j )
		impressao[ aux++ ] = invert[ j ];
		
	impressao[ aux ] = '\0';
	printf( "%d %s\n", maior, impressao );
}

int main(){
	for( int i = 0; i < MAX; ++i ){
		pd[ i ][ 0 ].qtd = 0;
		pd[ 0 ][ i ].qtd = 0;
	}
	
	while( scanf( "%s", s1 ) != EOF )
		responder();
}
