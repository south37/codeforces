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

void solve() {
  ll x, y;
  cin >> x >> y;
  if ((x+y) % 2 == 0) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  xChanged = false;
  yChanged = false;
  // Here, x+y is odd
  if (x < 0) {
    x *= -1;
    xChanged = true;
  }
  if (y < 0) {
    y *= -1;
    yChanged = true;
  }
  // Here, x >= 0 && y >= 0

  ll s = x+y;
  // cout << "s:" << s << endl;

  ll n = 1;
  while (n < s) {
    n *= 2;
    //cout << "n:" << n << endl;
  }
  // Here, n >= s and n is 2^k
  if (s != 1) {
    n /= 2;
  }
  // cout << "n:" << n << endl;

  // Here, n < s
  // we use until n
  vector<ll> nums;
  ll sum = 0;
  {
    ll i = 1;
    while (i <= n) {
      nums.push_back(i);
      sum += i;
      i *= 2;
    }
    // Here, i == n*2
  }
  // cout << "nums: "; printvec(nums);

  ll diff = (sum - s) / 2;
  // cout << "diff:" << diff << endl;

  // we make diff
  ll m = nums.size();
  vector<bool> minuses(m);
  // cout << "m: " << m << endl;
  for (int i = m-1; i >= 0; --i) {
    // cout << "i: " << i << endl;
    if (diff >= nums[i]) {
      diff -= nums[i];
      nums[i] *= -1;
      minuses[i] = true;
    }
  }
  // Here, minuses is calculated
  // cout << "nums: "; printvec(nums);
  // cout << "minuses: "; printvec(minuses);

  bool found = false;
  ll pattern = -1;
  // We want to make x from nums and minuses
  rep(i, 1ll<<m) {
    ll nowx = 0;
    rep(j, m) {
      if (i & 1ll<<j) {
        nowx += nums[j];
      }
    }
    // cout << "nowx: " << nowx << endl;
    if (x == nowx) {
      found = true;
      pattern = i;
      break;
    }
  }

  if (!found) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  // print result
  rep(i, m) {
    if (pattern & 1ll<<i) { // x
      if (minuses[i]) {
        printw();
      } else {
        printe();
      }
    } else {
      if (minuses[i]) {
        prints();
      } else {
        printn();
      }
    }
  }
  cout << endl;
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
