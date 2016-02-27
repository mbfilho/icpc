#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1100

int x[N];
int wa, ac;
int n, k;

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int t = 1; t <= casos; ++t ){
		scanf( "%d %d", &n, &k );
		wa = ac = 0;
		double sumwa = 0, sumac = 0;
		
		for( int i = 0; i < n; ++i ){
			scanf( "%d", x + i );
			if( x[i] < 0 ){
				wa++;
				sumwa += (-x[i]);
			}else{
				++ac;
				sumac += x[i];
			}
		}
		int passos = 75;
		if( ac ){
			if( !wa ){
				double esp = double(1.0 / n) * sumac;
				printf( "Case %d: %.3lf\n", t, esp + 1e-9 );
				continue;
			}
			
			double p = 1;
			double ramos = wa;
			double ap = 1;
			double esp = sumac * ( 1.0/ double(n) ); // com zero
			double soma = sumwa;			
			for( int i = 0; i <= passos; ++i ){
				if( ramos < 1 ) break;
				p = p * (1.0/double(n - min(i,k) ));
				
				esp += p * (1.0/(n - min(i+1,k))) * ( soma * ac + sumac * ramos );
				//PROB do caminho * soma dos tempos ( soma das portas erradas * branch certo + soma das portas certas ) 				
				
				ramos = ramos * (wa - min(i+1,k));
				ap = ramos/wa;
				soma = soma * (wa - min(i+1,k)) + sumwa * ap;
			}
			
			printf( "Case %d: %.3lf\n", t, esp + 1e-9 );
		}else
			printf( "Case %d: -1.000\n", t );
	}
}

