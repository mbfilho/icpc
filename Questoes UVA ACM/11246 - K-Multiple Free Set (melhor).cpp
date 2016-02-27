#include <cstdio>

int main(){
	int casos, n, k, soma, temp, aux;
	bool subtrai;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &k );
		soma = n;
		subtrai = true;
		
		aux = k;
		while( ( temp = n / aux ) ){
			if( subtrai )
				soma -= temp;
			else
				soma += temp;
			aux *= k;
			subtrai = !subtrai;	
		}
		
		printf( "%d\n", soma );
		
	}
}
