#include <iostream>
#include <time.h>

using namespace std;

long power_mod(long long b, long e, long m)
{
    // input: b (base), e (exponent), m (modulus)
    // output: b^e mod m

    // case wrong:
    // b = 20642
    // e = 649913
    // m = 1299827
    // expect: 1299826 - calc by: https://www.mtholyoke.edu/courses/quenell/s2003/ma139/js/powermod.html
    // result: 1078532

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

void parse_n(int n, int& k, int& m)
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

    // check if n even or = 2
    if (n == 2)
        return true;
    else if (n < 2 || n % 2 == 0)
        return false;

    int k = 0, m = 0;

    // parse n = 2^k*m + 1
    parse_n(n, k, m);

    // pick random a (1, n-1)
    long a = rand() % (n - 1) + 1;
    long b = power_mod(a, m, n);

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

    /*while (true) {
        cout << "\n> Input n:";
        cin >> n;

        bool ML = miller_rabin(n);
        if (ML == true)
            cout << n << " is prime";
        else
            cout << n << " is not prime";
    }*/

    cout << power_mod(20642, 649913, 1299827)<<endl;

    return 0;
}
