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

// - a: r 0 (beats s 2)
// - b: p 1 (beats r 0)
// - c: s 2 (beats p 1)
//
// - here, we map r, p, s to 0, 1, 2
//   - 0 > 2
//   - 1 > 0
//   - 2 > 1
//
// a = cnt[0] // r
// b = cnt[1] // p
// c = cnt[2] // s
//
// b_cnt // the count of bob.
//
// cnt[0] <-> b_cnt[2] : alice 2, bobe 1 (alice win)
// cnt[1] <-> b_cnt[0] : alice 2, bobe 1 (alice win)
// cnt[2] <-> b_cnt[1] : alice 2, bobe 1 (alice win)

void solve() {
  ll n;
  cin >> n;
  ll a, b, c;
  cin >> a >> b >> c;
  string s;
  cin >> s;
  vector<ll> cnt(3);
  cnt[0] = a; cnt[1] = b; cnt[2] = c;

  vector<ll> b_cnt(3);
  rep(i, n) {
    if (s[i] == 'R') {
      ++b_cnt[0];
    } else if (s[i] == 'P') {
      ++b_cnt[1];
    } else if (s[i] == 'S') {
      ++b_cnt[2];
    } else { // invalid case
      cout << "Wrong!" << endl;
      return;
    }
  }

  vector<ll> w(3); // The count of wins by alice.
  w[0] = min(cnt[0], b_cnt[2]); // alice wins by r==0, bob is s==2
  w[1] = min(cnt[1], b_cnt[0]); // alice wins by p==1, bob is r==0
  w[2] = min(cnt[2], b_cnt[1]); // alice wins by s==2, bob is p== 1

  vector<ll> rest(3); // The count of loses by alice.
  rest[0] = cnt[0] - w[0];
  rest[1] = cnt[1] - w[1];
  rest[2] = cnt[2] - w[2];
  string rest_s;
  rep(i, rest[0]) { rest_s += 'R'; }
  rep(i, rest[1]) { rest_s += 'P'; }
  rep(i, rest[2]) { rest_s += 'S'; }

  // For Debug
  // cout << "rest_s: " << rest_s << endl;
  ll rest_i = 0; // index for rest

  ll sum_w = w[0] + w[1] + w[2];
  if (sum_w >= (n + 1)/2) {
    cout << "YES" << endl;
    rep(i, n) {
      if ((s[i] == 'R') && (w[1] > 0)) { // bob is r==0, alice should be p==1
        cout << 'P';
        --w[1];
      } else if ((s[i] == 'P') && (w[2] > 0)){ // bob is p ==1, alice should be s==2
        cout << 'S';
        --w[2];
      } else if ((s[i] == 'S') && (w[0] > 0)) { // bob is s==2, alice should be r==0
        cout << 'R';
        --w[0];
      } else {
        cout << rest[rest_i];
        ++rest_i;
      }
    }
    cout << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
