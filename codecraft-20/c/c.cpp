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

  ll n, m, p;
  scanf("%lld", &n);
  scanf("%lld", &m);
  scanf("%lld", &p);
  // cin >> n >> m >> p;
  vector<ll> a(n);
  vector<ll> b(m);
  rep(i, n) {
    scanf("%lld", &a[i]);
    // cin >> a[i];
  }
  rep(i, m) {
    scanf("%lld", &b[i]);
    // cin >> b[i];
  }

  // printvec(a);
  // printvec(b);

  ll a_zero = 0;
  rep(i, n) {
    if (a[i] % p == 0) { // continue
      ++a_zero;
    } else {
      break;
    }
  }
  ll b_zero = 0;
  rep(i, m) {
    if (b[i] % p == 0) { // continue
      ++b_zero;
    } else {
      break;
    }
  }

  // Here, we calculated a0 and b0
  cout << a_zero + b_zero << endl;
}
