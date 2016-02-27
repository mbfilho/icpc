#include <algorithm>
#include <vector>
#include <cstdio>
#define maior( a, b ) (a) > (b) ? (a) : (b)
using namespace std;

int seq[2010], pai[2010];

class Elefante{
public:
	int peso, qi, id;
	
	bool operator<( const Elefante& e ) const{
		if( e.peso == peso )
			return qi < e.qi;
		return peso < e.peso;
	}
}ele[2000];

int cont, len;

int busca( int ind ){
	int retorno = 0;
	int i = 1, j = len, elemento;
	
	while( i <= j ){
		elemento = (i + j) / 2;
		if( ele[seq[elemento]].qi < ele[ind].qi ){
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
		
	for( int i = cont - 1; i >= 0; --i ){
		result = busca( i );
		
		pai[i] = seq[result];
		if( result == len || ele[ i ].qi < ele[ seq[ result + 1 ] ].qi ){
			seq[result + 1] = i;
			len = maior( result + 1, len );
		}
	}
	
	return len;
}

int main(){
	cont = 0;
	
	while( scanf( "%d %d", &ele[cont].peso, &ele[cont].qi ) != EOF ){	
		//ele[cont].id = ++cont;
		ele[cont].id = cont + 1;
		++cont;
	}
	
	if( cont == 0 ){
		printf( "0\n" );
		return 0;
	}
		
	sort( ele, ele + cont );
	
	printf( "%d\n", lcs() );
	
	vector<int> impressao;
	int p = seq[len];
	
	while( p != -1 ){
		impressao.push_back( ele[p].id );
		p = pai[p];
	}
	for( int it = 0; it < impressao.size(); ++it )
		printf( "%d\n", impressao[it] );
	
	return 0;
}
	
