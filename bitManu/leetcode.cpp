#include <iostream>
#include <vector>
using namespace std;

// 191.======================================
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

// 137.=======================================

//* time:O(32n)  space:O(1)
int singleNumber(vector<int> &nums)
{
    int result = 0;
    int x, sum;
    // Iterate through every bit
    for (int i = 0; i < 32; i++)
    {
        // Find sum of set bits at ith position in all
        // array elements
        sum = 0;
        x = (1 << i);
        for (int j = 0; j < nums.size(); j++)
        {
            if (nums[j] & x)
                sum++; // counting num of bits...so it should be multiple of 3 for all numbers which are repeating thrice

            // if (!sum % 3) // only true for sum = 1 and 2 (and sum will never be 2)
            // when sum is not multiple of 3 then it means the num is appearing only once so we ON all its bits which make it that num
            //* but using this condition will not going to work for -ve numbers
        }
        result = result | ((sum % 3) << i);
    }
    return result;
}

// 260. ================================================

class Solution
{
public:
    /* here what is happening 
    let:
    Input:  [1,2,1,3,2,5]
    Output: [3,5]

        first we are taking xor of all so we get xor of 3 and 5

        then the fact is that 
        to find first bit from left which is different for both nums , we do AND of a num and of its -ve    (shown below)
        3 --> 011
        5 --> 101

        firstLSB --> 010    (we get first bit which is different)

        now we are traversing it again a taking AND of firstLSB with every number
        and if it gives 1 then put it in one variable and if 0 then put it in other varible
        
        so that all same nums come in one variable
        and both unique nums in different varibles

        now taking or of all these numbers will cancel the same num and 
        2 unique nums will come in diiferent variables
     */
    vector<int> singleNumber(vector<int> &nums)
    {
        int xorNum = 0;
        for (int ele : nums)
        {
            xorNum ^= ele;
        }
        // to find first ON bit from left size we do this...called LSB
        int firstLSB = ((xorNum & (-xorNum)));

        int a = 0;
        int b = 0;
        for (int ele : nums)
        {
            if ((firstLSB & ele) != 0)
                a ^= ele;
            else
                b ^= ele;
        }
        return {a, b}; // java: new int[] {a, b};
    }
};

// 231. ==========================================================

class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

// 342. ==========================================================

class Solution
{
public:
    bool isPowerOfFour(int num)
    {
        if (num > 0 && !(num & (num - 1))) // is num power of 2
        {
            int count = 0;
            while (num > 1)
            {
                count++; // count all zeros after 1
                num >>= 1;
            }

            if ((count & 1) == 0) // count of 0 after 1 should be even num
                return true;
        }
        return false;
    }
};