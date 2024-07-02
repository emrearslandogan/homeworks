from the2 import check_month

resultList = []
theList = []
exampleList = []
with open('results.txt', 'r') as results:
    for line in results:
        line = line.strip('\n')
        result = eval(line)
        resultList.append(result)
with open('test.txt', 'r') as test:
    for line in test:
        line = line.strip('\n').split(' ')
        exampleList.append(line)
        theResult = check_month(line)
        theList.append(theResult)

a = 0
for i in range(len(resultList)):
    if resultList[i] != theList[i]:
        print(f'Test Case {i} Failed.')
        a += 1
