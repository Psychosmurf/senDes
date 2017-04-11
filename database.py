import sqlite3
from validate_email import validate_email
# Connects to Database file
CONN = sqlite3.connect('users.db')
C = CONN.cursor()


def check_user(username, password, email=" "):
    ''' Checks if the user is in the database '''
    # command for selecting a row
    check_row = "SELECT username, password, email FROM users"
    for row in C.execute(check_row):
        if str(row[0]) == username and str(row[1]) == password:
            return True
        if email != " ":
            if str(row[2]) == email:
                return True

    return False

def enter_user(username, password, email):
    ''' Enters a new user to the database '''
    if not validate_email(email):
        return 35, "Incorrect email format"

    check_row = "SELECT username FROM users"
    for row in C.execute(check_row):
        if str(row[0]) == username:
            return 30, "Username is already in use"

    if not check_user(username, password, email):
        enter_row = "INSERT INTO users (username, password, email) VALUES (?, ?, ?)"
        C.execute(enter_row, (username, password, email))
        CONN.commit()
        return 1, "Success"
    else:
        return 0, "You already have an account"

