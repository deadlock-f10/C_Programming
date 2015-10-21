#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#ifndef BigIntegerArithmatic
#define BASE 10
#define N 1024
int make_int (int A[], int n);
void increment (int A[]) ;
void add (int A[], int B[], int C[]) ;
void multiply (int A[], int B[], int C[]) ;
void multiply_one_digit (int A[], int B[], int n) ;
void shift_left (int A[], int n) ;
#endif

#define Max(x,y) ((x) < (y) ? (y):(x) )
#define Ceiling(x,y) ((x % y == 0) ? (x / y) : (x / y + 1))

struct INT{               
	int msb;               // most sufficient bit
	int length;              // length = msb+1
	//int *integer;          
	int integer[N];          
};
typedef struct INT *Int;
int K;
int at_least(int total ,int leftbit){  // 
	/*if(total >= (leftbit * 9))
		if(total % 9 == 0)
			return 9;
		else 
			return total % 9;
	else if(total == (leftbit * 9))
		return 9;
	else
		return 0;*/
	if(total <= leftbit * 9)
		return 0;
	else{
		return total - 9 * (leftbit);
	}
}
Int decide_min(int total, int totalbit){     // presume that least_bit == totalbit
	Int I = malloc(sizeof(struct INT));
	int i = 0;
	I->length = totalbit;
	I->msb = totalbit - 1;
	while(total > 9){
		I->integer[i++] = 9;
		total -= 9;
	}
	assert(i == I->msb);
	I->integer[I->msb] = total;
	return I;
}
Int decide_max(int total, int totalbit){
	Int I = malloc(sizeof(struct INT));
	I->length = totalbit;
	I->msb = totalbit - 1;
	int i;
	for(i = I->msb ; i >= 0 ; i--)
	{
		if(total > 9)
			I->integer[i] = 9;
		else
			I->integer[i] = total;
		total -= I->integer[i];
	}
	return I;
}
int least_bit(int total){
	return Ceiling(total,9);
}
int compare(Int A,Int B, int begin_bit){
	int i = begin_bit;
	int diff = 0;
	while(i >= 0 && (diff = (A->integer[i] - B->integer[i])) == 0 )
		i--;
	return diff;
}
Int findnext(Int Prev , int total){
	//printf("PrevLength=%d,total=%d\n",Prev->length,total);
	int cur_bit = Prev->msb;
	//int caut_point = cautious_point(Prev);
	if(least_bit(total) > Prev->length)
		return decide_min(total , least_bit(total));
	/*else if(least_bit(total) < Prev->length)
		return decide_min(total , Prev->length + 1);*/
	else if(compare(decide_max(total,Prev->length) , Prev , Prev->msb) > 0){
		Int cur = malloc(sizeof(struct INT));
		cur->length = Prev->length;
		cur->msb = cur->length - 1;
		while(cur_bit > 0){
			int suggest = Max(at_least(total,cur_bit) , Prev->integer[cur_bit]);
			//printf("suggest= %d\n",suggest);
			if(compare(decide_max(total - suggest , cur_bit) , Prev , cur_bit - 1) > 0){
				cur->integer[cur_bit] = suggest;
				cur_bit--;
				total -= suggest;
			}
			else{
				total -= (suggest + 1);
				cur->integer[cur_bit] = suggest+1;
				// do not use decied_min
				Int m = decide_max(total , cur_bit);
				cur_bit--;
				int i = cur_bit;
				while(i >= 0){
					cur->integer[i] = m->integer[cur_bit - i];
					i--;
				}
				free(m);
				break;
			}
		}
		if(cur_bit == 0)
			cur->integer[0] = total;
		return cur;
	}
	else{
		Int cur = malloc(sizeof(struct INT));
		cur->length =  Prev->length + 1;
		cur->msb = Prev->length;
		cur->integer[cur->msb] = 1;
		Int m = decide_max(total - 1 , cur->msb);
		int i = cur->msb-1;
		while(i >= 0){
			cur->integer[i] = m->integer[cur->msb -1 - i];
			i--;
		}
		free(m);
		return cur;
	}
}

Int Mult(Int A,int K){
	Int r = malloc(sizeof(struct INT));
	int m[N];
	make_int(m,K);
	multiply(A->integer,m,r->integer);
	//free(A);
	int i = N-1; 
	while(r->integer[i] == 0)
		i--;
	r->msb = i;
	r->length = i+1;
	return r;
}
int total(Int A){
	int t = 0;
	int i;
	for(i = A->msb ; i >= 0; i--)
		t += A->integer[i];
	return t;
}
void print(Int A);
int main()
{
	FILE *in =fopen("sequence.in","r"), *out = fopen("sequence.out","w");
	int K,a1,n;
	fscanf(in,"%d%d%d",&a1,&K,&n);
	Int A = malloc(sizeof(struct INT));
	A->length = make_int(A->integer,a1);
	A->msb = A->length-1;
	int i=1;
	while(i < n){
		i++;
//		A = findnext(A,10);
		Int B = Mult(A,K);
		//print(A);
		//print(B);
		A = findnext(A,total(B));
		free(B);
		//print(A);
		//printf("a%d=",i);
	}
	i = A->msb;
	while(i >= 0)
		fprintf(out,"%d",A->integer[i--]);
	fprintf(out,"\n");
	return 0;
}
void print(Int A){
	int j=A->msb;
	while(j >= 0)
		printf("%d",A->integer[j--]);
	printf("\n");
}




int make_int (int A[], int n) {
	int	i;

	/* start indexing at the 0's place */

	i = 0;

	/* while there is still something left to the number
	 * we're encoding... */

	while (n) {

		/* put the least significant digit of n into A[i] */

		A[i++] = n % BASE;

		/* get rid of the least significant digit,
		 * i.e., shift right once
		 */

		n /= BASE;
	}
	int m = i;

	/* fill the rest of the array up with zeros */

	while (i < N) A[i++] = 0;
	return m;
}
/* A++ */
void increment (int A[]) {
	int	i;

	/* start indexing at the least significant digit */

	i = 0;
	while (i < N) {

		/* increment the digit */

		A[i]++;

		/* if it overflows (i.e., it was 9, now it's 10, too
		 * big to be a digit) then...
		 */
	
		if (A[i] == BASE) {

			/* make it zero and index to the next 
			 * significant digit 
			 */
			A[i] = 0;
			i++;
		} else 
			/* otherwise, we are done */
			break;
	}
}
/* C = A + B */
void add (int A[], int B[], int C[]) {
	int	i, carry, sum;

	/* no carry yet */

	carry = 0;

	/* go from least to most significant digit */

	for (i=0; i<N; i++) {

		/* the i'th digit of C is the sum of the
		 * i'th digits of A and B, plus any carry
		 */
		sum = A[i] + B[i] + carry;

		/* if the sum exceeds the base, then we have a carry. */

		if (sum >= BASE) {

			carry = 1;

			/* make sum fit in a digit (same as sum %= BASE) */

			sum -= BASE;
		} else
			/* otherwise no carry */

			carry = 0;

		/* put the result in the sum */

		C[i] = sum;
	}

	/* if we get to the end and still have a carry, we don't have
	 * anywhere to put it, so panic! 
	 */
	if (carry) printf ("overflow in addition!\n");
}
/* C = A * B */
void multiply (int A[], int B[], int C[]) {
	int	i, P[N];

	/* C will accumulate the sum of partial products.  It's initially 0. */

	make_int (C, 0);

	/* for each digit in A... */

	for (i=0; i<N; i++) {
		/* multiply B by digit A[i] */

		multiply_one_digit (B, P, A[i]);

		/* shift the partial product left i bytes */

		shift_left (P, i);

		/* add result to the running sum */

		add (C, P, C);
	}
}
/* B = n * A */
void multiply_one_digit (int A[], int B[], int n) {
	int	i, carry;

	/* no extra overflow to add yet */

	carry = 0;

	/* for each digit, starting with least significant... */

	for (i=0; i<N; i++) {

		/* multiply the digit by n, putting the result in B */

		B[i] = n * A[i];

		/* add in any overflow from the last digit */

		B[i] += carry;

		/* if this product is too big to fit in a digit... */

		if (B[i] >= BASE) {

			/* handle the overflow */

			carry = B[i] / BASE;
			B[i] %= BASE;
		} else

			/* no overflow */

			carry = 0;
	}
	if (carry) printf ("overflow in multiplication!\n");
}
void shift_left (int A[], int n) {
	int	i;

	/* going from left to right, move everything over to the
	 * left n spaces
	 */
	for (i=N-1; i>=n; i--) A[i] = A[i-n];

	/* fill the last n digits with zeros */

	while (i >= 0) A[i--] = 0;
}

