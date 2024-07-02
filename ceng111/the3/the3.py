from math import atan2

def checkPoint(point, poly_coords): # checks if a point is inside a polygon 
    full_area = polygon_area(poly_coords)

    temp_area = 0

    for i in range(len(poly_coords)-1):
        temp_coords = [poly_coords[i]] + [poly_coords[i+1]] + [point]
        temp_area += polygon_area(temp_coords)

    temp_area += polygon_area([poly_coords[0], poly_coords[-1], point])


    if temp_area == full_area:    return True
    else:   return False


def polygon_area(coords):  # calculates a polygon's area using shoelace formula
    points = coords[:]
    points.append(coords[0])

    positive = 0
    negative = 0

    for i in range(len(points) - 1):
        positive += points[i][0] * points[i+1][1]

    for i in range(len(points) - 1):
        negative -= points[i][1] * points[i+1][0]

    return abs((positive + negative)) / 2 


# what if we just found ever side's equation, checked if any two of those intersect at any point, and then find the area from that point
def intersection(point11, point12, point21, point22):
    
    ## creating line equations
    if point12[0] - point11[0] != 0:  # in case it is not vertical
        m1 = (point12[1] - point11[1]) / (point12[0] - point11[0])
        n1 =  point12[1] - (m1 * point12[0])
        line1 = (-m1, 1, -n1)
    
    else:   line1 = (-1, 0, -point11[0])  # is vertical

    if point22[0] - point21[0] != 0:
        m2 =  (point22[1] - point21[1]) / (point22[0] - point21[0])
        n2 =  point22[1] - (m2 * point22[0])
        line2 = (-m2, 1, -n2)
    
    else:   line2 = (-1, 0, -point21[0])

    ## intersections
    if line1[1] != 0 and line2[1] != 0:  # in case both of the lines are not vertical
        determinant = (line1[0]*line2[1]) - (line2[0]*line1[1])
        if abs(determinant) <= 0.00000001:   return -1  ## lines are parallel, with a little bit of error margin

        x_determinant = - (line1[2]*line2[1]) + (line2[2]*line1[1])
        y_determinant = - (line1[0]*line2[2]) + (line2[0]*line1[2])

        x_coord = round(x_determinant / determinant, 12)
        y_coord = round(y_determinant / determinant, 12)

        if min(point11[0], point12[0]) <= x_coord <= max(point11[0], point12[0]) and min(point21[0], point22[0]) <= x_coord <= max(point21[0], point22[0]):
            if min(point11[1], point12[1]) <= y_coord <= max(point11[1], point12[1]) and min(point21[1], point22[1]) <= y_coord <= max(point21[1], point22[1]):
                return (x_coord, y_coord)
            else:   return -1    
        else:   return -1


    elif line1[1] != 0 and line2[1] == 0:  # in case line2 is vertical
        x_coord = point21[0]
        if abs(line1[0]) < 0.00000001:  # if line1 is horizontal
                y_coord = point11[1]
        else:   y_coord = (-line1[0]) * x_coord - line1[2]
    
        if min(point21[1], point22[1]) <= y_coord <= max(point21[1], point22[1]) and min(point11[0], point12[0]) <= x_coord <= max(point11[0], point12[0]) and  min(point11[1], point12[1]) <= y_coord <= max(point11[1], point12[1]):
            return (x_coord, y_coord)
        else:   return -1

    elif line2[1] != 0 and line1[1] == 0:  # in case line1 is vertical
        x_coord = point11[0]
        if abs(line2[0]) < 0.00000001:
            y_coord = point21[1]
        else:   y_coord = (-line2[0]) * x_coord - line2[2]
    
        if min(point11[1], point12[1]) <= y_coord <= max(point11[1], point12[1]) and min(point21[0], point22[0]) <= x_coord < max(point21[0], point22[0]) and min(point21[1], point22[1]) <= y_coord <= max(point21[1], point22[1]):
            return (x_coord, y_coord)
        else:   return -1

    else: return -1

def toClockWise(points):
    n = len(points)
    if n == 0: # if there is no intersection/incloseness
        return -1

    centroid_x = sum(x for x, y in points) / n
    centroid_y = sum(y for x, y in points) / n

    # creating a list of tuples to use while sorting
    indices_and_angles = [(i, atan2(y - centroid_y, x - centroid_x)) for i, (x, y) in enumerate(points)]

    indices_and_angles.sort(key=lambda x: x[1])  # sorting

    ordered_points = [points[i] for i, _ in indices_and_angles]

    return ordered_points


def area(quad, trig):
    intersections = []

    for i in range(3): # for quad
        for j in range(2): # for triangle
            temp_result = intersection(quad[i], quad[i+1], trig[j], trig[j+1])
            if temp_result != -1:
                intersections.append(temp_result)

    for i in range(3):
        temp_result = intersection(quad[i], quad[i+1], trig[-1], trig[0])
        if temp_result != -1:
                intersections.append(temp_result)

    for i in range(2): 
        temp_result = intersection(quad[-1], quad[0], trig[i], trig[i+1])
        if temp_result != -1:
            intersections.append(temp_result)

    temp_result = intersection(quad[-1], quad[0], trig[-1], trig[0])
    if temp_result != -1:
        intersections.append(temp_result)

    # we also need to get which corners are in which shape 
    for qcorner in quad:
        if (checkPoint(qcorner, trig)):
            intersections.append(qcorner)    
    
    for tcorner in trig:
        if (checkPoint(tcorner, quad)):
            intersections.append(tcorner)

    coordinates = toClockWise(intersections)
    
    if coordinates == -1:   return 0.0  # if there isn't any intersection
    else:   return polygon_area(coordinates)