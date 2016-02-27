#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
#define N 300

map<string,int> mapa;
int n;
bool ma[N][N];
char linha[10000];
char buf[1000];
char a[1000], b[1000];

char* getLine(char* out){
	out[0] = 0;
	while( cin.peek() == '\n' ) cin.ignore();
	return gets(out);
}

int get(char* in, bool t = true){
	int ta;
	if( mapa.count(in) ) return mapa[in];
	else{
		if(!t) return -1;
		
		ta = mapa[in] = n++;
		ma[ta][ta] = true;
		return ta;
	}
}


void update( int ta, int tb ){
	if(!ma[ta][tb]){
		ma[ta][tb] = true;
		for( int i = 0; i < n; ++i )
			ma[ta][i] |= ma[ta][tb] && ma[tb][i]; 
			
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j )
				ma[i][j] |= (ma[i][ta] && ma[ta][j]);
		}
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	gets(buf);
	
	for( int ca = 1; ca <= casos; ++ca ){
		printf( "Case #%d:\n", ca );
		mapa.clear();
		n = 0;
		memset( ma, false, sizeof ma );
		char p[100], q[100], r[100];
		linha[0] = 0;
		int c = 1;
		
		while( getLine(linha) != NULL ){
			int tam = strlen(linha);
			assert(linha[tam-1] == '!' || linha[tam-1] == '?' || linha[tam-1] == '.');
			if(linha[tam-1] == '!') break;
			char *tmp = linha;
			int qtd;
			
			if(tmp[tam-1] == '?'){		
				tmp[tam-1] = 0;
				char op[100];
				
				sscanf( tmp, "%s%s%s%n", op, a, b, &qtd ); //are ou can
				tmp += qtd;
				if(*tmp){
					sscanf(tmp, "%*s%s%s", a, b);
					int sa = strlen(a), sb = strlen(b);
					if(op[0] == 'a'){
						b[sb] = '_';
						b[sb+1] = 0;
					}
				}else{
					int sa = strlen(a), sb = strlen(b);
					a[sa] = '_'; a[sa+1] = 0;
					if(op[0] == 'a'){
						b[sb] = '_';
						b[sb+1] = 0;
					}
				}
				
//				if(ca == 3 && c == 35){
//					printf( "|%s|\n", linha);
//					for(map<string,int>::iterator it = mapa.begin(); it != mapa.end(); ++it)
//						printf( "%s\n", (it -> first).c_str());
//					return 1;
//				}
				
				int ta = get(a,false), tb = get(b,false);
				if((ta != -1 && tb != -1 && ma[ta][tb]) || strcmp(a,b) == 0 ) printf("Y");
				else printf( "M");
				++c;
			}else{
				tmp[tam-1] = 0;
				int qtd;
				
				char op[100];
				sscanf( tmp, "%s%s%s%n", a, op, b, &qtd );
				tmp += qtd;
				if(*tmp){
					sscanf( tmp, "%s%s%s", a, op, b );
					int sa = strlen(a), sb = strlen(b);
					if(op[0] == 'a'){
						b[sb] = '_';
						b[sb+1] = 0;
					}
				}else{
					int sa = strlen(a), sb = strlen(b);
					a[sa] = '_'; a[sa+1] = 0;
					if(op[0] == 'a'){
						b[sb] = '_';
						b[sb+1] = 0;
					}
				}
				
				int ta = get(a), tb = get(b);
				update(ta, tb);
				
			}
		}
		
//		for(map<string,int>::iterator it = mapa.begin(); it != mapa.end(); ++it)
//			printf( "%s\n", (it -> first).c_str());
//		
		printf( "\n");
		
		
	}	
}

