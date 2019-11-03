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
  ll n;
  cin >> n;
  ll a, b, c;
  cin >> a >> b >> c;
  string s;
  cin >> s;
  vector<ll> cnt(3);

  ll A = 0, B = 0, C = 0;
  rep(i, n) {
    if (s[i] == 'R') {
      ++A;
    } else if (s[i] == 'P') {
      ++B;
    } else { // 'S'
      ++C;
    }
  }

  ll w = min(a, C) + min(b, A) + min(c, B);
  if (2 * w < n) {
    cout << "NO" << endl;
    return;
  }

  cout << "YES" << endl;
  string t;
  rep(i, n) {
    if (s[i] == 'S' && a) { // R > S
      --a;
      t += 'R';
    } else if (s[i] == 'R' && b) { // P > R
      --b;
      t += 'P';
    } else if (s[i] == 'P' && c) { // S > P
      --c;
      t += 'S';
    } else {
      t += '_';
    }
  }
  // Set rest to _ in t.
  rep(i, n) {
    if (t[i] == '_') {
      if (a) {
        --a;
        t[i] = 'R';
      } else if (b) {
        --b;
        t[i] = 'P';
      } else {
        --c;
        t[i] = 'S';
      }
    }
  }
  cout << t << endl;
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
