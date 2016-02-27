#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int DIR = 0, ESQ = 1, INDEF = -1;
typedef long long ll;
#define mp make_pair

struct No{
	int adj[ 2 ];
	char op;
	int posX;
	ll val;
}nos[ 1000 ];

int cont;
int pilha[ 1000 ];
string linha;

bool ehOperador( char a ){
	if( a == '+' || a == '-' || a == '*' || a == '/' ) return true;
	return false;
}

bool ehDigito( char a ){
	return a >= '0' && a <= '9';
}

void buildTree(){
	int sp = 0;
	cont = 0;
		
	for( int i = 0; linha[ i ]; ++i ){		
		// printf( "A %c\n", linha[ i ] );
		if( ehOperador( linha[ i ] ) ){
			nos[ cont ].op = linha[ i ];
			nos[ cont ].adj[ DIR ] = pilha[ --sp ];
			nos[ cont ].adj[ ESQ ] = pilha[ --sp ];
			pilha[ sp++ ] = cont;
			++cont;
		}else if( ehDigito( linha[ i ] ) ){
			nos[ cont ].op = 0;
			nos[ cont ].adj[ 0 ] = nos[ cont ].adj[ 1 ] = INDEF;
			nos[ cont ].val = linha[ i ] - '0';
			pilha[ sp++ ] = cont;
			++cont;
		}else if( linha[ i ] == 'X' ){
			nos[ cont ].op = 'X';
			nos[ cont ].adj[ 0 ] = nos[ cont ].adj[ 1 ] = INDEF;
			pilha[ sp++ ] = cont;
			++cont;
		}
	}
}

ll gcd( ll a, ll b ){
	ll temp;
	a = abs( a );
	b = abs( b );
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

ll mmc( ll a, ll b ){
	return a * b / gcd( a, b );
}


pair<ll,ll> norm( pair<ll,ll> a ){
	if( a.second < 0 ){
		a.second *= -1;
		a.first *= -1;
	}
	
	ll mdc = gcd( a.first, a.second );
	a.first /= mdc;
	a.second /= mdc;
	
	return a;
}


pair<ll,ll> somar( pair<ll,ll> a, pair<ll,ll> b ){
	ll mult = mmc( a.second, b.second );
	// printf( "Mult %lld\n", mult );
	a.first *= ( mult / a.second );
	b.first *= ( mult / b.second );
	
	return norm( mp( a.first + b.first, mult ) ); 
}

pair<ll,ll> multiplicar( pair<ll,ll> a, pair<ll,ll> b ){
	return norm( mp( a.first * b.first, a.second * b.second ) );
}

pair<ll,ll> dividir( pair<ll,ll> a, pair<ll,ll> b ){
	return norm( mp( a.first * b.second, a.second * b.first ) ); 
}

pair<ll,ll> menos( pair<ll,ll> a ){
	return norm( mp( -a.first, a.second ) );
}

pair<ll,ll> subtrair( pair<ll,ll> a, pair<ll,ll> b ){
	return norm( somar( a, menos( b ) ) );	
}


pair<ll,ll> avaliar( int root ){
	if( !nos[ root ].op )
		return mp( nos[ root ].val, 1 );
	
	pair<ll,ll> a = avaliar( nos[ root ].adj[ ESQ ] ), b = avaliar( nos[ root ].adj[ DIR ] );
	
	if( nos[ root ].op == '+' )
		return somar( a, b );
	else if( nos[ root ].op == '-' )
		return subtrair( a, b );
	else if( nos[ root ].op == '*' )
		return multiplicar( a, b );
	else if( nos[ root ].op == '/' )
		return dividir( a, b );
}

bool preencher( int root ){
	if( nos[ root ].op == 'X' )
		return true;
		
	if( !nos[ root ].op )
		return false;
	
	bool dir = preencher( nos[ root ].adj[ DIR ] ), esq = preencher( nos[ root ].adj[ ESQ ] );
	
	if( dir )
		nos[ root ].posX = DIR;
	else if( esq )
		nos[ root ].posX = ESQ;
	else
		nos[ root ].posX = INDEF;
		
	return ( dir || esq );	
}

/*
void posordem( int root ){
	if( nos[ root ].op ){
		if( nos[ root ].op == 'X' )
			printf( "Root %d X", root  );
		else{
			posordem( nos[ root ].adj[ ESQ ] );
			posordem( nos[ root ].adj[ DIR ] );
			printf( " Root %d (%c-%d)", root, nos[ root ].op, nos[ root ].posX );
		}
	}else
		printf( "Root %d %lld", root, nos[ root ].val );
}*/

int main(){
	
	while( cin.peek() == '\n' ) cin.ignore();
	
	while( getline( cin, linha ) ){
		buildTree();
		
		preencher( cont - 1 );
		
		pair<ll,ll> result = mp( 0, 1 ), temp;
		
		int sinal = 0;
		
		int root = cont - 1, posX;
		if( nos[ root ].posX == INDEF ){
			temp = avaliar( root );
			if( temp.first == 0 )
				sinal = 1;
			else
				sinal = -1;
		}
		ll mdc;	
		while( !sinal && nos[ root ].op != 'X' ){
		
		//	result = norm( result );
			
			posX = nos[ root ].posX;

			if( nos[ root ].op == '+' ){
				temp = avaliar( nos[ root ].adj[ posX xor 1 ] );
				result = subtrair( result, temp );
			}else if( nos[ root ].op == '-' ){
				if( posX == DIR ) // 41 - x = 0
					result.first = -result.first;
				result = somar( result, avaliar( nos[ root ].adj[ posX xor 1 ] ) );
			}else if( nos[ root ].op == '/' ){
				temp = avaliar( nos[ root ].adj[ posX xor 1 ] );
				if( temp.first == 0 ){
					if( result.first == 0 )
						sinal = 1;
					else
						sinal = -1;
					break;
				}
				
				if( posX == DIR ){
					// 41 / x = 0
					ll t = result.first;
					result.first = result.second;
					result.second = t;
					
					if( result.second == 0 ){
						sinal = -1;
						break;
					}
				}
				
				result = multiplicar( result, temp );			
			}else if( nos[ root ].op == '*' ){
				temp = avaliar( nos[ root ].adj[ posX xor 1 ] );
				if( temp.first == 0 ){
					if( result.first == 0 )
						sinal = 1;
					else
						sinal = -1;
					break;
				}
				
				result = dividir( result, temp );
			}
			
			root = nos[ root ].adj[ posX ];
		}
		
		if( !sinal ){
		//	mdc = gcd( result.first, result.second );
		//	result.first /= mdc;
		//	result.second /= mdc;
			result = norm( result );
		//	if( result.first % result.second )
				printf( "X = %lld/%lld\n", result.first, result.second );
		//	else
		//		printf( "X = %lld\n", result.first / result.second );
			
		}else if( sinal == 1 ){
			printf( "MULTIPLE\n" );
		}else
			printf( "NONE\n" );
		
		while( cin.peek() == '\n' ) cin.ignore();
	}
}



