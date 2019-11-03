#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  string s;
  cin >> s;
  ll n = s.size();

  // Check w and m
  rep(i, n) {
    if (s[i] == 'w' || s[i] == 'm') {
      cout << 0 << endl;
      return 0;
    }
  }

  vector<ll> fib(n+1);
  fib[0] = 1; fib[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fib[i] = (fib[i-1] + fib[i-2]) % MOD;
  }

  ll ans = 1;
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && s[j] == s[i]) {
      ++j;
    }
    // Now, j-i is the length of same caracters with s[i].
    if (s[i] == 'u' || s[i] == 'n') {
      ans *= fib[j-i];
      ans %= MOD;
    }
  }

  cout << ans << endl;
}
