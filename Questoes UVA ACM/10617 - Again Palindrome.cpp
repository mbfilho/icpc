/*
10617 - Again Palindrome 
Examples of BAOBAB derived observational 
0 B 
1 A 
2 O 
3 B 
4 A 
5 B 
Two for loops to run, outside the loop i is index 0 to index 5, within the loop is j = i + 1 to index 5. 
str [i] == B of the index is 0, str [j] == B of the index is 3, index 3 - index 0 = count 3. 
BAOB just have BB, BAB, BOB this 3, and the same results. 
str [j] == B of the index is 5, index 5 - index 0 = count 5. 
BAOBAB for end to end B to count just a BB, BAB, BOB, BBB, BAB these 5 species, and the same results. 
So the first step of this assumption has been correct, and now look at the second step. 

B can still arise between the head and tail BAAB, BAOAB, BABAB the 3 groups. 
Then the two groups B to remove head and tail into AA, AOA, ABA, is precisely equal to AOBA the 3 groups change, so the second step is to run the recursion. 
When str [i] == A, the calculation of AOBA the three groups also resulted in duplication. This can open a two-dimensional unsigned long long array, record the value has been calculated that, to avoid recursive counted the same thing too many times resulting in TLE. 
Finally, we have B, A, O, B, A, B 6 single character that did not add to, exactly equal to string length, plus is the answer.
*/

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

ll memo[61][61];
int tam;
char s1[70];

ll responder( int i, int j ){
//	cout << i << " " << j << endl;
	if( i > j || j >= tam )
		return 0;
		
	if( memo[i][j] != -1 )
		return memo[i][j];
	if( i == j )
		return memo[i][j] = 1;

		
	ll resp = responder( i + 1, j ) + responder( i, j + 1 ) - responder( i + 1, j - 1 );
	if( s1[i] == s1[j] )
		resp += 1 + responder( i + 1, j - 1 );
	
	return memo[i][j] = resp;
}

int main(){
	int qtd;
	cin >> qtd;
	
	while( qtd-- ){
		cin >> s1;
		tam = strlen( s1 );
		for( int i = 0; i < tam; ++i ){
			for( int j = 0; j < tam; ++j )
				memo[i][j] = -1;
		}
		cout << responder( 0, tam - 1 ) << endl;
	}
}
