#!/bin/env python3

# Update list within iteration
num = 10
numlist = list(range(num))
for i in numlist:
    print(i,end=',')
    if i == num-1:
        numlist.extend(reversed(range(num-1)))
else:
    print()

# Check if file has any matching extensions
def check_ext(filename):
    exts = ('c', 'h', 'cpp', 'hpp', 'cxx', 'hxx')
    status = 'no'
    if filename.endswith(exts):
        status = ''
    print("File", filename, "has", status, "matching extenstion in", exts)
    return status
# filename = input('Enter a file name: ')
check_ext('test.c')
check_ext('test.txt')
check_ext('test.hxx')
print()

# List Comprehension - apply expression iterating over a list
test_filenames = ('test.cpp', 'test.txt', 'test.h', 'test')
list(map(check_ext, test_filenames))
print()
[check_ext(filename) for filename in test_filenames]
print()

# Update dictionary with filenames and count
file_dict = dict.fromkeys(test_filenames, 1)
for file in ('test.c', 'test.cpp', 'test.h', 'test.hpp'):
    file_dict.setdefault(file, 0)
    file_dict[file] += 1
else:
    print(file_dict)
file_dict = {}
for file in test_filenames + ('test.c', 'test.cpp', 'test.h', 'test.hpp'):
    file_dict.setdefault(file, dict(count=0))
    # print(file, id(file_dict[file]), file_dict[file])
    file_dict[file]['count'] += 1
else:
    print(file_dict)