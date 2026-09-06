import random

length = 56
list = sorted(random.sample(range(1, 100), length))
number = random.choice(list)
n_try = 0

"""print('given list: ', list)"""
print('wanted number: ', number)

a = 0
while a != number :
    index = (len(list)+1) // 2
    a = list[index-1]

    if a > number : 
        list = list[0 : index]
        n_try += 1
        print('try: ', n_try, 'given number =', a)
        
    elif a < number : 
        list = list[index:]
        n_try += 1
        print('try: ', n_try, 'given number =', a)

n_try += 1
print('try: ', n_try, 'given number =', a)
print('total number of tries: ', n_try)