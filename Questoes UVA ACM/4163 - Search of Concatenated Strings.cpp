#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long hash;
#define B 937

char text[6000];
char words[15][100];
char linha[6000];

int pot[15];
int len[15];
int size;
int n, m;

hash expo[200];

bool pd[5010][1 << 14];

char* getLine(char* in){
	in[0] = 0;
	
	while( gets(in) != NULL && in[0] == 0 ) in[0] = 0;
	
	if(in[0]) return in;
	return NULL;
}

void init(){
	for( int i = 0; i <= size; ++i ){
		for( int j = 0; j <= pot[n]; ++j ) pd[i][j] = false;
	}

	for( int i = 0; i < n; ++i ){
		hash hp = 0, ht = 0;
		len[i] = 0;
		
		for( int& j = len[i]; words[i][j]; ++j )
			hp = hp * B + words[i][j];
		for( int j = 0; j < min(len[i], size); ++j )
			ht = ht * B + text[j];
		
		int ind = len[i], ini = 0;
		
		while(ind <= size){
			if(hp == ht)
				pd[ini][pot[i]] = true;
						
			ht = ht - text[ini] * expo[len[i]-1];
			ht = ht * B + text[ind];
			++ind;
			++ini;
		}
	}
}

int main(){
	pot[0] = 1;
	for( int i = 1; i < 15; ++i ) pot[i] = 2 * pot[i-1];
	expo[0] = 1;
	for( int i = 1; i < 200; ++i ) expo[i] = B * expo[i-1];
	
	while( scanf( "%d %d", &n, &m ) != EOF && (n|m) ){
		for( int i = 0; i < n; ++i ){
			scanf( "%s", words[i] );
		}
		text[0] = 0;
		
		size = 0;
		for(int i = 0; i < m; ++i ){
			scanf( "%s", text + size);
			while(text[size]) ++size;
		}
//		size = strlen(text);
		init();
		
		int cont = 0;
		for( int i = size - 1; i >= 0; --i ){
			for( int j = 0; j < n; ++j ){
				if( i + len[j] >= size ) continue;
				
				if(pd[i][pot[j]]){
					for( int k = 0; k < 1 << n; ++k ){
						if( k & pot[j] ) continue;
						pd[i][k | pot[j]] |= pd[i+len[j]][k];
					}
				}
			}
			if(pd[i][pot[n] - 1]) ++cont;
		}
		
		printf( "%d\n", cont );
	}
	
		
}

