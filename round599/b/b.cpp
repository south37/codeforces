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

void solve() {
  ll n;
  cin >> n;
  string s, t;
  cin >> s;
  cin >> t;
  ll cnt = 0; // mistake
  rep(i, n) {
    if (s[i] != t[i]) { ++cnt; }
  }
  if (cnt == 0) {
    cout << "Yes" << endl;
    return;
  }
  if (cnt == 2) {
    ll i1 = -1;
    ll i2 = -1;
    rep(i, n) {
      if (s[i] != t[i]) {
        if (i1 == -1) {
          i1 = i;
        } else {
          i2 = i;
        }
      }
    }

    // Now, we compare s[i1], t[i1], ..
    // s[i1] <=> t[i2]
    if (s[i1] == s[i2] && t[i1] == t[i2]) {
      cout << "Yes" << endl;
      return;
    } else {
      cout << "No" << endl;
      return;
    }
  }

  cout << "No" << endl;;
  return;
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
