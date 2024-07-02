# Emre Arslandoğan
# This program uses file system addressing approach to find brothers, sisters
# Firstly, helper function creates a dictionary (example->  "sarah":"fikret/ahmet/sarah") which pairs 
# names with their absolute path from root (excluding their name itself).


def get_names_and_paths(nested_list):
  def explore_list(data, current_path=""):
    result = {}
    if isinstance(data, list):
      for index, item in enumerate(data):
        new_path = f"{current_path}{index}" if current_path else str(index)
        result.update(explore_list(item, new_path))
    elif isinstance(data, str):
      result[data] = current_path
    return result

  return explore_list(nested_list)

# after getting this type of indexing, we can figure out absolute path easily.
# First, without changing anything find the a.b.c.d's a.b.c.0 That is the last parent. Pop last zero. 
# Iterate, reach root node.

def pathFinalizer(nested_list):
  indexDict = get_names_and_paths(nested_list)

  absPathDict = {}
  convDict = {v: k for k, v in indexDict.items()}

  for name in indexDict.keys():
    path = ""

    for i in range(len(indexDict[name])): # this will continue for every digit of index path
      if indexDict[name] == "0": # root node
        path = "ROOT/"

      elif indexDict[name][-1] == 0: 
        path = name
        indexDict[name] = indexDict[name][:-1]
      
      else:
        path = convDict[indexDict[name][:-1]+"0"] + "/" + path
        indexDict[name] = indexDict[name][:-1]

    if name in path.split("/"):
      absPathDict.update({name:path[:path[:-1].rfind("/")]})  

    else:
      absPathDict.update({name:path[:-1]})

  return absPathDict


def brothers(T, pname): 
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items():
    if name.islower() and apath == path and pname != name:
      result.append(name)
      
  return result 

def sisters(T, pname): 
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items():
    if apath == path and name[0].isupper() and pname != name: # checks if they have the same parents, not themself and woman
      result.append(name)
      
  return result 

def siblings(T, pname):
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items():
    if apath == path and pname != name:   # checks if they have the same parents and not itself
      result.append(name)

  return result

def uncles(T, pname):
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items():
    if apath == path[:path.rfind("/")] and name.islower() and path[path.rfind("/")+1:] != name: # checks if it is male, upper-level, and not the father
      result.append(name)

  return result

def aunts(T, pname):
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items():
    if apath == path[:path.rfind("/")] and name[0].isupper() and path[path.rfind("/")+1:] != name: # checks if it is male, upper-level, and not the father
      result.append(name)

  return result

def cousins(T, pname):
  referenceDict = pathFinalizer(T)
  path = referenceDict[pname]

  result = []

  for name, apath in referenceDict.items(): # their grand-parent needs to be same, but different parents for being cousins
    if apath[:apath.rfind("/")] == path[:path.rfind("/")] and path[path.rfind("/")+1:] != apath[apath.rfind("/")+1:]:
      result.append(name)

  return result
