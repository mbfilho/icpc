#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;

ll pascal[70][70];
int base[70];

void pre(){
	base[1] = 0;
	for( int i = 2; i < 70; ++i ){
		int cnt = 0, tmp = i;
		while( tmp ){
			++cnt;
			tmp -= tmp & -tmp;
		}
		base[i] = 1 + base[cnt];
	}
	
	memset( pascal, 0, sizeof pascal );
	pascal[0][0] = 1;
	for( int i = 1; i < 70; ++i ){
		pascal[i][0] = pascal[i][i] = 1;
		for( int j = 1; j < i; ++j )
			pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
	}	
}


ll contar( ll hight, int cnt ){
	ll ret = 0, tmp = hight;
	int bits = 0;
	while( tmp ){
		++bits;
		tmp -= tmp & -tmp;
	}
	
	
	for( ll i = 0, j = 1; i < 63; ++i, j *= 2 ){
		if( hight & j ){
			--bits;
			if(cnt >= bits)
				ret += pascal[i][cnt-bits];
		}
	}
	
	return ret;
}

int main(){
	pre();
	ll lo, hi;
	int x;
	
	while( scanf( "%lld %lld %d", &lo, &hi, &x ) != EOF && ( hi | lo | x ) ){
		if( !x ){
			if( 1 >= lo && 1 <= hi ) printf( "1\n" );
			else printf( "0\n" );
		}else{
			ll resp = 0;
			for( int i = 1; i < 64; ++i ){
				if( base[i] == x - 1 ){
					resp += contar( hi + 1, i ) - contar( lo, i );
				}
			}
			if( x == 1 && ( 1 >= lo && 1 <= hi ) ) --resp;
			printf( "%lld\n", resp );
		}
	}
	
}





