#include <cstdio>
#include <iostream>
using namespace std;

/*
Se k | x, entao floor(x/k) == ceil(x/k), logo, basta p + q = k.
Senao, floor(x/k) + 1 = ceil(x/k). Chame h' = floor(x/k). Nesse caso:
	ph' + q + qh' = x
	p + q = ( x - q ) / h'
	q = ( x - q ) / h'   - q
	
	Onde basta que 'q' seja um numero que torne x divisivel por h'. O menor é bom =D
	OBS: há o caso especial em que floor(x/k) = 0, ou seja k > x. Nesse caso, 
	ceil() = 1 e q = x. p pode ser qualquer numero.
*/
int main(){
	int x, k, p, q, casos;
	
	scanf( "%d", &casos );
	while( casos-- ){
		scanf( "%d %d", &x, &k );
		
		if( x % k == 0 )
			printf( "0 %d\n", k );
		else{
			int chao = x / k;
			if( chao != 0 ){
				q = x % chao;
				p = (x - q) / chao - q;
			}else{
				p = 0;
				q = x;
			}
			
			printf( "%d %d\n", p, q );
		}
	}
}
