#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
typedef unsigned long long hash;
#define B 1097
#define N 200000
char pat[N], str[N];

bool number( char ch ){
	return ch >= '0' && ch <= '9';
}

int plength;
bool match(){
	int cnt, par, imp;
	int p = 0, t = 0;
	int tlength = strlen(str);
	
	while(1){
		if( p == plength && t == tlength) break;
		
		par = imp = 0;
		while( p < plength && !number(pat[p]) ){
			if( pat[p] == '*' ) ++par;
			else ++imp;
			++p;
		}
		
		int ini = p, fim = p;
		hash padrao = 0;
		while( fim < plength && number(pat[fim]) ){
			padrao = padrao * B + pat[fim];
			++fim;
		}
		p = fim;
		
		int tam = 0;
		hash texto = 0;
		while( t < tlength && tam != fim - ini ){
			texto = texto * B + str[t];
			++t;
			++tam;
		}
		
		if( tam != fim - ini ) return false;
		hash pot = 1;
		for( int i = 1; i < tam; ++i ) pot *= B;
		
		if( !tam ){//sem numeros
			tlength -= t;//restantes
			tlength -= imp;//pelo menos os impares
			
			return tlength >= 0 && (tlength % 2) == 0;
		}
		
		cnt = 0;
		while(1){
			if( p == plength ){
				while( t != tlength ){
					if( imp + par == 0 ) return false;
					
					texto -= str[t - tam] * pot;
					texto = texto * B + str[t];
					++t;
					++cnt;
				}
			}
			if( texto == padrao && cnt >= imp && (cnt&1) == (imp&1) ) break;
			else{
				if( t == tlength ) return false;
				if( imp + par == 0 ) return false;
				texto -= str[t - tam] * pot;
				texto = texto * B + str[t];
				++t;
				++cnt;
			}
				
		}		
	}
	
	if( ( p < plength || t < tlength) )	return false;
	return true;
}

int main(){
	int caso = 1;
	
	while( scanf( "%s", pat ) != EOF ){
		int sub = 1;
		plength = strlen(pat);
		while( scanf( "%s", str ) != EOF ){
			if( str[0] == 'E' || str[0] == 'Q' ) break;
			if( match() )
				printf( "%d.%d. match\n", caso, sub++ );
			else
				printf( "%d.%d. not\n", caso, sub++ );
		}
		
		if( str[0] == 'Q' ) break;
		++caso;
	}
	
}




