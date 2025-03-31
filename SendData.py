from pymongo import MongoClient


client = MongoClient("mongodb+srv://Peter:vx06051blveBaZ7T@cluster0.t9fms6j.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0")

import sys

if len(sys.argv) < 2:
    sys.exit(1)

name = sys.argv[1].strip()

if not name:
    sys.exit(1)

try:
    db = client["my_database"]
    collection = db["my_collection"]

    if collection.find_one({"name": name}):
        sys.exit(2)

    data = {"name": name}
    collection.insert_one(data)
finally:
    client.close()
