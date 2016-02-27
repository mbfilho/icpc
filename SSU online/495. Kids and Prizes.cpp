#include <cstdio>
#include <cmath>

using namespace std;

int main(){
	freopen("in.txt","r",stdin);
	
	int n, m;
	scanf( "%d%d", &n, &m );
	double resposta = double( n - 1 ) / n;
	resposta = ( 1 - pow( resposta, m ) ) * n;
	printf( "%.9lf\n", resposta );
	
}
