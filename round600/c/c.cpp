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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  sort(all(a));
  // cout << "a: "; printvec(a);
  // Now, a is sorted in increasing order.
  // We want to select first k. But, we eat each by m in decreasing order.

  // We want to pre-calculate "each m" summention.

  vector<ll> s(n+1); // summention. s[i] .. sum of [0, i)
  rep(i, n) {
    s[i+1] = s[i] + a[i];
  }
  // cout << "s: "; printvec(s);

  // Now, diff[i] = s[i+1] - s[i+1-m]. diff[i] = 0 if i <= ...
  vector<ll> diff(n, 0);
  rep(i, n) {
    if (i+1-m >= 0) {
      diff[i] = s[i+1] - s[i+1-m];
    } else {
      diff[i] = s[i+1]; // i+1-m is lower, so we treat them as 0
    }
  }
  // cout << "diff: "; printvec(diff);

  vector<ll> diff_sum(n); // The summention.
  rep(i, m) { // count in each m
    ll d = 0;
    while (i + d * m < n) {
      if (d >= 1) {
        diff_sum[i + d * m] = s[i + d * m + 1] + diff_sum[i + (d-1) * m];
      } else {
        diff_sum[i + d * m] = diff[i + d * m];
      }
      ++d;
    }
  }
  // cout << "diff_sum: "; printvec(diff_sum);

  rep(k, n) {
    cout << diff_sum[k] << " ";
  }
  cout << endl;
}
