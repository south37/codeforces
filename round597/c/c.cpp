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

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};

// Combination mod prime.
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct Combination {
  vector<mint> fact, ifact;
  Combination(int n) { init(n); }
  void init(int n) {
    assert(n < MOD); // n must be lower than MOD.

    fact.resize(n + 1);
    ifact.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) { fact[i] = fact[i-1] * i; }
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) { ifact[i-1] = ifact[i] * i; }
  }
  mint operator() (int n, int k) const {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[k] * ifact[n-k];
  }
  mint perm(int n, int k) const {
    if (k < 0 || k > n) { return 0; }
    return fact[n] * ifact[n-k];
  }
};

Combination c(0);
ll n;


//  - pattern of numbers ([n/2, n])
//    - l = 3, r = 6
//    - 3, 4, 5, 6 (left is 切り上げ)
//    - 3: [w, w, w] -> 1 pattern (3C3) i = l, l + 0,
//    - 4: [w, w, u, u] -> 6 pattern (4C2) i = l + 1, l - i
//    - 5: [w, u, u, u, u] -> 5 pattern (5C1)
//    - 6: [u, u, u, u, u, u] -> 1 pattern (6C0)
mint f(ll x) {
  ll l = (x+1)/2;

  mint res(0);
  // We search [l, x]
  for (int i = l; i <= x; ++i) {
    res += c(i, x - i);
  }
  return res;
}

// int main(int argc, char** argv) {
//   MOD = 13;
//
//   Combination c(12);
//   cout << c(12, 0).x << endl;  // 1  = 1 % 13
//   cout << c(12, 1).x << endl;  // 12 = 12 % 13
//   cout << c(12, 2).x << endl;  // 1  = 66 % 13 = (12 * 11 / 2) % 13
//   cout << c(12, 3).x << endl;  // 12 = 220 % 13 = (12 * 11 * 10 / (3 * 2 * 1)) % 13
//   cout << c(12, 11).x << endl; // 12 = 12 % 13
//   cout << c(12, 12).x << endl; // 1  = 12 % 13
//
//   cout << c.perm(12, 3).x << endl; // 7 = 12 * 11 * 10 % 13
// }

int main(int argc, char** argv) {
  string s;
  cin >> s;
  n = s.size();

  c.init(n);

  vector<ll> sequences;

  ll seq_len = 1;
  rep(i, n-1) {
    if ((s[i] == 'm') || (s[i] == 'w')) {
      cout << 0 << endl;
      return 0;
    }
    if ((s[i+1] == 'm') || (s[i+1] == 'w')) {
      cout << 0 << endl;
      return 0;
    }

    if (s[i] == s[i+1]) {
      ++seq_len;
    } else { // s[i] != s[i+1]
      if (seq_len > 1) {
        if ((s[i] == 'u') || (s[i] == 'n')) { // we consider only u or n
          sequences.push_back(seq_len);
        }
      }
      seq_len = 1;
    }
  }
  if (seq_len > 1) {
    if ((s[n-1] == 'u') || (s[n-1] == 'n')) { // we consider only u or n
      sequences.push_back(seq_len);
    }
  }

  // For Debug
  // cout << "sequences: " << endl;
  // for (auto x : sequences) {
  //   cout << x << " ";
  // }
  // cout << endl;

  if (sequences.size() == 0) {
    cout << 1 << endl;
    return 0;
  }

  // Here, sequences have counts.
  // we want to calculate the answer.
  mint ans(1);
  for (auto x : sequences) {
    ans *= f(x);
  }
  cout << ans.x << endl;
}
