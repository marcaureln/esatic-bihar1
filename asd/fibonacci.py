def fib(n):
  if n <= 1:
    return 1
  return fib(n-1) + fib(n-2)

def fast_fib(n, memo=dict()):
  if n <= 1:
    return 1
  if n not in memo:
    memo[n] = fast_fib(n-1, memo) + fast_fib(n-2, memo)
  return memo[n]

#print(fib(50))
print(fast_fib(998))