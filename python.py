import random

""" Slower 
def generate_char():
    return str(chr(random.randint(33, 126)))

with open('large.txt', 'w') as f:
    for _ in range(20000000):
        f.write(generate_char())
"""

# faster
def generate_str():
    return "".join([chr(random.randrange(33,126)) for _ in range(10000)])

with open('large2.txt', 'w') as f:
    for _ in range(2000):
        f.write(generate_str())
