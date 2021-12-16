#include "Pow2Util.h"
#include <math.h>

NS_YH_BEGIN

bool isPow2(int n)
{
	if (n <= 0)
		return false;
	return (n & (n - 1)) == 0;
}

// Next power of 2  
int nextPow2(int n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;
	return n;
}

// Previous power of 2  
int prevPow2(int n)
{
	int n2 = n >> 1;
	// divide by 2    
	if (n2 > 0)
		return nextPow2(n2);
	else
		return nextPow2(n);
}

// Nearest power of 2  
int nearPow2(int n)
{
	if (isPow2(n))
		return n;
	int nNext = nextPow2(n);
	int nPrev = prevPow2(n);
	if (nNext - n > abs(n - nPrev))
		return nPrev;
	else
		return nNext;
}

NS_YH_END
