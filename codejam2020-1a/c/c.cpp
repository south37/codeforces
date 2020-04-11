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

// 0,      1,   2,     3
// bottom, top, right, left
int dr[4]   = { 1, -1, 0, 0 };
int dc[4]   = { 0, 0, 1, -1 };
int revD[4] = { -1, 1, 0, 0 };
int revC[4] = { 0, 0, -1, 1 };

vector<vector<ll>> mat;

bool skill_is_lower(vector<vector<vector<pair<P, ll>>>>& neibers, int r, int c) {
  vector<ll> skills;
  rep(i, 4) {
    if (neibers[r][c][i].second > 0) {
      skills.push_back(neibers[r][c][i].second);
    }
  }
  if (skills.size() == 0) { return false; }

  ll avg = 0;
  for (int skill : skills) { avg += skill; }
  return (avg > skills.size() * mat[r][c]);  // mat[r][c] is lower than average of neibers
}

void solve() {
  ll h, w;
  cin >> h >> w;
  mat.assign(h, vector<ll>(w));
  ll sum = 0;
  rep(r, h) {
    rep(c, w) {
      cin >> mat[r][c];
      sum += mat[r][c];
    }
  }

  queue<pair<ll, ll>> q; // eliminate q

  // neibers[r][c] .. neibers or (r, c)
  vector<vector<vector<pair<P, ll>>>> neibers(h, vector<vector<pair<P, ll>>>(w, vector<pair<P, ll>>(4, pair<P, ll>({ -1, -1 }, -1))));
  rep(r, h) {
    rep(c, w) {
      if (r > 0) {
        neibers[r][c][1] = pair<P, ll>({ r-1, c }, mat[r-1][c]); // top
      }
      if (r < h-1) {
        neibers[r][c][0] = pair<P, ll>({ r+1, c }, mat[r+1][c]); // bottom
      }
      if (c > 0) {
        neibers[r][c][3] = pair<P, ll>({ r, c-1 }, mat[r][c-1]); // left
      }
      if (c < w-1) {
        neibers[r][c][2] = pair<P, ll>({ r, c+1 }, mat[r][c+1]); // right
      }

      if (skill_is_lower(neibers, r, c)) {
        q.emplace(r, c);
      }
    }
  }

  ll ans = 0;
  while (!q.empty()) {
    ans += sum;
    ll sz = q.size();
    rep(iter, sz) {
      auto p = q.front(); q.pop();
      int r = p.first;
      int c = p.second;
      sum -= mat[r][c]; // eliminate
      // Here, check neibers
      rep(i, 4) {
        auto p = neibers[r][c][i^1];
        P pos = p.first;
        ll nextR = pos.first;
        ll nextC = pos.second;
        ll skill = p.second;
        if (nextR < 0) { continue; } // invalid
        neibers[nextR][nextC][i] = neibers[r][c][i]; // update neiber

        // Check the average skill
        if (skill_is_lower(neibers, nextR, nextC)) {
          q.emplace(nextR, nextC);
        }
      }
    }
  }
  ans += sum;
  cout << ans;
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
    cout << endl;
  }
}
