#Excercise 1
import xml.etree.ElementTree as ET

# Load and parse the XML file
tree = ET.parse('students.xml')
root = tree.getroot()

# Check the structure
for student in root.findall('student'):
    print(student.find('name').text, student.find('age').text, student.find('city').text)

def display_all_students():
    for student in root.findall('student'):
        id_ = student.find('id').text
        name = student.find('name').text
        age = student.find('age').text
        city = student.find('city').text
        print(f"ID: {id_}, Name: {name}, Age: {age}, City: {city}")

display_all_students()

def display_students_by_city(city_name):
    for student in root.findall('student'):
        city = student.find('city').text
        if city == city_name:
            name = student.find('name').text
            print(f"Name: {name}, City: {city}")

# Example usage: Display students from 'HCM'
display_students_by_city('HCM')

def display_students_by_city(city_name):
    for student in root.findall('student'):
        city = student.find('city').text
        if city == city_name:
            name = student.find('name').text
            print(f"Name: {name}, City: {city}")

# Example usage: Display students from 'HCM'
display_students_by_city('HCM')

def display_students_by_city(city_name):
    for student in root.findall('student'):
        city = student.find('city').text
        if city == city_name:
            name = student.find('name').text
            print(f"Name: {name}, City: {city}")

# Example usage: Display students from 'HCM'
display_students_by_city('HCM')


def add_new_student(id_, name, age, city):
    # Create new student element
    new_student = ET.SubElement(root, 'student')
    ET.SubElement(new_student, 'id').text = id_
    ET.SubElement(new_student, 'name').text = name
    ET.SubElement(new_student, 'age').text = str(age)
    ET.SubElement(new_student, 'city').text = city

    # Save changes to the original XML file
    tree.write('students.xml')


# Example usage: Add a new student
add_new_student('0010', 'New Student', 25, 'NY')

def update_student_by_id(student_id, new_name=None, new_age=None, new_city=None):
    for student in root.findall('student'):
        id_ = student.find('id').text
        if id_ == student_id:
            if new_name:
                student.find('name').text = new_name
            if new_age:
                student.find('age').text = str(new_age)
            if new_city:
                student.find('city').text = new_city
            break
    tree.write('students.xml')

# Example usage: Update student with ID '0003'
update_student_by_id('0003', new_name='Updated Name', new_age=21)

def delete_student_by_id(student_id):
    for student in root.findall('student'):
        id_ = student.find('id').text
        if id_ == student_id:
            root.remove(student)
            break
    tree.write('students.xml')

# Example usage: Delete student with ID '0004'
delete_student_by_id('0004')

#Excercise 2

import xml.etree.ElementTree as ET

# Load and parse NetworkConf.xml
tree = ET.parse('NetworkConf.xml')
root = tree.getroot()


def display_host_info():
    for session in root.find('Sessions').findall('NetworkSession'):
        name = session.get('name')
        protocol = session.get('protocol')
        enable = session.get('enable')
        ip = session.find('NetworkAddress').get('hostIP')
        desc = session.get('desc')

        status = "Connected" if enable == "1" else "Not Connected"
        print(f"Session Name: {name}\nProtocol: {protocol}\nIP: {ip}\nDescription: {desc}\nStatus: {status}\n")


display_host_info()


def display_atm_info():
    tree = ET.parse('TermConf.xml')
    root = tree.getroot()

    terminal = root.find('Terminal')
    terminal_id = terminal.get('id')
    ip = terminal.find('TermIP').text
    branch_number = terminal.find('branchNumber').text
    terminal_type = terminal.find('TerminalType').text
    autorestart = terminal.find('autorestartmode').text

    print(f"Terminal ID: {terminal_id}")
    print(f"IP Address: {ip}")
    print(f"Branch Number: {branch_number}")
    print(f"Terminal Type: {terminal_type}")
    print(f"Auto Restart Mode: {autorestart}")


display_atm_info()


def update_terminal_info():
    tree = ET.parse('TermConf.xml')
    root = tree.getroot()
    terminal = root.find('Terminal')

    new_ip = input("Enter new IP Address: ")
    new_branch_number = input("Enter new Branch Number: ")
    new_terminal_type = input("Enter new Terminal Type: ")
    new_autorestart_mode = input("Enter new Auto Restart Mode (1 for yes, 0 for no): ")

    terminal.find('TermIP').text = new_ip
    terminal.find('branchNumber').text = new_branch_number
    terminal.find('TerminalType').text = new_terminal_type
    terminal.find('autorestartmode').text = new_autorestart_mode

    tree.write('TermConf.xml')
    print("ATM Configuration updated successfully!")


# Call the function to update terminal information
update_terminal_info()

#Excercise 3
import json

# Load the JSON file
with open('Pythongroup.json', 'r') as file:
    data = json.load(file)


def display_posts_info():
    posts = data['group']['posts']

    for post in posts:
        post_id = post['post_id']
        author_name = post['author']['name']
        content = post['content']
        likes = len(post['likes'])
        shares = len(post['shares'])

        print(f"Post ID: {post_id}\nAuthor: {author_name}\nContent: {content}\nLikes: {likes}\nShares: {shares}\n")


display_posts_info()


def most_engaged_post():
    max_engagement = 0
    top_post = None

    for post in data['group']['posts']:
        likes = len(post['likes'])
        shares = len(post['shares']) * 2  # Share is worth +2
        engagement = likes + shares

        if engagement > max_engagement:
            max_engagement = engagement
            top_post = post

    if top_post:
        print(
            f"Most Engaged Post:\nPost ID: {top_post['post_id']}\nContent: {top_post['content']}\nTotal Engagement: {max_engagement}")


most_engaged_post()

from datetime import datetime, timedelta


def most_liked_post_in_first_hour():
    top_post = None
    max_likes = 0

    for post in data['group']['posts']:
        post_time = datetime.strptime(post['timestamp'], '%Y-%m-%d %H:%M:%S')
        one_hour_later = post_time + timedelta(hours=1)

        likes_within_one_hour = [like for like in post['likes'] if
                                 datetime.strptime(like['timestamp'], '%Y-%m-%d %H:%M:%S') <= one_hour_later]
        if len(likes_within_one_hour) > max_likes:
            max_likes = len(likes_within_one_hour)
            top_post = post

    if top_post:
        print(f"Post with Most Likes in First Hour:\nPost ID: {top_post['post_id']}\nLikes: {max_likes}")


most_liked_post_in_first_hour()


def add_new_post(post_id, author_name, content):
    new_post = {
        "post_id": post_id,
        "author": {
            "user_id": f"user_{post_id[-3:]}",
            "name": author_name
        },
        "content": content,
        "timestamp": datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
        "likes": [],
        "shares": []
    }

    data['group']['posts'].append(new_post)

    # Save changes to the file
    with open('Pythongroup.json', 'w') as file:
        json.dump(data, file, indent=4)
    print("New post added successfully!")


# Example usage: Add a new post
add_new_post("post_003", "New Author", "This is a new post")

from collections import Counter


def most_engaged_user():
    user_counter = Counter()

    for post in data['group']['posts']:
        for like in post['likes']:
            user_counter[like['user_id']] += 1
        for share in post['shares']:
            user_counter[share['user_id']] += 2  # Share counts more

    most_engaged = user_counter.most_common(1)[0]
    print(f"Most Engaged User: {most_engaged[0]}, Total Engagements: {most_engaged[1]}")


most_engaged_user()

