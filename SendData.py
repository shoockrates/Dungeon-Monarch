from pymongo import MongoClient

client = MongoClient("mongodb+srv://Peter:vx06051blveBaZ7T@cluster0.t9fms6j.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0")

import sys

SEND = "1"

command = 0

level = 0

if len(sys.argv) < 2:
    sys.exit(1)

command = sys.argv[1].lower()

level = sys.argv[2].lower()

if command not in ["1", "0"]:
    sys.exit(1)

if level not in ["1", "2", "3", "4", "5"]:
    sys.exit(1)

name = ""

for i in range(3, len(sys.argv)):
    if i > 2:
        name += " "
        
    name += sys.argv[i].strip()

if not name:
    sys.exit(1)

try:
    db = client["my_database"]
    collection = db["my_collection"]

    if command == SEND:
        if collection.find_one({"name": name}):
            collection.update_one({"name": name}, {"$set": {"level": level}})
        else:
            data = {"name": name, "level": level}
            collection.insert_one(data)
    else:
        if not collection.find_one({"name": name}):
            sys.exit(2)
            
        data = collection.find_one({"name": name})
        #print(data)
finally:
    client.close()
