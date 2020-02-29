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
    while (i) {
      d[i] += x;
      i -= i&-i;
    }
  }
  T sum(ll i) {
    T x = 0;
    while (i <= n) {
      x += d[i];
      i += i&-i;
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
  string as, bs, s;
  cin >> as;
  cin >> bs;
  cin >> s;

  vector<ll> z_a = build_z(s + '#' + as);
  reverse(all(bs));
  reverse(all(s));
  vector<ll> z_b = build_z(s + '#' + bs);
  // printvec(z1);
  // printvec(z2);

  vector<ll> a(n+1);
  vector<ll> b(n+1);

  for (int i = 1; i <= n; ++i) {
    a[i] = min(m-1, z_a[i+m]);
    b[i] = min(m-1, z_b[n+m-i+1]);
  }

  BIT<ll> bit1(m);
  BIT<ll> bit2(m);

  ll ans = 0;
  for (int i = 1; i <= n; ++i){
    if (a[i]) {
      bit1.add(a[i], a[i]);
      bit2.add(a[i], 1);
    }
    if (i >= m&& a[i-m+1]) {
      bit1.add(a[i-m+1],-a[i-m+1]);
      bit2.add(a[i-m+1],-1);
    }
    if (b[i]) {
      ans += bit1.sum(m-b[i]) + (b[i]-m+1) * bit2.sum(m-b[i]);
    }
  }
  cout << ans << endl;
  return 0;
}
