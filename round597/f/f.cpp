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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// The number of integers y where (0 <= y < b) and (a+y = a^y)
//
// g(a,b) = h(a,b) + g(x,b-lsb(b))
// h(a,b): the number of integers y where (b-lsb(b) <= y < b) and (a+y=a^y)
ll g(ll a, ll b) {
  ll ret = 0;
  ll zeroes = 0; // number of 0-bits in lower log(i) bits of a.

  for (ll i = 1; i <= b; i <<= 1) {
    if (b & i) {
      b ^= i; // Set 0 to log(i)-bit of b.
      if (!(a & b)) {
        ret += 1 << zeroes;
      }
    }

    if (!(a&i)) {
      ++zeroes;
    }
  }
  return ret;
}

// - f(0,r) = 2r - 1 + f(1,r)
// - f(2l,2r) = 3f(l,r)
// - f(l,r) = f(l+1,r) + 2(g(l,r)-g(l,l)) if l is odd
// - f(l,r) = f(l,r-1) + 2(g(r-1,r)-g(r-1,l)) if r is odd
ll rec(ll a, ll b) {
  if (a == b) { return 0; }
  if (a == 0) {
    return 2 * b - 1 + rec(1, b);
  }

  ll ret = 0;
  if (a & 1) {
    ret += 2 * (g(a, b)-g(a, a));
    ++a;
  }
  if (b & 1) {
    ret += 2 * (g(b-1, b)-g(b-1,a));
    --b;
  }
  return ret + 3 * rec(a/2, b/2);
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    ll a, b;
    cin >> a >> b;
    cout << rec(a, b+1) << endl;
  }
}
