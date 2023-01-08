def mccarthy91(n):
  if n > 100:
    print(n - 10)
    return n - 10
  print('mccarthy91(mccarthy91(' + str(n + 11) + ')')
  return (mccarthy91(mccarthy91(n + 11)))


print(mccarthy91(1000))
