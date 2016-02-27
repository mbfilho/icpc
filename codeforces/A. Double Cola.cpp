#include <cstdio>
typedef long long ll;



int main(){
	ll ini = 1, fim = 5, qtd = 5;
	int n;
	scanf( "%d", &n );
	
	while( n > fim ){
		qtd = qtd * 2LL;
		ini = fim + 1;
		fim = ini + qtd - 1;
	}
	
	int divi = qtd / 5;
	int cara = ( n - ini ) / divi;
	const char *caras[] = { "Sheldon", "Leonard", "Penny", "Rajesh", "Howard" };
	printf( "%s\n", caras[ cara ] ); 
}



