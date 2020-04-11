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

void solve() {
  ll n;
  cin >> n;
  // Here, we calculate all case.
  // start from (0, 0). (n, k) is nCk.

  if (n == 1) {
    cout << "1 1" << endl;
    return;
  } else if (n == 2) {
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    return;
  } else if (n == 3) {
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    cout << "3 1" << endl;
    return;
  } else { // n >= 4
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    cout << "3 2" << endl; // (2, 1)
    ll remain = n - 4;
    // Here, our position is (2, 1)
    // start from here, and increment in greedy way
    ll r = 2;
    while (remain > 0) {
      // Here, we do "(r, 1)" pair. It is rC1 = r.
      ++r;
      if (remain >= r) {
        remain -= r;
        cout << r + 1 << " " << 2 << endl;
      } else { // reached to small remaining
        break;
      }
    }
    --r; // decrease.
    // Here, we do small remaining
    while (remain > 0) {
      cout << r + 1 << " " << 1 << endl; // (r, 0)
      --remain;
      ++r;
    }
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    cout << "Case #" << (i+1) << ": ";
    cout << endl;
    solve();
  }
}
