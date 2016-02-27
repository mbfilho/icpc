#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pd[20][200];

void pre(){
	memset( pd, 0, sizeof pd );
	for( int i = 0; i < 10; ++i ) pd[1][i] = 1;
	
	for( int tam = 2; tam < 20; ++tam ){
		for( int sum = 0; sum < 200; ++sum ){
			for( int i = 0; i < 10; ++i ){
				pd[tam][sum] += pd[tam-1][sum-i];
			}
		}
	}
}

ll soma( char *num, int prt, int tam, int sum ){
	if( !num[prt] ) return 0;
	if( tam == 1 ){
		if( num[prt] - '0' >= sum )
			return pd[1][sum];
		return 0;
	}
	ll res = 0;
	
	for( int i = 0; i < num[prt] - '0'; ++i ){
		if( sum < i ) break;
		res += pd[tam-1][sum-i];
	}
	
	res += soma( num, prt + 1, tam - 1, sum - num[prt] + '0' );
	return res;
}

char num[100];

int main(){
	pre();
	
	ll a, b, x;
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%lld %lld %lld", &a, &b, &x );
		
		ll qtd = 0;
		int sum = 1;
		
		while(x && sum < 200){
			sprintf( num, "%lld", b );
			ll tmp = soma( num, 0, strlen(num), sum );
			sprintf( num, "%lld", a - 1 );
			tmp -= soma( num, 0, strlen(num), sum );
			if( tmp * sum <= x ){
				x -= tmp * sum;
				qtd += tmp;
			}else{
				qtd += x / sum;
				x = 0;
			}
			
			++sum;
		}
		
		printf( "%lld\n", qtd );
		
		
	}
	
	
}





