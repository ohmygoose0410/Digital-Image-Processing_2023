# HW4 Image Restoration

**演算法**

- Image Restoration : Wiener Filter
- Point Spread Function : Motion, Gaussian

## 運行方式

**作業系統要求: Linux**

1.  首先打開terminal，並且確保當前路徑是在資料夾的根目錄，執行 "make" 進行編譯，在根目錄內會出現1個執行檔，為 ``main_restoration``

    ```bash
    make dir
    ```

2.  若要對影像做image restoration，執行下面的指令

    ```bash
    Usage: ./main_restoration [--help] [--version] [--goldenPath VAR] blurPath motionKernelSize motionKernelAngle motionK gaussianKernelSize gaussianSigma gaussianK

        Positional arguments:
        blurPath            Input blur image path 
        motionKernelSize    Motion kernel size 
        motionKernelAngle   Motion angle 
        motionK             Wiener filter K 
        gaussianKernelSize  Gaussian kernel size 
        gaussianSigma       Gaussian SD 
        gaussianK           Wiener filter K 

        Optional arguments:
        -h, --help          shows help message and exits 
        -v, --version       prints version information and exits 
        -gp, --goldenPath   Input original image path [nargs=0..1] [default: ""]
    ```

## Quick start

1. 若要對影像1做image restoration，執行

    ```bash
    ./main_restoration -gp ./testdata/input1_ori.bmp ./testdata/input1.bmp 23 -45 0.1 11 15 0.01
    ```

2. 若要對影像2做image restoration，執行

    ```bash
	./main_restoration ./testdata/input2.bmp 21 -45 0.04 11 10 0.005
    ```

最後產生得結果會放在根目錄

## 結果

| 原始影像 | Image Restoration |  
|:---:|:---:|
|<img src="testdata/input1.bmp" width="300">|<img src="result/output1.bmp" width="300">|
|<img src="testdata/input2.bmp" width="300">|<img src="result/output2.bmp" width="300">|
