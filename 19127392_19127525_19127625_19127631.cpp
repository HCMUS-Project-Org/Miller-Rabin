#include <iostream>
#include <time.h>

using namespace std;

long power_mod(long b, long e, long m)
{
   // input: b (base), e (exponent), m (modulus)
   // output: b^e mod m

   b %= m;
   long result = 1;
   while (e > 0)
   {
      // Check odds
      if (e & 1)
      {
         result = result * b % m;
      }
      b = b * b % m;
      e >>= 1;
   }

   return result;
}

void parse_n(int n, int &k, int &m)
{
   n = n - 1;

   // while n even
   while (n % 2 == 0)
   {
      k++;
      n = n / 2;
   }
   m = n;
}

bool miller_rabin(long n)
{
   // input: n
   // output: true/false
   int k = 0, m = 0;

   // parse n = 2^k*m + 1
   parse_n(n, k, m);

   // pick random a (1, n-1)
   int a = rand() % (n - 1) + 1;
   cout << "a:" << a << endl;
   long b = power_mod(a, m, n);
   cout << "b:" << b << endl;

   if (b % n == 1)
      return true;

   for (int i = 0; i < k; i++)
   {
      if (b % n == n - 1)
         return true;
      b = power_mod(b, 2, n);
   }

   return false;
}

int main()
{
   srand(time(NULL));

   long n;
   cout << "-------------------------------------------------" << endl;
   cout << "--                 Miller Rabin                --" << endl;
   cout << "--         ---------------------------         --" << endl;
   cout << "--  19127392 - 19127525 - 19127625 - 19127631  --" << endl;
   cout << "-------------------------------------------------" << endl;

   // cout << "> Input n:";
   // cin >> n;

   // bool ML = miller_rabin(n);
   // if (ML == true)
   //    cout << n << " is prime";
   // else
   //    cout << n << " is not prime";
   for (int i = 0; i < 1000; i++)
   {
      cout << i << ": " << miller_rabin(i) << endl;
      if (i % 100 == 0)
         cout << "-------------" << endl;
   }

   return 0;
}
