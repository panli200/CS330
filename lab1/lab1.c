/*
       +------------------+
       |  TEXT            | x400200
       |                  |
       |  instructions in | x40084b = proc1
       |  machine code    | x400930 = proc2
       |                  |
       +------------------+ x400b36 = etext
       |  DATA            | x6014bc = g1   global initialized
       |  - initialized   | x6014c0 = g3
       |    variables     | x6014c8 = ls1  static initialized
       |                  | x6014c4 = ls3
       |                  | 
       | ---------------  | x6014cc = edata
       |                  | x601500 = g0   global uninitialized
       |                  | x601520 = g2   big array 
       |                  | x602c90 = g4
       |  - uninitialized | x602c98 = ls0  static uninitialized
       |    variables     | x602c94 = ls2
       |                  |
       |                  | 
       | ---------------  | x602ca0 = end 
       |  - heap for      | x1c10010 pointed to by heap1
       |  dynamic         | x1c10030 pointed to by heap2
       |  allocation      |
       |                  |
       |                  |
       +------------------+ 
                |
                |
                V

                .
                .
                .

                ^
                |
                |
       +------------------+
       |  STACK           | x7ffd03103138 = lc4, lc6   | Activation record for 
       |  - function      | x7ffd0310313c = lc3, lc5   | proc1 or proc2
       |    activation    |
       |    records       |
       |  - local         | x7ffd03103154 = lc2       | Activation record for
       |    automatic     | x7ffd03103158 = lc1       | main
       |    variables     | x7ffd0310315c = lc0       |
       +------------------+
*/
/*
Question:4
Answer:As variables are added to the stack, the addresses get smaller

Question:5
Answer:Variables stored on the stack have the same address as other variables. 
Because a variable pushed into the stack, then pop. Another variable pushed into the stack, thus they have the same address.

Question:6
Answer:We expect variables in recursive functions to stored in stack.
After step 7, this answer is correct. 
*/

#include <stdio.h>
long factorial (int n);

int main(){
       int a;
       printf("Please enter an integer:");
       scanf("%i",&a);
       printf("Factorial %i = %li \n", a , factorial(a));
       return 0;
}


long factorial (int n){
       long result;
       if(n == 0)
        result = 1;
       else
        result= n * factorial(n-1);
       return result;
}