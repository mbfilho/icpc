#include <cstdio>
#include <vector>
using namespace std;

int ele[500000];
int seq[500000],pai[500000];
int len, cont;

int maior( int a, int b ){
	if( a > b )
		return a;
	return b;
}

int busca( int ind ){
	int retorno = 0;
	int i = 1, j = len, elemento;
	
	while( i <= j ){
	//	elemento = (i + j) / 2;
		elemento = i + ( j - i ) / 2;
		if( ele[seq[elemento]] < ele[ind] ){
			retorno = elemento;
			i = elemento + 1;
		}else
			j = elemento - 1;	
	}
	
	return retorno;
}

int lcs(){
	len = 0;
	seq[0] = -1;
	int result;
		
	for( int i = 0; i < cont; ++i ){
		result = busca( i );
		
		pai[i] = seq[result];
		if( result == len || ele[ i ] < ele[ seq[ result + 1 ] ] ){
			seq[result + 1] = i;
			len = maior( result + 1, len );
		}
	}
	
	return len;
}

int main(){
	cont = 0;
	
	while( scanf( "%d", &ele[cont] ) != EOF )
		++cont;
	
	printf( "%d\n-\n", lcs() );
	
	vector<int> impressao;
	int p = seq[len];
	
	while( p != -1 ){
		impressao.push_back( ele[p] );
		p = pai[p];
	}
	for( int it = impressao.size() - 1; it >= 0; --it )
		printf( "%d\n", impressao[it] );
}
