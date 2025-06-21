import sys
from pymongo import MongoClient
from pymongo.errors import ConnectionFailure

# !!! IMPORTANT !!!
# Replace this with your actual MongoDB connection string.
MONGO_URI = "mongodb+srv://Peter:vx06051blveBaZ7T@cluster0.t9fms6j.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"

# --- Exit Codes ---
# 0: Success
# 1: Argument Error (wrong number of args, invalid level, etc.)
# 2: Database Connection Error
# 3: Database Operation Error (e.g., update failed)

def main():
    if len(sys.argv) < 4:
        sys.exit(1) # Exit with Argument Error

    command = sys.argv[1].strip()
    level_str = sys.argv[2].strip()
    name = " ".join(sys.argv[3:]).strip()

    if command != "1" or not name:
        sys.exit(1) # Exit with Argument Error

    try:
        level = int(level_str)
    except ValueError:
        sys.exit(1) # Exit with Argument Error (level is not a number)

    try:
        client = MongoClient(MONGO_URI, serverSelectionTimeoutMS=5000)
        # The ismaster command is cheap and does not require auth.
        client.admin.command('ismaster')
        db = client["game_database"]
        collection = db["player_levels"]
    except ConnectionFailure:
        sys.exit(2) # Exit with DB Connection Error

    if command == "1":
        try:
            collection.update_one(
                {"name": name},
                {"$set": {"level": level}},
                upsert=True
            )
            client.close()
            sys.exit(0) # Exit with Success
        except Exception:
            client.close()
            sys.exit(3) # Exit with DB Operation Error
    
    # Fallback in case logic expands later
    sys.exit(1)


if __name__ == "__main__":
    main()
