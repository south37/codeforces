// ref. https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fef2/U251a2U

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

const ll M = 1e9;

string check(ll x, ll y) {
  cout << x << " " << y << endl;
  string res;
  cin >> res;
  return res;
}

bool finish = false;
bool f(ll x, ll y) {
  if (finish) { return true; }
  string res = check(x, y);
  if (res == "CENTER") {
    finish = true;
    return true;
  }
  if (res == "HIT") { return true; }
  return false;
}

void solve() {
  finish = false;
  for (ll sx = -M/2; sx <= M/2; sx += M/2) {
    for (ll sy = -M/2; sy <= M/2; sy += M/2) {
      if (f(sx, sy)) { // hit
        ll lx, ly, rx, ry;
        {
          ll l = -M-1, r = sx;
          while (r-l>1) {
            ll c = (l+r)/2;
            if (f(c,sy)) { r = c; } else { l = c; }
          }
          lx = r; // left boundary of hit
        }
        {
          ll l = sx, r = M+1;
          while (r-l>1) {
            ll c = (l+r)/2;
            if (f(c,sy)) { l = c; } else { r = c; }
          }
          rx = l; // right boundary of hit
        }
        {
          ll l = -M-1, r = sy;
          while (r-l>1) {
            ll c = (l+r)/2;
            if (f(sx,c)) { r = c; } else { l = c; }
          }
          ly = r; // bottom boundary of hit
        }
        {
          ll l = sy, r = M+1;
          while (r-l>1) {
            ll c = (l+r)/2;
            if (f(sx,c)) { l = c; } else { r = c; }
          }
          ry = l; // top boundary of hit
        }
        f ((lx+rx)/2, (ly+ry)/2); // shoot to center
        return;
      }
    }
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t, a, b;
  cin >> t >> a >> b;
  rep(i, t) {
    // cout << "Case #" << (i+1) << ": ";
    solve();
  }
}
