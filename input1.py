def h():
    print "Function h() called"
sumi = 0
sumj = 0
divBy2 = 0
divBy3 = 0
for i in range(10):
    print i
    if( i % 2 == 0 ):
        divBy2 = divBy2 + 1
    elif( i % 3 == 0 ):
        divBy3 = divBy3 + 1
    sumi = sumi + i
    for j in range( 10 ):
        sumj = sumj + j
        print j
print sumi
print sumj

print divBy2
print divBy3
array = [1, 2, 3 ,4]
h()
print array
array[0] = array[1] + sumi
print array
array.append(sumj)
print array
array.append(sumj+sumi)
print array
array.pop()
print array
