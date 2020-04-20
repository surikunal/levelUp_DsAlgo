#include <iostream>
#include <vector>
using namespace std;

void KthOFFtoON(int &n, int k)
{
    int mask = (1 << k);
    n |= mask;
}

void KthONtoOFF(int &n, int k)
{
    int mask = (~(1 << k));
    n &= mask;
}

int countNumOfSetBits(int num)
{
    int count = 0;
    int totalBits = 32;
    while (num != 0 && totalBits != 0)
    {
        if ((num & 1) != 0)
        {
            count++;
        }
        num >>= 1;
        totalBits--;
    }
    return count;
}

int countBits(int num)
{
    int count = 0;
    while (num != 0)
    {
        count++;
        num &= (num - 1);
    }
    return count;
}

void set1()
{
    int n = 45;
    int k = 3;
    KthOFFtoON(n, k);
    cout << n << endl;
    KthONtoOFF(n, k);
    cout << n << endl;

    cout << countNumOfSetBits(n) << endl;
    cout << countBits(n) << endl;
}

// 191
int hammingWeight(uint32_t num)
{
    int count = 0;
    while (num != 0)
    {
        num &= (num - 1);
        count++;
    }
    return count;
}

void set2()
{
    /* leetcode */
    // 191
    // cout << hammingWeight(00000000000000000000000000001011) << endl;

    // 338


    // 137
    
}

void solve()
{
    // set1();
    set2();
}

int main(int args, char **argv)
{
    solve();
    return 0;
}