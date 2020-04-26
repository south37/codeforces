#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string.h>
#include <set>
#include <unordered_map>
#include <vector>

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
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int gcd(int a, int b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

void solve() {
  ll a, b, q;
  cin >> a >> b >> q;
  if (a < b) {
    swap(a, b);
  }
  // Here, a >= b
  ll gg = gcd(a, b);
  ll aa = a/gg;
  ll bb = b/gg;
  // Here, aa and bb are prime
  ll g = aa*bb*gg;

  // cout << "a: " << a << endl;
  // cout << "b: " << b << endl;
  // cout << "g: " << g << endl;
  // cout << "x: " << x << endl;

  rep(iter, q) {
    ll l, rr;
    cin >> l >> rr;
    vector<ll> ans(2);
    vector<ll> rng(2);
    rng[0] = l-1;
    rng[1] = rr;
    rep(k, 2) {
      ll v = rng[k];

      ll cnt = v / g;
      ll res = (a-1) + cnt*a - max(0ll, (g*cnt+a-1) - v);
      ans[k] = res;
    }
    cout << (rng[1]-rng[0]) - (ans[1] - ans[0]);
    if (iter < q-1) {
      cout << " ";
    }
  }
  cout << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
