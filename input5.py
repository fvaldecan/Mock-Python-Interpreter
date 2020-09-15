def f(a,b):
    array = a
    newElement = b
    array.append(newElement)
    return array
vName = [1, 3, 5, 7, 9]
print vName
a = vName[10 * 0] + 5
array = f(vName,a)
print array