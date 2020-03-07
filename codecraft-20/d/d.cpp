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

vector<string> result; // the result matrix
vector<vector<ll>> states; // 0 .. unvisited, 1 .. intermediate, 2 .. visited and not cycle, 3 .. visited and cycle

ll n;
vector<vector<pair<ll, ll>>> input;
int dr[4] = { 1, -1, 0, 0 }; // 0 .. D, 1 .. U, 2 .. R, 3 .. L
int dc[4] = { 0, 0, 1, -1 };
char dir[4] = { 'D', 'U', 'R', 'L' };
char revDir[4] = { 'U', 'D', 'L', 'R' };

void connect(int sr, int sc, int nr, int nc, char sd, char nd) {
  result[sr][sc] = sd;
  if (result[nr][nc] == ' ') { // { nr, nc } is not painted yet
    result[nr][nc] = nd;
  }
}

void dfs(int r, int c, char d) {
  if (result[r][c] != ' ') { return; } // already painted
  result[r][c] = d;
  rep(i, 4) {
    int nextR = r + dr[i];
    int nextC = c + dc[i];
    if (nextR < 0 || nextR >= n || nextC < 0 || nextC >= n) { continue; } // skip
    if (input[nextR][nextC] == input[r][c]) {
      dfs(nextR, nextC, revDir[i]);
    }
  }
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

  rep(r, n) {
    rep(c, n) {
      if (input[r][c] == mp(-1ll, -1ll)) { // cycle
        bool isPainted = result[r][c] != ' ';
        rep(k, 4) {
          if (isPainted) { continue; } // res is already true

          int nextR = r + dr[k];
          int nextC = c + dc[k];
          if (nextR < 0 || nextR >= n || nextC < 0 || nextC >= n) { continue; }
          if (input[nextR][nextC] == mp(-1ll, -1ll)) {
            connect(r, c, nextR, nextC, dir[k], revDir[k]);
            isPainted = true;
          }
        }
        if (!isPainted) {
          cout << "INVALID" << endl;
          return 0;
        }
      } else {
        if (input[r][c] == mp(r, c)) {
          // start dfs from target
          dfs(r, c, 'X');
        }
      }
    }
  }

  rep(r, n) {
    rep(c, n) {
      if (result[r][c] == ' ') { // not painted
        cout << "INVALID" << endl;
        return 0;
      }
    }
  }

  cout << "VALID" << endl;
  rep(r, n) {
    cout << result[r] << endl;;
  }
}
