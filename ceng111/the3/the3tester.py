from the3 import area
errors = 0
resultList = []
theList = []
errorlist = []
with open('outputs.txt', 'r') as outputs:
    for line in outputs:
        line = line.strip('\n')
        result = eval(line)
        resultList.append(result)
with open('inputs.txt', 'r') as inputs:
    for line in inputs:
        line = line.strip('\n')
        inn = eval(line)
        try:
            theResult = area(inn[0],inn[1])
            theList.append(theResult)
        except:
            theList.append(-1)

for i in range(len(resultList)):
    try: 
        if abs(resultList[i] - theList[i])>0.000001:
            errors += 1
            errorlist.append(i)
    except:
        errors += 1
        errorlist.append(i)
        
if errors == 0:
    print("Congrats")
elif errors > 30:
    print(f"There are {errors} failed cases.")
    for i in range(30):
        print(f"Testcase {errorlist[i]} failed.")
    print("Just 30 failed cases were printed")
else:
    print(f"There are {errors} failed cases.")
    for i in errorlist:
        print(f"Testcase {i} failed.")
    
