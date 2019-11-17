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

const int MAX_ROW = 10010; // To be set appropriately.
const int MAX_COL = 500; // To be set appropriately.

class BitMatrix {
public:
  BitMatrix(int m = 1, int n = 1) : H(m), W(n) {}
  inline bitset<MAX_COL>& operator [] (int i) { return val[i]; }

  int H, W;

private:
  bitset<MAX_COL> val[MAX_ROW];
};

ostream& operator << (ostream& s, BitMatrix A) {
  s << endl;
  rep(i, A.H) {
    rep(j, A.W) {
      s << A[i][j] << ", ";
    }
    s << endl;
  }
  return s;
}

int GaussJordan(BitMatrix &A, bool is_extended = false) {
  int rank = 0;
  rep(col, A.W) {
    if (is_extended && col == A.W - 1) { break; }
    int pivot = -1;
    for (int row = rank; row < A.H; ++row) {
      if (A[row][col]) {
        pivot = row;
        break;
      }
    }
    if (pivot == -1) continue;
    swap(A[pivot], A[rank]);
    rep(row, A.H) {
      if (row != rank && A[row][col]) {
        A[row] ^= A[rank];
      }
    }
    ++rank;
  }
  return rank;
}

int linear_equation(BitMatrix A, vector<int> b, vector<int> &res) {
  int m = A.H, n = A.W;
  BitMatrix M(m, n + 1);
  rep(i, m) {
    rep(j, n) {
      M[i][j] = A[i][j];
    }
    M[i][n] = b[i];
  }
  int rank = GaussJordan(M, true);

  // check if it has no solution
  for (int row = rank; row < m; ++row) {
    if (M[row][n]) { return -1; }
  }

  // answer
  res.assign(n, 0);
  rep(i, rank) {
    res[i] = M[i][n];
  }
  return rank;
}

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<ll> a(N);
//   rep(i, N) {
//     cin >> a[i];
//   }
//
//   const int DIGIT = 61;
//   BitMatrix A(DIGIT, N);
//   rep(d, DIGIT) {
//     rep(i, N) {
//       if (a[i] & (1LL << d)) {
//         A[d][i] = 1;
//       }
//     }
//   }
//
//   int rank = GaussJordan(A);
//   cout << (1LL << rank) << endl;
// }

void solve() {
  ll n;
  cin >> n;
  vector<string> s(n);
  rep(i, n) {
    cin >> s[i];
  }

  // For Debug
  // cout << endl;
  // rep(i, n) {
  //   cout << s[i] << endl;
  // }
  // Now, s[i][j] means the position.
  // We maske n*n vector. this vector contains the whole information of board.
  // We want to try (n-1)*2+1 operation. This is equation. after this operation, we want to make all board to be black.
  // So, the operation means the change of elements in vector.

  // white(.) is 0, black(#) is 1.

  BitMatrix A(n*n, 4*n+2);
  vector<int> b(n*n), res;

  rep(i, n) {
    rep(j, n) {
      ll current = (s[i][j] == '.') ? 0 : 1;
      b[i*n+j] = 1 - current; // We want to swap if first is 0(white).
      // For Debug
      // if (current == 0) {
      //   cout << "(i,j)="<<"("<<i<<","<<j<<")="<<endl;
      // }
    }
  }

  // For Debug
  map<ll, ll> left_insert_map;
  map<ll, ll> right_insert_map;

  // We make 2 * "2*(n-1)+1" equations.
  // Which has the uniquness by "i-j" when left ans "i+j" when right
  ll left_counter = 0;
  map<ll, ll> left_set;  // "\"
  ll right_counter = 0; // The initial value.
  map<ll, ll> right_set;  // "\"
  // We use i-j in increasing order.

  set<ll> lefts; // "\"
  set<ll> rights;  // "/"
  rep(i, n) {
    rep(j, n) {
      if (lefts.count(i-j) == 0) { // Make left equation
        lefts.insert(i-j);
      }
      if (rights.count(i+j) == 0) { // Make right equation
        rights.insert(i+j);
      }
    }
  }
  // Now, lefts and rights are sorted
  for (auto v : lefts) {
    left_set[v] = left_counter++;
    left_insert_map[left_set[v]] = v; // For Debug
  }
  for (auto v : rights) {
    right_set[v] = left_counter + (right_counter++);
    right_insert_map[right_set[v]] = v; // For Debug
  }
  // Now, left_set and right_set are created

  // cout << "For Debug:" << endl;
  // cout << "lefts:";
  // for (auto v: lefts) { cout << v << " "; }
  // cout << endl;
  // cout << "rights:";
  // for (auto v: rights) { cout << v << " "; }
  // cout << endl;
  // cout << "left_counter + right_counter: " << left_counter + right_counter << endl;

  rep(i, n) {
    rep(j, n) {
      // if (left_set.count(i-j) == 0) { // Make left equation
      //   left_set[i-j] = left_counter++;
      //   left_insert_map[left_set[i-j]] = i-j;
      // }
      A[i*n+j][left_set[i-j]] = 1; // Set 1 because

      // if (right_set.count(i+j) == 0) { // Make right equation
      //   right_set[i+j] = right_counter++;
      //   right_insert_map[right_set[i+j]] = i+j;
      // }
      A[i*n+j][right_set[i+j]] = 1; // Set 1 because
    }
  }
  // Now, all equation are created. We solve it by GaussJordan.

  int rank = linear_equation(A, b, res);
  if (rank == -1) {
    cout << "Invalid!";
  } else {
    // Now, res contains the operation.
    ll even_cnt = 0; // even. limit is 10 if n = 5.
    ll odd_cnt = 0; // odd. limit is 8 if n = 5.
    rep(i, res.size()) {
      if (res[i] == 1) {
        if (i <= 2*(n-1)) {
          // cout << "operation(\\) i: " << i << endl;
          // cout << "i-j: " << left_insert_map[i] << endl;
          if (left_insert_map[i] % 2 == 0) { //even
            ++even_cnt;
          } else {
            ++odd_cnt;
          }
        } else {
          // cout << "operation(/) i: " << i << endl;
          // cout << "i+j: " << right_insert_map[i] << endl;
          if (right_insert_map[i] % 2 == 0) { //even
            ++even_cnt;
          } else {
            ++odd_cnt;
          }
        }
      }
    }
    // total is 2*(n-1)+1 * 2 = 4 * n - 2
    // e.g. n=5 -> 18
    ll even_limit;
    ll odd_limit;
    if (n % 2 != 0) {
      even_limit = 2*n;
      odd_limit = 2*n-2;
    } else {
      even_limit = 2*n-1;
      odd_limit = 2*n-1;
    }
    // cout << "even_cnt: " << even_cnt << endl;
    // cout << "odd_cnt: " << odd_cnt << endl;
    cout << min(even_cnt, (even_limit - even_cnt)) + min(odd_cnt, (odd_limit - odd_cnt));
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    cout << "Case #"<<i+1<<": ";
    solve();
    cout << endl;
  }
}
