#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
#define N 1000200

char str[N], out[N];
int tam;

int pilha[N], sp;
bool dm;

void faz(){
	dm = false;
	sp = 0;
	
	int pos = -1;
	char letra;
	for( int i = 0; i < tam; ++i ){
		if(str[i] == 'a'){
			//mudar pra 'e'
			if(sp && pilha[sp-1] == 'a'){
				pos = i;
				letra = 'e';
			}else if(i+sp+2 <= tam){//colocar i
				pos = i;
				letra = 'i';
			}else if( sp && pilha[sp-1] == 'i'){//para 'o'
				pos = i;
				letra = 'o';
			}
			pilha[sp++] = str[i];
		}else if(str[i] == 'i'){
			if( sp && pilha[sp-1] == 'i' ){//colocar 'o' 
				pos = i;
				letra = 'o';
			}
			pilha[sp++] = str[i];
		}else if(str[i] == 'e'){
			if(i+sp+2 <= tam ){//colocar 'i'
				letra = 'i';
				pos = i;
			}else if(sp && pilha[sp-1] == 'i' ){//colocar 'o'
				letra = 'o';
				pos = i;
			}
			
			if(!sp || pilha[sp-1] != 'a'){
				dm = true;
				break;
			}else --sp;
		}else if(str[i] == 'o'){
			if(!sp || pilha[sp-1] != 'i'){
				dm = true;
				break;
			}
			else --sp;
		}
	}
	
	if(sp) dm = true;

	if(dm) printf( "INVALID\n" );
	else if(pos == -1 ) printf( "ULTIMATE\n" );
	else{
		sp = 0;
		int i;
		for( i = 0; i < tam;  ){
			if( i == pos ){
				out[i++] = letra;
				if(letra == 'i') pilha[sp++] = 'i';
				else --sp; /*if( letra == 'e' || letra == 'o' ) */ 

				int qtd = tam - i - sp;
				for( int j = 0; j < qtd / 2; ++j, ++i )	out[i] = 'a';
				for( int j = 0; j < qtd / 2; ++j, ++i )	out[i] = 'e';
					
				while( sp ){
					char ch = pilha[--sp];
					if(ch =='a') out[i++] = 'e';
					else if(ch == 'i') out[i++] = 'o';
				}
				
			}else{
				if(str[i] == 'e' ) --sp;
				else if(str[i] == 'o' ) --sp;
				else pilha[sp++] = str[i];
				out[i] = str[i++];
			}
		}
		out[tam] = 0;
		printf( "%s\n", out );
	}
}

int main(){
	int n;
	scanf( "%d", &n );
	
	while( n-- ){
		scanf( "%s", str );
		for( tam = 0; str[tam]; ++tam );
		faz();
		
	}
}




