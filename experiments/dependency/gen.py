from numpy.random import rand, randint

for file_id in range(50):
    with open('./random-1304-' + str(file_id) + '.txt', 'w') as f:
        f.write('pooled')
        f.write('\n')
        for rel in range(7):
            t = ';' if rand() < 0.5 else ';;'
            bit_a = randint(0, 15)
            bit_b = randint(0, 15)
            f.write(str(bit_a) + t + str(bit_b))
            f.write('\n')
