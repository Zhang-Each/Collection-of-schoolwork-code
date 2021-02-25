#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int constant = 1000000007;
const int radication = 31623;

int quick_power(int k); /*To caculate 2^k mod 1000000007 fastly. */
int quick_mul(int a, int b); /*To caculate a*b mod 1000000007 fastly. */
int quick_square(int a); /* To caculate a^2 mod 1000000007 fastly. */

int main()
{
    int n, m, i, j;
    cin >> n >> m;
    vector<int>num(n + 1); /* To store the numbers of the original sequence. */
    vector<int>result(n + 1, 0); /* To store the result of the subsequence from the 1-st element to the i-th element. */
    for(i = 1; i <= n; i++) {
        cin >> num[i];
    }
    for(i = 2; i <= n; i++) {
	unsigned int include_i = 0; /* Variable 'include_i' is to caculate the number of the subsequences which is no longer a beautiful subsequence without the i-th element. */
	for(j = 1; j < i; j++) {
	    if(abs(num[i] - num[j]) <= m) include_i += quick_power(j - 1) + result[j - 1] - result[j]; /* For every element whose index is smaller than the i-th element and difference between which and the i-th element is no larger than m, the number of the beautiful subsquences which is made a beautiful subsquence by the i-th element and the j-th element equals to the number of the non-beautiful subsquences minors (result[j] - result[j - 1]). */
	    include_i %= constant;
	}
	result[i] = 2 * result[i - 1] + include_i; /* 'result[i]' equals two times of result[i - 1] plus the the number of the subsequences which is no longer a beautiful subsequence without the i-th element. */
	if(result[i] >= constant) result[i] %= constant;
    }
    cout << result[n] << endl;
    //cout << quick_power(1000) - n - 1 << endl;
    return 0;
}

int quick_power(int k)
{
    int result = 1, n = 2;
    while(k > 0) {
	if(k % 2 == 1) result = quick_mul(result, n);
	k /= 2;
	if(n >= radication) n = quick_square(n);
	else n = n * n;
    }
    result %= constant;
    return result;
}

int quick_mul(int a, int b)
{
    if(a < b) return quick_mul(b, a);
    else if(a == b) return quick_square(a);
    int x, y, result;
    if((a + b) % 2 == 0) {
	x = (a + b) / 2;
	y = (a - b) / 2;
	result = quick_square(x) - quick_square(y);
    }
    else {
	x = (a + b) / 2;
	y = (a - b) / 2;
	result = quick_square(x) - quick_square(y) + b;
    }
    if(result < 0) result += constant;
    return result % constant;
}

int quick_square(int a)
{
    int t = a / radication;
    int p = a % radication;
    int temp1_t = t * t / 70812;
    int temp1_p = t * t % 70812;
    int temp1 = (7057 * temp1_t + 14122 * temp1_p) % constant;
    temp1 = (temp1 + p * p) % constant;
    int temp2, temp2_t, temp2_p;
    temp2_t = 2 * t * p / radication;
    temp2_p = 2 * t * p % radication;
    temp2 = (14122 * temp2_t + radication * temp2_p) % constant;
    a = temp1 + temp2;
    a %= constant;
    return a;
}
