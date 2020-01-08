#include <iostream>
#define Regular typename
#define Integer typename
#define SemigroupOp typename
#define MonoidOp typename
#define GroupOp typename
#define Monoid typename
#define Group typename

struct fib_matrix {
  int a;
  int b;
};

struct fib_matrix_multiply {
  fib_matrix operator()(const fib_matrix& l, const fib_matrix& r) const {
    return fib_matrix{l.a * (r.a + r.b) + l.b * r.a, l.a * r.a + l.b * r.b};
  }
};

fib_matrix identity_element(fib_matrix_multiply op) {
  return fib_matrix{0, 1};
}

template <Integer N>
bool odd(N n) {
  return bool(n & 0x1);
}

template <Integer N>
N half(N n) {
  return n >> 1;
}

template <Monoid A>
A identity_element(std::plus<A> op) {
  return A(0);
}

template <Monoid A>
A identity_element(std::multiplies<A> op) {
  return A(1);
}

template <Group A>
std::negate<A> inverse_operation(std::plus<A>) {
  return std::negate<A>();
}

template <Group A>
struct reciprocal {
  A operator()(const A& a) const { return A(1) / a; }
};

template <Group A>
reciprocal<A> inverse_operation(std::multiplies<A>) {
  return reciprocal<A>();
}

template <Regular A, Integer N, SemigroupOp OP>
A power_semigroup_accumulate(A r, A a, N n, OP op) {
  // Preconditions: n >= 0
  if (n == N(0)) return r;
  while (true) {
    if (odd(n)) {
      r = op(r, a);
      if (n == N(1)) return r;
    }
    n = half(n);
    a = op(a, a);
  }
}

template <Regular A, Integer N, SemigroupOp OP>
A power_semigroup(A a, N n, OP op) {
  // Precondition: n > 0
  while (!odd(n)) {
    a = op(a, a);
    n = half(n);
  }
  if (n == N(1)) return a;
  return power_semigroup_accumulate(a, op(a, a), half(n - 1), op);
}

template <Regular A, Integer N, MonoidOp OP>
A power_monoid(A a, N n, OP op) {
  // Precondition: n >= 0
  if (n == N(0)) return identity_element(op);
  return power_semigroup(a, n, op);
}

template <Regular A, Integer N, GroupOp OP>
A power_group(A a, N n, OP op) {
  if (n < 0) {
    n = -n;
    a = inverse_operation(op)(a);
  }
  return power_monoid(a, n, op);
}

int fib(int n) {
  auto matrix = power_monoid(fib_matrix{1, 0}, n, fib_matrix_multiply());
  return matrix.a;
}

int main() {
  std::cout << power_semigroup(13, 8, std::plus<int>()) << std::endl;
  std::cout << power_monoid(7, 13, std::plus<int>()) << std::endl;
  std::cout << power_monoid(13, 0, std::plus<int>()) << std::endl;
  std::cout << power_group(3.0, -1, std::multiplies<double>()) << std::endl;
  for (int i = 0; i < 46; i ++) {
    std::cout << "Fib\t" << i << ": " << fib(i) << std::endl;
  }
  return 0;
}