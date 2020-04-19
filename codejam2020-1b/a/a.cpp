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

bool xChanged = false;
bool yChanged = false;

void printw() {
  if (xChanged) {
    cout << "E";
  } else {
    cout << "W";
  }
}
void printe() {
  if (xChanged) {
    cout << "W";
  } else {
    cout << "E";
  }
}
void printn() {
  if (xChanged) {
    cout << "S";
  } else {
    cout << "N";
  }
}
void prints() {
  if (xChanged) {
    cout << "N";
  } else {
    cout << "S";
  }
}

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
string pattern = "EWNS";

void printone(int x, int y) {
  if (x == 1) {
    cout << "E" << endl;
  } else if (x == -1) {
    cout << "W" << endl;
  } else if (y == 1) {
    cout << "N" << endl;
  } else {
    cout << "S" << endl;
  }
}

void solve() {
  ll x, y;
  cin >> x >> y;
  // try all case
  ll s = abs(x) + abs(y);
  if (s == 1) {
    printone(x, y);
    return;
  }
  vector<ll> nums;
  ll n = 1;
  while (n < s) {
    nums.push_back(n);
    n *= 2;
  }
  // Here, n >= s
  // n /= 2;
  // printvec(nums);

  // Here, we try all case of nums
  ll m = nums.size();
  rep(i, 1ll<<m) {
    rep(j, 1ll<<m) {
      ll xx = 0;
      ll yy = 0;
      string ps;
      // Here, i and j represents pattern
      rep(k, m) {
        ll dir = 0;
        if (i & 1ll<<k) {
          dir += 1;
        }
        if (j & 1ll<<k) {
          dir += 2;
        }
        // cout << "dir: " << dir << endl;
        // Here, dir is 0-3
        xx += (1ll<<k) * dx[dir];
        yy += (1ll<<k) * dy[dir];
        ps += pattern[dir];
      }
      // cout << "xx: " << xx << endl;
      // cout << "yy: " << yy << endl;
      // cout << "ps: " << ps << endl;
      if (xx == x && yy == y) {
        cout << ps << endl;
        return;
      }
    }
  }
  cout << "IMPOSSIBLE" << endl;
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
    solve();
  }
}
