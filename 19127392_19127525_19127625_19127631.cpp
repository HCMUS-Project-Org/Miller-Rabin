#include <iostream>
#include <time.h>

using namespace std;

long power_mod(long long b, long e, long m)
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
      // b overflew before calc modular, so use long long for base.
      b = b * b % m;
      e >>= 1;
   }

   return result;
}

void parse_n(long long n, int &k, long long &m)
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

bool miller_rabin(long long n)
{
   // input: n
   // output: true/false

   // check if n even or = 2
   if (n == 2)
      return true;
   else if (n < 2 || n % 2 == 0)
      return false;

   int k = 0;
   long long m = 0;

   // parse n = 2^k*m + 1
   parse_n(n, k, m);

   // pick random a (1, n-1)
   long long a = rand() % (n - 1) + 1;
   long long b = power_mod(a, m, n);

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

   long long n;
   string input;
   cout << "-------------------------------------------------" << endl;
   cout << "--                 Miller Rabin                --" << endl;
   cout << "--         ---------------------------         --" << endl;
   cout << "--  19127392 - 19127525 - 19127625 - 19127631  --" << endl;
   cout << "-------------------------------------------------" << endl;

   while (true) {
      cout << "\n> Input n:";
      // Flush input to prevent infinity loop
      cin >> n;
      cin.clear();
      fflush(stdin);
      if (n < 0) {
        cout << "Input number should be a positive one" << endl;
        continue;
      }
      bool ML = miller_rabin(n);
      if (ML == true)
        // if the result is different from the input -> overflow
        cout << n << " is prime";
      else
        cout << n << " is not prime";

      cout << endl;
   };

   return 0;
}
