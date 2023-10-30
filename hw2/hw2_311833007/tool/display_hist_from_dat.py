import matplotlib.pyplot as plt
import numpy as np

def main():
    lightness = open("lightness.dat")
    lightness_dat = lightness.readline()
    
    lightness_list = []
    while lightness_dat:
        lightness_list.append(int(lightness_dat))
        lightness_dat = lightness.readline()

    lightness_np = np.array(lightness_list)

    fig, ax = plt.subplots()
    ax.hist(lightness_np, bins=[i for i in range(256)])
    plt.show()


if __name__ == "__main__":
    main()