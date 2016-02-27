#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50

char ma[30][30];
char key[30];
char tmp[100];
char enc[100], resp[100];

int main(){
	gets(tmp);
	int h;
	for(h = 0; tmp[h] != ':'; ++h);
	tmp[h] = 0;
	strcpy(key, tmp + h + 1);
//	printf( "W |%s| |%s|\n",tmp, key); 
	
	for(int i = 0; i < h; ++i){
		ma[i][0] = tmp[i];
		for(int j = 1; j < 27; ++j){
			if(ma[i][j-1] == 'Z') ma[i][j] = ' ';
			else if(ma[i][j-1] == ' ') ma[i][j] = 'A';
			else ma[i][j] = ma[i][j-1] + 1;
		}
	}
	
	while(gets(enc)){
		int aux[100];
		int linha = 0;
		int c;
		for(int i = 0; key[i]; ++i)
			aux[i] = key[i] - '0';
			
		for(c = 0; enc[c]; ++c){
//			if(c <= 2) printf("Linha %d %d\n", linha, aux[linha] );
			int j;
			for(j = 0; j < 27; ++j){
				if(ma[linha][j] == enc[c]) break;
			}
			
			if(j == 26) resp[c] = ' ';
			else resp[c] = j + 'a';
			
			--aux[linha];
			if(!aux[linha]){
				aux[linha] = key[linha] - '0';
				++linha;
				linha %= h;
			}
		}
		resp[c] = 0;
		printf( "%s\n", resp );
	}	
	
}




