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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

void solve() {
  ll n, k, d;
  cin >> n >> k >> d;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  map<ll, ll> m;

  // We want to get th minimum cnt
  // We check [i, i+d-1] in each step. i is [0, n-d]
  rep(i, d) {
    ++m[a[i]];
  }
  ll cnt = m.size();
  ll min_cnt = cnt;

  // we already checked [0, d-1]
  ll r = d;
  while (r < n) {
    ll l = (r - d + 1);  // e.g. if r = d, then l = 1. we check [l, r]
    // Now, check [l, r]

    ++m[a[r]];
    if (m[a[r]] == 1) { // Just added
      ++cnt;
    }

    --m[a[l-1]];
    if (m[a[l-1]] == 0) { // Just erased
      --cnt;
    }

    if (cnt < min_cnt) {
      min_cnt = cnt;
    }

    ++r;
  }

  cout << min_cnt << endl;
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
