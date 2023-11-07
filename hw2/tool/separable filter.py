import numpy as np
import math

def main():
    matrix_size = 10
    output_size = matrix_size - 5 + 1
    const = math.floor(5 / 2)
    hv = np.array([[1,3,5,3,1]])
    vv = hv.transpose()

    kernel = np.outer(hv, vv)
    oMat = np.random.randint(20, size=(matrix_size, matrix_size))
    convMat = np.zeros((output_size, output_size), dtype=int)
    tempMat = np.zeros((matrix_size, matrix_size), dtype=int)
    sepaMat = np.zeros((matrix_size, matrix_size), dtype=int)

    multiply_cnt = 0
    for rol in range(const, matrix_size-const):
        for col in range(const, matrix_size-const):
            convMat[rol-const, col-const] = np.sum(np.dot(oMat[rol-const:rol+const+1, col-const:col+const+1],
                                                       kernel))
            multiply_cnt += 25

    print(convMat)
    print("multiply operation: ", multiply_cnt)

    multiply_cnt = 0
    for row in range(const, matrix_size-const):
        for col in range(matrix_size):
            # sum((5x1) dot (1x5))
            tempMat[row,col] = np.sum(np.dot(oMat[row-const:row+const+1, col:col+1], hv))
            multiply_cnt += 3

    for col in range(const, matrix_size-const):
        for row in range(matrix_size):
            # (1x5) dot (5x1) -> 1x1
            sepaMat[row,col] = np.dot(tempMat[row:row+1, col-const:col+const+1], vv)
            multiply_cnt += 3

    print(sepaMat[const:-const,const:-const])
    print("multiply operation: ", multiply_cnt)

if __name__ == "__main__":
    main()