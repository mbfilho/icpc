#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 25

char ma[ N ][ N ];
int marc[ N ][ N ][ N ][ N ];
int n, m;

struct No{
	int ci, cj;//cara
	int bi, bj;//box
	
	No(){}
	
	No( int cci, int ccj, int bbi, int bbj ){
		ci = cci;
		bi = bbi;
		cj = ccj;
		bj = bbj;
	}
};

bool caraPode( int ci, int cj, int bi, int bj ){
	if( ci >= 0 && ci < n && cj >= 0 && cj < m ){
		if( ma[ ci ][ cj ] == '#' ) return false;
		if( ma[ ci ][ cj ] == 'd' ){
			if( ma[ bi ][ bj ] == 'b' ) return true;
			return false;
		}
		return true;
	}
	
	return false;
}

bool boxPode( int bi, int bj ){
	if( bi >= 0 && bi < n && bj >= 0 && bj < m ){
		if( ma[ bi ][ bj ] == '#' || ma[ bi ][ bj ] == 'd' )
			return false;
		return true; 
	}
	return false;
}

void bfs( No inicio ){
	memset( marc, -1, sizeof( marc ) );
	marc[ inicio.ci ][ inicio.cj ][ inicio.bi ][ inicio.bj ] = 0;
	queue<No> fila;
	fila.push( inicio );
	
	No temp;
	int ci, cj, bi, bj, dist;
	while( fila.empty() == false ){
		temp = fila.front();
		fila.pop();
		ci = temp.ci;
		cj = temp.cj;
		bi = temp.bi;
		bj = temp.bj;
		dist = marc[ ci ][ cj ][ bi ][ bj ];

		//Cima
		if( caraPode( ci - 1, cj, bi, bj ) ){
			//andar sem a caixa
			if( ci - 1 != bi || cj != bj ){
				if( marc[ci - 1][cj][bi][bj] == -1  ){
					fila.push( No( ci - 1, cj, bi, bj ) );
					marc[ci - 1][cj][bi][bj] = dist + 1;
				}
			}else{
				//com a caixa
				if( boxPode( bi - 1, bj ) && marc[ci-1][cj][bi-1][bj] == -1 ){
					fila.push( No( ci - 1, cj, bi - 1, bj ) );
					marc[ci - 1][cj][bi - 1][bj] = dist + 1;
				}
			}
			
		}
		
		//Baixo
		if( caraPode( ci + 1, cj, bi, bj ) ){
			//andar sem a caixa
			if( ci + 1 != bi || cj != bj ){
				if( marc[ci + 1][cj][bi][bj] == -1 ){
					fila.push( No( ci + 1, cj, bi, bj ) );
					marc[ci + 1][cj][bi][bj] = dist + 1;
				}
			}else{
				//com a caixa
				if( boxPode( bi + 1, bj ) && marc[ci + 1][cj][bi+1][bj] == -1 ){
					fila.push( No(ci+1,cj,bi+1,bj ) );
					marc[ci+1][cj][bi+1][bj] = dist + 1;
				}
			}
		}
		
		//Esquerda
		if( caraPode( ci, cj - 1, bi, bj ) ){
			//Sem a caixa
			if( ci != bi || cj - 1 != bj ){
				if( marc[ci][cj-1][bi][bj] == -1 ){
					fila.push( No(ci, cj - 1, bi, bj ) );
					marc[ci][cj-1][bi][bj] = dist + 1;
				}
			}else{
			//Com a caixa
				if( boxPode(bi,bj-1) && marc[ci][cj-1][bi][bj-1] == -1 ){
					fila.push( No( ci, cj - 1, bi, bj - 1 ) );
					marc[ci][cj-1][bi][bj-1] = dist + 1;
				}
			}
		}
		
		//direita
		if( caraPode( ci, cj + 1, bi, bj ) ){
			//Sem box
			if( ci != bi || cj + 1 != bj ){
				if( marc[ci][cj+1][bi][bj] == -1 ){
					marc[ci][cj+1][bi][bj] = dist + 1;
					fila.push( No( ci, cj + 1, bi, bj ) );
				}
			}else{
			//Com box
				if( boxPode( bi, bj + 1 ) && marc[ci][cj+1][bi][bj+1] == -1 ){
					marc[ci][cj+1][bi][bj+1] = dist + 1;
					fila.push( No( ci, cj + 1, bi, bj + 1 ) );
				}
			}
		}
		
	}
}

int main(){
	No ini, fim;
	while( scanf( "%d %d", &n, &m ) && ( n | m ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%s", ma[ i ] );
		
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < m; ++j ){
				if( ma[ i ][ j ] == '@' ){
					ini.ci = i;
					ini.cj = j;
				}else if( ma[ i ][ j ] == 'x' ){
					ini.bi = i;
					ini.bj = j;
				}else if( ma[ i ][ j ] == 'd' ){
					fim.ci = i;
					fim.cj = j;
				}else if( ma[ i ][ j ] == 'b' ){
					fim.bi = i;
					fim.bj = j;
				}
			}
		}
		
//		printf( "%d %d %d %d\n", ini.ci, ini.cj, ini.bi, ini.bj );
//		printf( "%d %d %d %d\n", fim.ci, fim.cj, fim.bi, fim.bj );
		
		bfs( ini );
		if( marc[fim.ci][fim.cj][fim.bi][fim.bj] == -1 ){
			printf( "No Way!\n" );
		}else{
			printf( "%d\n", marc[fim.ci][fim.cj][fim.bi][fim.bj] );
		}
	}
}


