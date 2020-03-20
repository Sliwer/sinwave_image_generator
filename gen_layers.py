import random
import sys

file_path = 'layer_data.txt'

# l = number of layers
def random_gen(l):
    # Clear the file before writing the new content
    with open(file_path, 'w') as f:
        f.write('')
    with open(file_path, 'a') as f:
        for _ in range(0, l):
            # Rand only generates int but we want values from 0.0 to 2.0
            x_mod = random.randrange(0, 200) / 200
            y_mod = random.randrange(0, 200) / 200

            # Same thing but the scale of the layer cannot be 0
            s_mod = random.randrange(1, 200) / 200

            f.write(" {} {} {}".format(x_mod, y_mod, s_mod))


if __name__ == "__main__":
    # Generate some random data and write it in a file
    random_gen(int(sys.argv[1]))



            