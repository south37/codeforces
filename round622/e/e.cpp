// ref. https://codeforces.com/contest/1313/submission/71676206
// ref. https://codeforces.com/contest/1313/submission/71681170

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

vector<ll> build_z(const string& s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = -1, r = -1;
  for (int i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<ll>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  ll n;
  vector<T> d;
  BIT(ll n=0) : n(n), d(n+1) {}
  void add(ll i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  T sum(ll i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // 24
//   cout << bit.sum(9) << endl; // 55
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  string a, b, s;
  cin >> a;
  cin >> b;
  cin >> s;

  vector<ll> z_a = build_z(s + '#' + a);
  reverse(all(b));
  reverse(all(s));
  vector<ll> z_b = build_z(s + '#' + b);
  vector<ll> dpa(n); // dpa[i] .. the length of common prefix of a[i, n] and s[1,m-1]
  vector<ll> dpb(n); // dpb[i] .. the length of common suffix of b[1, i] and s[2,m]
  rep(i, n) {
    dpa[i] = z_a[m+1+i];
    dpb[i] = z_b[m+1+(n-1-i)];
    dpa[i] = min<ll>(dpa[i], m-1);
    dpb[i] = min<ll>(dpb[i], m-1);
  }
  BIT<ll> bit1(n);
  BIT<ll> bit2(n);
  // m-dpb[i] > a <=> m-dpb[i]-a > 0
  ll ans = 0; // the sum of sigma_l1 sigma_r2 max(a[l1] + dpb[r2] - m + 1, 0)
  rep(i, n) {
    if (dpa[i]) {
      bit1.add(dpa[i], dpa[i]);
      bit2.add(dpa[i], 1);
    }
    if (i >= m && dpa[i-m]) {
      bit1.add(dpa[i-m], -dpa[i-m]);
      bit2.add(dpa[i-m], -1);
    }
    if (dpb[i]) {
      ans += bit1.sum(m-dpb[i]-1) + (dpb[i]-m+1) * bit2.sum(m-dpb[i]-1);
    }
  }
  cout << ans << endl;
}
