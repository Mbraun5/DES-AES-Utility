import random

# faster
def generate_str():
    return "".join([chr(random.randrange(33,126)) for _ in range(10000)])

with open('large1.txt', 'w') as f:
    for _ in range(2000):
        f.write(generate_str())

with open('large2.txt', 'w') as f:
    for _ in range(2000):
        f.write(generate_str())