#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50
char ma[N][N];
int resp[N][N];
int n, m;

int main(){
	while(scanf( "%d %d", &n, &m ) != EOF){
		memset(resp, 0, sizeof resp);
		for(int i = 0; i < n; ++i) scanf( "%s", ma[i] );
		int cnt = 1;
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(ma[i][j] == '.'){
					resp[i+1][j+1] = cnt++;
				}
			}
		}
		
		if(cnt != 1){
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= m; ++j){
					if(resp[i][j]){
						printf( "%d %d %d %d %d\n", resp[i][j], resp[i-1][j], resp[i][j+1], resp[i+1][j], resp[i][j-1]);
					}
				}
			}
		}
		printf( "\n" );
	}
}

