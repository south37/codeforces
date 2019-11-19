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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  // ll d = 0;
  ll i = 0;
  vector<ll> indices; // The indices in which day end.

  while (i < n) {
    vector<bool> visited(1000005); // already entered
    set<ll> entered; // The entered visitors. must be empty at day night.
    // ++d;
    while (i < n) {//) day
      // cout << "i: " << i << endl;
      // cout << "a[i]: " << a[i] << endl;
      if (a[i] > 0) { // enter
        if (visited[a[i]]) { // already entered
          if (entered.size() == 0) {
            // i is not valid.
            indices.push_back(i-1);
            // ++i;
            // cout << "end day with i-1" << i-1 << endl;
            break; // day ends
          } else { // invalid case
            // cout << "doule entered" << endl;
            cout << -1 << endl;
            return 0;
          }
        }
        visited[a[i]] = true;
        entered.insert(a[i]);
      } else { // leave
        if (entered.count(-a[i])) { // ok
          entered.erase(-a[i]);
        } else { // invalid
          // cout << "i: " << i<< endl;;
          // cout << "-a[i]: " << -a[i]<< endl;;
          // cout << "entered.size(): " << entered.size() << endl;;
          // cout << "entered.count(-a[i]): " << entered.count(-a[i]) << endl;;

          // cout << "no enter remove" << endl;
          cout << -1 << endl;
          return 0;
        }
      }
      ++i;
    }

    if (i == n) {
      if (entered.size() > 0) {
        // cout << "remaining" << endl;
        cout << -1 << endl;
        return 0;
      } else { // end
        indices.push_back(n-1);
      }
    }
  }

  cout << indices.size() << endl;
  rep(k, indices.size()) {
    if (k == 0) {
      cout << indices[k] + 1 << " ";
    } else {
      cout << indices[k] - indices[k-1] << " ";
    }
  }
  cout << endl;
}
