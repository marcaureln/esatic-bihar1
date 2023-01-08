def merge_sort(array):
  n = len(array)
  if n <= 1:
    return array
  else:
    return merge(merge_sort(array[:int(n / 2)]), merge_sort(array[int((n / 2)):]))

def merge(array1, array2):
  if len(array1) < 1:
    return array2
  if len(array2) < 1:
    return array1
  if array1[0] <= array2[0]:
    return [array1[0], *merge(array1[1:], array2)]
  else:
    return [array2[0], *merge(array1, array2[1:])]

t = [42, 10, 58, 45, 82, 72, 95, 43, 100, 66]

print('Avant tri : ', t)
print('.'*50)
print('Après tri :', merge_sort(t))