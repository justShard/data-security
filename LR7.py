import math

# Функція для швидкого піднесення до степеня за модулем
def mod_exp(base, exp, mod):
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp = exp >> 1
        base = (base * base) % mod
    return result

# Функція для обчислення оберненого за модулем за допомогою малої теореми Ферма
def mod_inverse(base, mod):
    return mod_exp(base, mod - 2, mod)

# Функція для реалізації алгоритму Baby-step Giant-step
def baby_step_giant_step(G, H, Q):
    m = math.isqrt(Q) + 1  # Обчислюємо приблизне m як sqrt(Q)
    
    # Baby-step: обчислюємо та зберігаємо значення G^j % Q для j = 0, 1, ..., m-1
    value_map = {}
    for j in range(m):
        value = mod_exp(G, j, Q)
        value_map[value] = j

    # Precompute G^(-m) % Q (модульно обернене для G^m)
    Gm_inv = mod_exp(G, m * (Q - 2), Q)  # Еквівалент G^(-m) % Q

    # Giant-step: перевіряємо для i = 0, 1, ..., m-1 чи H * G^(-im) % Q є у мапі
    cur_value = H
    for i in range(m):
        if cur_value in value_map:
            j = value_map[cur_value]
            return i * m + j  # Рішення: X = i * m + j
        # Переходимо до наступного кроку Giant-step
        cur_value = (cur_value * Gm_inv) % Q

    return -1  # Якщо рішення не знайдено

# Вхідні дані: публічні ключі (G, H, Q)
G, H, Q = map(int, input().split())

# Знаходимо секретний ключ Аліси X за допомогою алгоритму Baby-step Giant-step
secret_key = baby_step_giant_step(G, H, Q)

# Виводимо секретний ключ X
print(secret_key)
