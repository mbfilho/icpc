#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 70100

int ma[N];
int n, m;


int pos( int i, int j ){
	return (i-1) * m  + j;
}
int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int t = 1; t <= casos; ++t ){
		scanf( "%d %d", &n, &m );
		
		
		ma[pos(n,m)] = 0;
		
		for( int j = m - 1; j > 0; --j ){
			ma[pos(n,j)] = 1 - ma[pos(n,j+1)];
		}
		
		for( int i = n - 1; i > 0; --i ){
			ma[pos(i,m)] = 1 - ma[pos(i+1,m)];
		}
		
		for( int i = n - 1; i > 0; --i ){
			for( int j = m - 1; j > 0; --j ){
				int marc[] = {0,0,0};
				++marc[ ma[pos(i+1,j)] ];
				++marc[ ma[pos(i,j+1)] ];
				if( !marc[0] ) ma[pos(i,j)] = 0;
				else if( !marc[1] ) ma[pos(i,j)] = 1;
				else ma[pos(i,j)] = 2;
			}
		}
//		for( int i = 1; i <=n; ++i ){
//			for( int j = 1; j <= m; ++j ){
//				printf( "%d ", ma[pos(i,j)] );
//			}
//			printf( "\n" );
//		}
		int nim = 0;
		
		for( int i = 1; i <= n; ++i ){
			for( int j = 1; j <= m; ++j ){
				int x;
				scanf( "%d", &x );
//				printf( ">>> %d\n",x );
//				printf( ">> %d %d\n",x ,ma[pos(i,j)]);
				if( ma[pos(i,j)] ) nim ^= x;
				
			}
		}
		
		if(nim) printf( "Case %d: win\n", t );
		else printf( "Case %d: lose\n", t );
	}
}




