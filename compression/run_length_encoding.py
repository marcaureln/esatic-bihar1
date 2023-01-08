def encode(text):
  res = ''
  n = len(text)
  i = 0
  while i < n - 1:
    count = 1
    while (i < n - 1 and text[i] == text[i + 1]):
      count += 1
      i += 1
    res += text[i] + str(count)
    i += 1
  return res


def decode(text):
  res = ''
  i = 0
  while i < len(text) - 1:
    res += text[i] * int(text[i + 1])
    i += 2
  return res


if __name__ == "__main__":
  test = "wwwwaaadexxxxxxywww"
  encoded_text = encode(test)
  print('Résultat encodage :', encoded_text)
  decoded_text = decode(encoded_text)
  print('Résultat décodage :', decoded_text)
