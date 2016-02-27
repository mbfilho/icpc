#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define oo 2000000000
#define EPS 1e-7
int a, n;
double b;

double avalia(int v, double E){
	double p = 1/( 1 + pow(v - a, b));
	
	return p * ( v  - E );
}

int main(){
	int caso = 0;
	while( scanf("%d", &n) != EOF && n ){
		++caso;
		scanf( "%d%lf", &a, &b );
		
		double E = a;
		for( int i = 1; i < n; ++i ){
			int ini = a + 1, fim = oo, best;

			bool sair = false;
			while(!sair){
				if( fim - ini < 2 ) sair = true;
				int t = (fim - ini + 1) / 3;
				
				int first = ini + t, second = fim - t;
//				printf( "(%d,%d) F: %d[%.10lf] S %d[%.10lf] {%d} \n", ini, fim, first, avalia(first,E), second, avalia(second,E), avalia(first,E) >= avalia(second,E)); 
				if(avalia(first,E) >= avalia(second,E) || first == second){
					fim = second;
					best = first;
				}else{
					ini = first;
					best = second;
				}
			}
//			printf( "[%d,%lf]\n", best, avalia(best,E));
			E = avalia(best,E) + E;
		}
		
		printf( "Case %d: %.2lf\n", caso, E );
	}
}




