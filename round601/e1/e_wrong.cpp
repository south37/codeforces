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

void solve() {
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  vector<ll> indices;
  rep(i, n) {
    if (a[i] == 1) {
      indices.push_back(i);
    }
  }
  ll m = indices.size();
  if (m == 0) { // no 1
    cout << 0 << endl;
    return 0;
  }

  if (m == 1) {
    cout << -1 << endl;
    return 0;
  }

  // We want to calculate the minimum divisor k.
  ll i = 2;
  ll maximum_divisor = -1;
  while (i * i <= m) {
    if (m % i == 0) {
      maximum_divisor = i;
    }
    ++i;
  }
  if (maximum_divisor == -1) { // n is prime
    maximum_divisor = m;
  }

  // Now, we have maximum_divisor. We calculate from end.
  ll ans = 0;
  ll j = 0;
  while (j < indices.size()) {
    rep(iter, maximum_divisor - 1) {
      ans += indices[j + maximum_divisor - 1]  - indices[j + iter];
    }
    j += maximum_divisor;
  }

  cout << ans << endl;
  return 0;
}
