from faker import Faker
import random

fake = Faker()

participants = [fake.name() for _ in range(10)]

for name in participants:
    print(name)

half1 = []
half2 = []

for _ in participants:
    name1 = random.choice(participants)
    name2 = random.choice(participants)

    half1.append(name1)
    half2.append(name2)

    participants.pop(participants.index(name1))
    participants.pop(participants.index(name2))

print(*zip(half1, half2))