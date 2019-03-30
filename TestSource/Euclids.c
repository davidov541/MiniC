#include <stdio.h>
// The following method determines the Greatest Common Divisor of a and b
// using Euclid's algorithm.
int gcd(int a, int b)
{
  if (a == 0) {
    return b;
  }
  
  while (b != 0) {
	if (a > b) {
	  a = a - b;
	} else {
	  b = b - a;
	}
  }
  return a;
}

// Find m that is relatively prime to n.
int relPrime(int n)
{
   int m = 2;

   //m = 2;
   
   while (gcd(n, m) != 1) {  // n is the input from the outside world
		m = m + 1;
   }

   return m;
}

int main(int argc)
{
	int c;
	while(true)
	{
		c = getchar();
		int x = relPrime(c);
		putk(x);
	}
	return 0;
}