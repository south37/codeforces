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
  ll n, k;
  cin >> n >> k;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  ll ans = 0;
  map<ll, ll> mp; // remain => count.
  rep(i, n) {
    // cout << a[i] << ": ";

    if (a[i] == 1) {
      ans += mp[1];
      ++mp[1];
    } else {
      map<ll, ll> pf; // prime factor => count
      ll l = 2;
      while (l * l <= a[i]) {
        while (a[i] % l == 0) {
          ++pf[l];
          a[i] /= l;
        }
        ++l;
      }
      if (a[i] > 1) {
        ++pf[a[i]];
      }

      ll b = 1; // The remaining. e.g. 3**1 -> 3**1
      ll c = 1; // The other side of remaining. e.g. 3**1 -> 3**(k-1)
      for (auto x : pf) {
        if (x.second % k == 0) { continue; }
        ll remain = x.second % k;
        rep(i, remain) { b *= x.first; }
        rep(i, k - remain) { c *= x.first; }
      }
      // If a[i] is j**k, then b = 1 and c = 1.
      ans += mp[c];
      ++mp[b];
    }
  }

  cout << ans << endl;
}
