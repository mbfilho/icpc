#include <cstdio>
#include <cstring>
#define MAX 1100

/*
To com preguiça de explicar, então olha a explicação do Algorithmist:
If S has less than two letters, it is trivially a palindrome. Otherwise,
 examine the first and the last letter of S. If they are equal, we may 
 ignore them from now on, we only have to change the rest of S into a 
 palindrome. If they are not equal, sooner or later we will have to fix this. 
 As the changes are independent, we may do it now. 

What options do we have? 
* Remove one of these letters. 
* Change one of these letters to match the other one. 

(Note that adding new letters is never necessary. Instead of adding new 
letters to match existing ones we may simply delete those existing letters that 
didn't have a match. The remaining two operations are necessary, consider the 
strings abcddcb and abcddcbe.) 

After each of these changes, we are left with a shorter string and the same 
task – change it into a palindrome. Moreover, we may note that the shorter 
string is always some (continuous) substring of S. Now all we have to do is to 
find an optimal solution for each of these shorter strings, and pick the best of 
these solutions. 

This brings us to the idea of the solution. Let B(i,j) be the best solution for the 
substring . From the observations above we get:
	B( i, j ) =
	1) 0, se i >= j ( ou seja, se a string tem tamanho menor que 2 )
	2) B( i + 1, j - 1 ), se S[ i ] == S[ j ]
	3) 1 + min( B( i + 1, j - 1 ), B( 1 + i, j ), B( i, j - 1 ) )
	The values B(i,j) can be either computed using a recursive function with
	memoization, or we may compute them "bottom-up", starting with shortest substrings.
*/

char nome[ MAX ];
int memo[ MAX ][ MAX ];

int minimo( int a, int b, int c ){
	int menor = a;
	if( b < menor )
		menor = b;
	if( c < menor )
		menor = c;
		
	return menor;
}

int best( int i, int j ){
	if( i >= j )
		return memo[ i ][ j ] = 0;
	
	if( memo[ i ][ j ] != -1 )
		return memo[ i ][ j ];
	
	if( nome[ i ] == nome[ j ] )
		return memo[ i ][ j ] = best( i + 1, j - 1 );
	
	int substituir = best( i + 1, j - 1 );
	int remover1 = best( i + 1, j );
	int remover2 = best( i, j - 1 );
	memo[ i ][ j ] = 1 + minimo( remover1, remover2, substituir );
	return memo[ i ][ j ];
	
}

int main(){
	int casos, tam;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%s", nome );
		tam = strlen( nome );
		
		for( int i = 0; i < tam; ++i ){
			for( int j = 0; j < tam; ++j )
				memo[ i ][ j ] = -1;
		}
		
		printf( "Case %d: %d\n", c, best( 0, tam - 1 ) );
	}
}
