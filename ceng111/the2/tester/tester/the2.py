def exponentAdder(days):
    if days > 0:
        return (1 - pow(5,days)) // -4 -1 # used geometrical series'es feature

    else:
        return 0

def rule1(calendar, cost, final_errors): # mother's rule

    # finding mother's days inside the given calendar, and formatting it
    enumcalendar = enumerate(calendar)
    motherdays = list(filter(lambda x:  x[1] == "m", enumcalendar)) # finds mother's days 
    motherdaysfinal = [t[0] for t in motherdays]

    # there are 2 conditions, mom can only work for one day each week, and her offday is fixed
    temp = [t % 5 for t in motherdaysfinal]
    temp = set(temp) # making it a set, because this way we can see if she works more than one day in a week or offday differs 

    if len(temp) > 1:
        final_errors.append(1)
        return cost, final_errors
    
    else:
        cost += len(motherdaysfinal) * 10
        return cost, final_errors 


def rule2(calendar, cost, final_errors): # father's rule

    # finding father's days
    enumcalendar = enumerate(calendar)
    fatherdays = list(filter(lambda x: x[1] == "f", enumcalendar)) # finds father's days
    fatherdaysfinal = [t[0] for t in fatherdays]

    # there are 2 conditions, he can't babysit more than 2 days, and those days cannot be consecutive
    if len(fatherdaysfinal) > 2:
        final_errors.append(2)
        return cost, final_errors
    
    elif len(fatherdaysfinal) == 2 and fatherdaysfinal[0] == fatherdaysfinal[1] -1: # if the two days differ with 1 day 
        if fatherdaysfinal[0] % 5 == 4 and fatherdaysfinal[1] % 5 == 0: # the only exception to the first rule is babysitting friday and monday 
            cost += len(fatherdaysfinal) * 20
            return cost, final_errors
        else:
            final_errors.append(2)
            return cost, final_errors

    else:
        cost += len(fatherdaysfinal) * 20
        return cost, final_errors

def rule3(calendar, cost, final_errors): # babysitter
    # finding babysitter's days
    enumcalendar = enumerate(calendar)
    bsitterdays = list(filter(lambda x: x[1] == "b", enumcalendar))
    bsitterdaysfinal = [t[0] for t in bsitterdays]

    temp = [t + 2*(t//5) for t in bsitterdaysfinal]  # it takes weekends into consideration
    
    differenceMap = [int(temp[e+1]) - int(temp[e]) for e in range(len(temp) -1)]

    formattedDifference = [int(differenceMap[e]) - 1 if int(differenceMap[e]) < 4 and int(differenceMap[e]) != 1 else 0 for e in range(len(temp) -1)]
    interveningDays = sum(formattedDifference)

    cost += (len(bsitterdaysfinal) + interveningDays )* 30
    return cost, final_errors


def rule4(calendar, cost, final_errors): # grandma

    # finding grandmas days
    enumcalendar = enumerate(calendar)
    grandmadays = list(filter(lambda x: x[1] == "g", enumcalendar))
    grandmadaysfinal = [t[0] for t in grandmadays]

    # there is only one condition. She can't work more than 1 wednesday (% == 2)
    temp = [t % 5 for t in grandmadaysfinal]
    
    if temp.count(2) > 1: # if wednesday is present for more than one time 
        final_errors.append(4)
        return cost, final_errors
    
    else:
        cost += (len(grandmadaysfinal) * 50)
        return cost, final_errors


def rule5(calendar, cost, final_errors): # Aunt 1
    # finding a1's days
    enumcalendar = enumerate(calendar)
    a1days = list(filter(lambda x: x[1] == "a1", enumcalendar))
    a1daysfinal = [t[0] for t in a1days]

    # there is only one condition, she is only avaliable on tuesdays and fridays (% == 1 or % == 4)
    temp = [t % 5 for t in a1daysfinal]

    if (0 in temp) or (2 in temp) or (3 in temp):
        final_errors.append(5) 
        return cost, final_errors
    
    else:
        cost += len(a1daysfinal * 32)
        return cost, final_errors


def rule6(calendar, cost, final_errors): # aunt2

    # finding a1's days
    enumcalendara1 = enumerate(calendar)
    a1days = list(filter(lambda x: x[1] == "a1", enumcalendara1))
    a1daysfinal = [t[0] for t in a1days]

    # finding a2's days
    enumcalendara2 = enumerate(calendar)
    a2days = list(filter(lambda x: x[1] == "a2", enumcalendara2))
    a2daysfinal = [t[0] for t in a2days]

    checking_table = [0 if (t -1) in a1daysfinal and t % 5 != 0 else 1 for t in a2daysfinal] # iterates over a2daysfinal, for an element, if it does not cause an exception it writes 1, otherwise 0  
    
    if 0 in checking_table:
        final_errors.append(6)
        return cost, final_errors

    else:
        cost += len(a2daysfinal) * 27    
        return cost, final_errors


def rule7(calendar, cost, final_errors): # neighbour, monday, tuesday and wednesday

    # finding days
    enumcalendar = enumerate(calendar)
    ndays = list(filter(lambda x: x[1] == "n", enumcalendar))
    ndaysfinal = [t[0] for t in ndays]

    temp = [t % 5 for t in ndaysfinal]
    
    if (3 in temp or 4 in temp):
        final_errors.append(7)
        return cost, final_errors

    else:
        cost += exponentAdder(len(ndaysfinal))     
        return cost, final_errors


def check_month(month_calendar):
    final_errors = []
    cost = 0

    cost, final_errors = rule1(month_calendar, cost, final_errors)
    cost, final_errors = rule2(month_calendar, cost, final_errors)
    cost, final_errors = rule3(month_calendar, cost, final_errors)
    cost, final_errors = rule4(month_calendar, cost, final_errors)
    cost, final_errors = rule5(month_calendar, cost, final_errors)
    cost, final_errors = rule6(month_calendar, cost, final_errors)
    cost, final_errors = rule7(month_calendar, cost, final_errors)

    if final_errors: # if there is no final error
        return final_errors

    else:
        return cost    
