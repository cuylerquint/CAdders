/*
Cuyler Quint
CPS 360
2/21/16

Assigment 3
  implement halfaddr/fulladdr into 4 bit and 16 bit adders
  utilzing ripple carry scheme.  Addtionally provide parity,
  Mutiplexer and Magintude functions for the program parameters

*/



#include <stdio.h>
#include <stdlib.h>
/*
  This module peforms a bit summation on the lowest
  order bits of the two varibles passed in
  while setting the out cary and sum

*/
void halfaddr(int a, int b, int *sum, int *outcarry){
  void printForm(char *, int *s, int *c );
  int bitzeroa = (a & (1 << 0)) >> 0;
  int bitzerob = (b & (1 << 0)) >> 0;
  *sum = *outcarry = 0;
  *sum = ((bitzeroa & 1) ^ (bitzerob & 1));
  *outcarry = ((bitzeroa & 1) & (bitzerob & 1));


}

/*
  This function peforms a full add on the lowest order
  bits of two numbers and carrys the bit if the
  operation permits for the next possible add
*/

void fulladdr(int a, int b, int incarry, int *sum, int *outcarry){
  int bitzeroa = (a & (1 << 0)) >> 0;
  int bitzerob = (b & (1 << 0)) >> 0;
  int AxorB = ((bitzeroa & 1) ^ (bitzerob & 1));
  *sum = *outcarry = 0;
  *sum = ((AxorB & 1) ^ (incarry & 1));
  *outcarry = ((AxorB & incarry) | (bitzeroa & bitzerob));
}


/*
  This function performs a ripple carry add that
  uses 4 Full adders and carrys the outcarry from the last
  into the new fulladder
*/

void add4(int a, int b, int incarry, int *sum, int *outcarry){
  void printForm(char *, int *s, int *c);
  void printresult(char *label, int a);
  int tempSum0 = 0;
  int tempSum1 =  0;
  int tempSum2 = 0;
  int tempSum3 = 0;
  int bita0 = (a & (1 << 0)) >> 0;
  int bitb0 = (b & (1 << 0)) >> 0;
  int bita1 = (a & (1 << 1)) >> 1;
  int bitb1 = (b & (1 << 1)) >> 1;
  int bita2 = (a & (1 << 2)) >> 2;
  int bitb2 = (b & (1 << 2)) >> 2;
  int bita3 = (a & (1 << 3)) >> 3;
  int bitb3 = (b & (1 << 3)) >> 3;

  fulladdr(bita0,bitb0,incarry,sum,outcarry);
  tempSum0 = *sum;
  incarry = *outcarry;

  fulladdr(bita1,bitb1,incarry,sum,outcarry);
  tempSum1 = *sum;
  incarry = *outcarry;

  fulladdr(bita2,bitb2,incarry,sum,outcarry);
  tempSum2 = *sum;
  incarry = *outcarry;


  fulladdr(bita3,bitb3,incarry,sum,outcarry);
  tempSum3 = *sum;
  incarry = *outcarry;

  *sum ^= (-tempSum0 ^ *sum) & (1 << 0);
  *sum ^= (-tempSum1 ^ *sum) & (1 << 1);
  *sum ^= (-tempSum2 ^ *sum) & (1 << 2);
  *sum ^= (-tempSum3 ^ *sum) & (1 << 3);

}

/*
  Simiular to the add4 this function summates the lower 2 bytes
  of two given numbers that incoperates the use of 4 add4 functions

*/

void add16(int a, int b, int incarry, int *sum, int *outcarry){
  void add16(int a, int b, int incarry, int *sum, int *outcary);
  int sum0, sum1, sum2, sum3;
  int ashift, bshift;
  int abits0,bbits0,abits1,bbits1,abits2,bbits2, abits3, bbits3;
  abits0 = (a >> 0) & ((1 << 4) - 1);
  bbits0 = (b >> 0) & ((1 << 4) - 1);

  ashift = a >> 4;
  bshift = b >> 4;

  abits1 = (ashift >> 0) & ((1 << 4) - 1);
  bbits1 = (bshift >> 0) & ((1 << 4) - 1);

  ashift = a >> 8;
  ashift = b >> 8;

  abits2 = (ashift >> 0) & ((1 << 4) - 1);
  bbits2 = (bshift >> 0) & ((1 << 4) - 1);

  ashift = a >> 12;
  ashift = b >> 12;

  abits3 = (ashift >> 0) & ((1 << 4) - 1);
  bbits3 = (bshift >> 0) & ((1 << 4) - 1);


  add4(abits0,bbits0, incarry, sum, outcarry);
  sum0 = *sum;
  incarry = *outcarry;

  add4(abits1,bbits1, incarry, sum, outcarry);
  sum1 = *sum;
  incarry = *outcarry;

  add4(abits2,bbits2, incarry, sum, outcarry);
  sum2 = *sum;
  incarry = *outcarry;

  add4(abits3,bbits3, incarry, sum, outcarry);
  sum3 = *sum;
  incarry = *outcarry;

  *sum = 0;

  sum1 = sum1 << 4;
  sum2 = sum2 << 8;
  sum3 = sum3 << 12;

  *sum = *sum | sum0;
  *sum = *sum | sum1;
  
}


/*
   finds magnitude of a (lower order 4 bits) using an add4 and xors
*/

void magnitude4(int a, int *rslt){
  void fulladdr(int a, int b, int incarry, int *sum, int *outcary);
  int incarry = 0;
  int *sum = 0;
  int *outcarry = 0;

  int sum0, sum1;

  int bita0 = (a & (1 << 0)) >> 0;
  int bita1 = (a & (1 << 1)) >> 1;
  int bita2 = (a & (1 << 2)) >> 2;
  int bita3 = (a & (1 << 3)) >> 3;

  add4(bita0,bita1,incarry,sum,outcarry);
  sum0 = *sum;

  add4(bita2,bita3,incarry,sum,outcarry);
  sum1 = *sum;

  *rslt = (sum0 ^ sum1);
}

/*

  This function performs as a Mutiplexer and selects
  one of the inputs based off of the given parameters

*/

void mux2x1(int a,int b,  int select, int *out){
  void printresult(char *label, int a);
  int alow = (a & (1 << 0)) >> 0;
  int blow = (b & (1 << 0)) >> 0;
  int slow = (select & (1 << 0)) >> 0;
  *out = (( ((slow ^ 1) & 1) & (alow & 1)) |  ((slow & 1 ) & (blow & 1)));

}

/*
  This function generates provides the odd parity
    of the lower odrer 3 bits of a given int
*/

void parity4(int a, int *outparity){
  int bitzeroa = (a & (1 << 0)) >> 0;
  int bitonea = (a & (1 << 1)) >> 1;
  int bittwoa = (a & (1 << 2)) >> 2;
  int zeroXORone = ((bitzeroa) ^ (bitonea));
  int parityA = (~(zeroXORone ^  bittwoa) & (1 << 0)) >> 0;
  printf("odd parity a:%d\n\n", parityA);

}

/*
  Helper Function to print correct format to screen
*/

void printForm(char *label, int *s, int *c ){
  void printresult(char *label, int a);
  printf("%s\n",label);
  printresult("sum:\t\t",*s);
  printresult("outcarry:\t",*c);
  printf("\n");
}

/*
  Function to print 32 bits of a given int
*/

void printresult(char *label, int a){
  unsigned i;
  int count = 0;
  printf("%s ",label);
  for (i = 1 << 31; i > 0; i = i / 2){
    (a & i)? printf("1"): printf("0");
    if ((count +1) % 8 == 0 ){
      if(count == 31 )break;
        else printf(" ");
   }
   count++;
 }
     printf("\n");
}

/*
  Allocates memeory for a given varible
*/
void mal(int **data) {
  *data = malloc (sizeof (int));
}

/*
  Prints the parameters given to the progarm
*/
void printInput(int a , int b){
  printf("num A: %d\t",a);
  printresult("",a);
  printf("num B: %d\t",b);
  printresult("",b);
  printf("\n");

}

int main(int argc, char *argv[]) {
  void halfaddr(int a, int b, int *sum, int *outcarry);
  void fulladdr(int a, int b, int incary, int *sum, int *outcary);
  void add4(int a, int b, int incary, int *sum, int *outcary);
  void add16(int a, int b, int incarry, int *sum, int *outcary);
  void parity4(int a, int *outparity);
  void mux2x1(int a, int b, int select, int *out);
  void magnitude4(int a, int *rslt);
  int *outparity = 0;
  int *sum = NULL;
  int *outcarry = NULL;
  int *out = 0;
  int *rslt = 0;
  mal(&out);
  mal(&sum);
  mal(&outcarry);
  mal(&outparity);
  int a = strtol(argv[1], NULL, 16);
  int b = strtol(argv[2], NULL, 16);
  int incarry = strtol(argv[3], NULL, 16);
  printInput(a,b);
  halfaddr(a,b,sum,outcarry);
  printForm("HalfAdder:",sum,outcarry);
  fulladdr(a,b,incarry,sum,outcarry);
  printForm("FullAdder:",sum,outcarry);
  add4(a,b,incarry,sum,outcarry);
  printForm("Add4:",sum,outcarry);
  add16(a,b,incarry, sum, outcarry);
  printForm("Add16:", sum, outcarry);
  parity4(a,outparity);
  mux2x1(a,b,1,out);
  printresult("mux select 1:", *out);
  mux2x1(a,b,0,out);
  printresult("mux select 0:", *out);
  magnitude4(a, rslt);


  return 0;
}
