import sympy
import time

# https://math.stackexchange.com/questions/2748541/is-this-set-of-solutions-complete/2829493


table27 = [True] * 50
table25 = [True] * 50
table49 = [True] * 50
table11 = [True] * 50
table13 = [True] * 50
table17 = [True] * 50
table19 = [True] * 50
table23 = [True] * 50
table29 = [True] * 50


def init():
    original_time = time.process_time()
    for a in range(50):
        if a % 3 != 1 and a not in [0, 9]:
            table27[a] = False
        if a % 5 not in [1, 4] and a != 0:
            table25[a] = False
        if a % 7 not in [1, 2, 4] and a != 0:
            table49[a] = False
        if a not in [0, 1, 3, 4, 5, 9]:
            table11[a] = False
        if a not in [0, 1, 3, 4, 9, 10, 12]:
            table13[a] = False
        if a not in [0, 1, 2, 4, 8, 9, 13, 15, 16]:
            table17[a] = False
        if a not in [0, 1, 4, 5, 6, 7, 9, 11, 16, 17]:
            table19[a] = False
        if a not in [0, 1, 2, 3, 4, 6, 8, 9, 12, 13, 16, 18]:
            table23[a] = False
        if a not in [0, 1, 4, 5, 6, 7, 9, 13, 16, 20, 22, 23, 24, 25, 28]:
            table29[a] = False
    print('init() function: ' + time.process_time() - original_time)


def is_square(apositiveint):
    if apositiveint % 8 != 1:
        return False
    if not table27[apositiveint % 27]:
        return False
    if not table25[apositiveint % 25]:
        return False
    if not table49[apositiveint % 49]:
        return False
    if not table11[apositiveint % 11]:
        return False
    if not table13[apositiveint % 13]:
        return False
    if not table17[apositiveint % 17]:
        return False
    if not table19[apositiveint % 19]:
        return False
    if not table23[apositiveint % 23]:
        return False
    if not table29[apositiveint % 29]:
        return False
    xx = apositiveint // 2
    seen = xx
    seen2 = None
    while xx * xx != apositiveint:
        xx = (xx + (apositiveint // xx)) // 2
        if xx == seen or xx == seen2:
            return False
        seen2 = seen
        seen = xx
    return True


# Check for the case where two of exponents are (2, 4)
# Estimated time: ~15 hours
def check1():
    original_time = time.process_time()
    x = 1
    nn = []
    # https://en.wikipedia.org/wiki/Beal_conjecture#Partial_results
    for i in range(2, 7):
        nn.append(2 ** i)
    nn.append(2 ** 11)
    nn.append(2 ** 13)
    nn.append(2 ** 14)
    for i in range(17, 97, 2):
        nn.append(2 ** i)
    while x < 5301000000:
        if x % 10000000 == 0:
            print(x)
            print(time.process_time())
        if sympy.ntheory.primetest.isprime(x) is True:
            for n in nn:
                if is_square(n + x ** 3) is not False:
                    print(n, x, n + x ** 3)
                if is_square(abs(n - x ** 3)) is not False:
                    print(n, x, n - x ** 3)
        x += 1
    print('check1() function: ' + time.process_time() - original_time)


# Check for the case where two of exponents are (2, 4)
# Estimated time: <1 seconds
def check2():
    original_time = time.process_time()
    x = 1
    nn = []
    for i in range(2, 53):
        nn.append(2 ** i)
    while x < 8700:
        if sympy.ntheory.primetest.isprime(x) is True:
            for n in nn:
                if is_square(n + x ** 4) is not False:
                    print(n, x, n + x ** 4)
                if is_square(abs(n - x ** 4)) is not False:
                    print(n, x, n - x ** 4)
        x += 1
    print('check2() function: ' + time.process_time() - original_time)


# Check for the case where two of exponents are (2, 5)
# Estimated time: <1 seconds
def check3():
    original_time = time.process_time()
    x = 1
    nn = []
    for i in range(2, 39):
        nn.append(2 ** i)
    while x < 202:
        if sympy.ntheory.primetest.isprime(x) is True:
            for n in nn:
                if is_square(n + x ** 5) is not False:
                    print(n, x, n + x ** 5)
                if is_square(abs(n - x ** 5)) is not False:
                    print(n, x, n - x ** 5)
        x += 1
    print('check3() function: ' + time.process_time() - original_time)


# Check for the case where two of exponents are not (2, 3), (2, 4), (2, 5)
# Estimated time: ~15 seconds
def checkFinal():
    original_time = time.process_time()
    x = 3
    limit = 2750000000
    nn = []
    for i in range(2, 32):
        nn.append(2 ** i)
    while x * x < limit:
        if sympy.ntheory.primetest.isprime(x) is True:
            xx = x * x
            while xx < limit:
                for n in nn:
                    if sympy.ntheory.perfect_power(n + xx) is not False:
                        print(x, xx, n, n + xx)
                    if sympy.ntheory.perfect_power(abs(n - xx)) is not False:
                        print(x, xx, n, n - xx)
                xx *= x
        x += 1
    print('checkFinal() function: ' + time.process_time() - original_time)


if __name__ == '__main__':
    init()
    check1()
    check2()
    check3()
    checkFinal()
