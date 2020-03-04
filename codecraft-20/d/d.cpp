// 1:50am

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

vector<string> result;
vector<vector<ll>> states; // 0 .. unvisited, 1 .. intermediate, 2 .. visited and not cycle, 3 .. visited and cycle

ll n;
vector<vector<pair<ll, ll>>> input;
int dr[4] = { 1, -1, 0, 0 }; // 0 .. D, 1 .. U, 2 .. R, 3 .. L
int dc[4] = { 0, 0, 1, -1 };

// return false if not reabhable to
bool cycleDfs(int r, int c) {
  // cout << "cycleDfs" << endl;
  // cout << r << "," << c << endl;
  // cout << states[r][c] << endl;

  if (states[r][c] == 1) { // cycle found
    return true;
  }
  if (states[r][c] == 3) { // cycle found
    return true;
  }
  if (states[r][c] == 2) { // not cycle
    return false;
  }
  bool isCycle = false;
  states[r][c] = 1;
  for (int i = 0; i < 4; ++i) {
    int nextR = r + dr[i];
    int nextC = c + dc[i];
    if (nextR < 0 || nextR >= n || nextC < 0 || nextC >= n) { continue; }
    if (input[nextR][nextC] != mp(-1ll, -1ll)) { continue; }  // skip no-cycle

    // cout << "nextR, nextC " << nextR << "," << nextC << endl;

    if (cycleDfs(nextR, nextC)) {
      isCycle = true;
      if (i == 0) {
        result[r][c] = 'D';
      } else if (i == 1) {
        result[r][c] = 'U';
      } else if (i == 2) {
        result[r][c] = 'R';
      } else if (i == 3) {
        result[r][c] = 'L';
      }
      break;
    }
  }
  if (!isCycle) {
    states[r][c] = 2;
    return false;
  } else {
    states[r][c] = 3;
    return true;
  }
}

// return false if not reabhable to
bool dfs(int r, int c, pair<ll, ll> dest) {
  // cout << "dfs" << endl;
  // cout << r << "," << c << endl;
  // cout << states[r][c] << endl;

  if (r == dest.first && c == dest.second) {
    result[r][c] = 'X';
    return true;
  }

  if (states[r][c] == 3) { return false; }
  if (states[r][c] == 2) { return input[r][c] == dest; }

  // Here, states[r][c] == 0
  states[r][c] = 1;
  bool reachable = false;
  for (int i = 0; i < 4; ++i) {
    int nextR = r + dr[i];
    int nextC = c + dc[i];
    if (nextR < 0 || nextR >= n || nextC < 0 || nextC >= n) { continue; }
    if (states[nextR][nextC] == 1) { continue; } // skip cycle

    // cout << "nextR, nextC " << nextR << "," << nextC << endl;
    // cout << "dest " << dest.first << "," << dest.second << endl;
    // cout << "input[nextR][nextR] " << input[nextR][nextC].first << "," << input[nextR][nextC].second << endl;

    if (input[nextR][nextC] == dest) {
      if (dfs(nextR, nextC, dest)) {
        reachable = true;
        if (i == 0) {
          result[r][c] = 'D';
        } else if (i == 1) {
          result[r][c] = 'U';
        } else if (i == 2) {
          result[r][c] = 'R';
        } else if (i == 3) {
          result[r][c] = 'L';
        }
      }
    }
  }
  states[r][c] = 2;
  return reachable;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  input.assign(n, vector<pair<ll, ll>>(n));
  rep(i, n) {
    rep(j, n) {
      ll r, c;
      cin >> r >> c;
      if (r == -1 && c == -1) {
        input[i][j] = { -1, -1 };
      } else {
        --r; --c; // 0-indexed;
        input[i][j] = { r, c };
      }
    }
  }
  result.assign(n, string(n, ' '));
  states.assign(n, vector<ll>(n));

  // Here, input[i][j] contains the destination from (i, j)
  // - (-1, -1) must make cycle.
  // - can not move over (-1, -1).
  // connect the components with "same destination"

  rep(i, n) {
    rep(j, n) {
      if (states[i][j] >= 2) { continue; } // already visited

      // Here, start dfs from (i,j)
      if (input[i][j] == mp(-1ll, -1ll)) { // cycle
        if (!cycleDfs(i, j)) { // not reacheable to pos
          cout << "INVALID" << endl;
          return 0;
        }
      } else {
        pair<ll, ll> pos = input[i][j];
        if (!dfs(i, j, pos)) { // not reacheable to pos
          cout << "INVALID" << endl;
          return 0;
        }
      }
    }
  }

  cout << "VALID" << endl;
  rep(i, n) {
    cout << result[i] << endl;
  }
}
