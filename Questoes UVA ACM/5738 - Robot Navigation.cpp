#include<cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 1200
#define oo 1000000000

int n, m, mod;
int cont[N][N][5], dist[N][N][5];
char ma[N][N];

//N L S O
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

struct No{
	int x, y, d;
	No( int xx, int yy, int dd ){
		x = xx;
		y = yy;
		d = dd;
	}
};

int faz( int xx, int yy, int dd, int xf, int yf ){
	queue<No> fila;
	
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < m; ++j ){
			for( int k = 0; k < 4; ++k ){
				dist[i][j][k] = oo;
				cont[i][j][k] = 0;
			}
		}
	}
	
	dist[xx][yy][dd] = 0;
	cont[xx][yy][dd] = 1;
	fila.push( No( xx, yy, dd ) );
	while( !fila.empty() ){
		int x = fila.front().x, y = fila.front().y, d = fila.front().d;
		fila.pop();
		int c = dist[x][y][d];
		
		int nx = x + dx[d], ny = y + dy[d];
		if( nx >= 0 && nx < n && ny >= 0 && ny < m && ma[nx][ny] == '.' ){
			if( c + 1 == dist[nx][ny][d] ){
				cont[nx][ny][d] = ( cont[nx][ny][d] + cont[x][y][d] ) % mod;
			}else if( dist[nx][ny][d] == oo ){
				dist[nx][ny][d] = c + 1;
				cont[nx][ny][d] = cont[x][y][d];
				fila.push( No(nx,ny,d) );
			}
		}
		
		int dir[] = { (d + 1) % 4, (d + 3) % 4 };
	
		for( int k = 0; k < 2; ++k ){
			int nd = dir[k];
		
			if( c + 1 == dist[x][y][nd] ){
				cont[x][y][nd] = ( cont[x][y][nd] + cont[x][y][d] ) % mod;
			}else if( dist[x][y][nd] == oo ){
				dist[x][y][nd] = c + 1;
				cont[x][y][nd] = cont[x][y][d];
				fila.push( No(x,y,nd) );
			}
		}
	}
	
	int menor = oo, soma = 0;
	for( int k = 0; k < 4; ++k )
		menor = min( menor, dist[xf][yf][k] );

	if( menor == oo ) return -1;
		
	for( int k = 0; k < 4; ++k ){
		if( dist[xf][yf][k] == menor )
			soma = ( soma + cont[xf][yf][k] ) % mod;
	}
	
	return soma;
}

int main(){
	int caso = 0;
	while( scanf( "%d%d%d", &n, &m, &mod ) != EOF && (mod) ){
		for( int i = 0; i < n; ++i )
			scanf( "%s", ma[i] );
		int x, y, xf, yf, dir;
		char buf[10];
		scanf( "%d%d%d%d%s", &x, &y, &xf, &yf, buf );
		
		if( buf[0] == 'N' ) dir = 0;
		else if( buf[0] == 'E' ) dir = 1;
		else if( buf[0] == 'S' ) dir = 2;
		else if( buf[0] == 'W' ) dir = 3;
		else throw 1;
		
		printf( "Case %d: %d %d\n", ++caso, mod, faz( x, y, dir, xf, yf ) );
	}
}



