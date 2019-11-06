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

int main(int argc, char** argv) {
  ll n;
  cin >> n;
  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }

  set<ll> pf;
  ll i = 2;
  while (i * i <= n) {
    while (n % i == 0) {
      pf.insert(i);
      n /= i;
    }
    ++i;
  }
  if (n > 1) {
    pf.insert(n);
  }
  // We should consider only prime factors.
  if (pf.size() == 1) {
    if (*pf.begin() == n) { // only itself. n is prime
      cout << n << endl;
      return 0;
    } else { // pf has the only 1 prime factor. e.g. 8 -> 2. 9 -> 3.
      cout << *pf.begin() << endl;
      return 0;
    }
  }

  // if (pf.size == 2) {
  //   auto iter = *pf.begin();
  //   ll a = *iter;
  //   ++iter;
  //   ll b = *iter;
  //   // Now, a and b are the prime factors of pf.
  // }
  cout << 1 << endl;
  return 0;
}
