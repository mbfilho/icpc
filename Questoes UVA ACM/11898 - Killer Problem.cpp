#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define mp make_pair
#define Q 10001
#define N 200100
struct No{
	int first, second, id;
	
	bool operator<( const No& a ) const{
		if( second != a.second )		
			return second < a.second;
		
		return first < a.first;
	}
};

No que[ Q ];
int resp[ Q ];
int marc[ 10001 ], marc2[ 10001 ];
int num[ N ], n, q;

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		for( int i = 1; i <= n; ++i )
			scanf( "%d", num + i );
		memset( marc, 0, sizeof( marc ) );
		memset( marc, 0, sizeof( marc2 ) );
		
		scanf( "%d", &q );
		
		for( int i = 0; i < q; ++i ){
			scanf( "%d %d", &que[ i ].first, &que[ i ].second );
			que[ i ].id = i;
		}
		sort( que, que + q );
		
		int last = 1;
		for( int i = 0; i < q; ++i ){
		//	printf( "(%d,%d)\n", que[i].first, que[i].second );
			if( que[ i ].second - que[ i ].first > 10000 ){
				resp[ que[i].id ] = 0;
				continue;
			}
			
			for( last = max( last, que[i].first ); last <= que[ i ].second; ++last ){
				marc2[ num[last] ] = marc[ num[last] ];
				marc[ num[last] ] = last;
			}

			int ult = -1, menor = 2000000;
			for( int j = 1; j <= 10000; ++j ){
				if( marc[ j ] >= que[ i ].first && marc[ j ] <= que[ i ].second ){
					ult = j;
					if( marc2[ j ] >= que[ i ].first && marc2[ j ] <= que[ i ].second )
						menor = 0;
					break;
				}
			}
			
			for( int j = ult + 1; j <= 10000; ++j ){
				if( marc[ j ] >= que[ i ].first && marc[ j ] <= que[ i ].second ){
					if( j - ult < menor )
						menor = j - ult;
					if( marc2[ j ] >= que[ i ].first && marc2[ j ] <= que[ i ].second )
						menor = 0;
					ult = j;
				}
			}
			
			resp[ que[i].id ] = menor;
		}
		
		for( int i = 0; i < q; ++i )
			printf( "%d\n", resp[ i ] );
			
	}
}




