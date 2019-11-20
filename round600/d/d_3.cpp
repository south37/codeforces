// base. https://pastebin.com/Heb9bF7b

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
typedef pair<int, int> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const int borne = 201*1000;
ll n, m;

vector<int> graph[borne];
bool visited[borne];
vector<P> ivComp; // The (weaker, biggre) pairs of each connected components.

// Calculate the weaker and the bigger of connected components.
P dfs(int v) {
  visited[v] = true;

  int weaker = v;
  int bigger = v;

  for (int u : graph[v]) {
    if (!visited[u]) {
      int w, b;
      tie(w, b) = dfs(u);
      chmin(weaker, w);
      chmax(bigger, b);
    }
  }

  return mp(weaker, bigger);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m;
  rep(i, m) {
    ll u, v;
    cin >> u >> v;
    --u; --v; // 0-indexed
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  rep(i, n) { // loop of node
    if (!visited[i]) {
      int weaker, bigger;
      tie(weaker, bigger) = dfs(i);
      ivComp.emplace_back(weaker, bigger);
    }
  }

  // Now, ivComp is already sorted.

  int curEnd = -1;
  int rep = 0;

  // We check the all intersections.
  for (auto comp : ivComp) {
    if (comp.fr <= curEnd) {
      ++rep;
    }
    chmax(curEnd, comp.sc);
  }

  cout << rep << endl;
}
