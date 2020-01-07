#include <iostream>

void fibonacci_forward(int& n_1, int& n) {
  std::tie(n_1, n) = std::make_pair(n, n + n_1);
}

void fibonacci_backward(int& n_1, int& n) {
  std::tie(n_1, n) = std::make_pair(n - n_1, n_1);
}

int quotient_fibonacci(int a, int b) {
  if (a < b) return 0;
  auto c = b;
  auto fib_n_1 = 1, fib_n = 1;

  do {
    fibonacci_forward(b, c);
    fibonacci_forward(fib_n_1, fib_n);
  } while (c < a);

  auto ret = 0;
  do {
    if (a >= c) {
      a = a - c;
      ret += fib_n;
    }
    fibonacci_backward(b, c);
    fibonacci_backward(fib_n_1, fib_n);
  } while (c > 0);

  return ret;
}

std::pair<int, int> quotient_remainder_fibonacci(int a, int b) {
  if (a < b) return {0, a};
  auto c = b;
  auto fib_n_1 = 1, fib_n = 1;

  do {
    fibonacci_forward(b, c);
    fibonacci_forward(fib_n_1, fib_n);
  } while (c < a);

  auto quotient = 0;
  do {
    if (a >= c) {
      a = a - c;
      quotient += fib_n;
    }
    fibonacci_backward(b, c);
    fibonacci_backward(fib_n_1, fib_n);
  } while (c > 0);

  return std::make_pair(quotient, a);
}

int main() {
  std::cout << quotient_fibonacci(47, 3) << std::endl;
  std::cout << quotient_fibonacci(42, 3) << std::endl;

  auto ret = quotient_remainder_fibonacci(47, 3);
  std::cout << ret.first << " " << ret.second << std::endl;
  ret = quotient_remainder_fibonacci(42, 3);
  std::cout << ret.first << " " << ret.second << std::endl;
  return 0;
}
