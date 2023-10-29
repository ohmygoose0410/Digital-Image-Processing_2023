作業系統要求: Windows

step 1. 首先打開powershell，並且確保當前路徑是在資料夾的根目錄，執行下面指令 "make directories"，makefile會自動建立3個資料夾分別為bin、dep 和 obj

step 2. 接著執行 "make" 進行編譯，在bin的資料夾內會出現3個執行檔，分別為main_flip.exe、main_quan.exe 和 main_scaling.exe

step 3. 若要對影像做翻轉，執行
	./bin/main_flip.exe ./input1.bmp ./input2.bmp

	若要對影像做quantization，執行
	./bin/main_quan.exe ./input1.bmp ./input2.bmp

	若要對影像做縮放，執行
	./bin/main_scaling.exe ./input1.bmp ./input2.bmp

	最後產生得結果會放在根目錄

step 4. 若要清除所有編譯過後所產生的資料如: *.exe、*.o 和 *.d，請執行 "make cleanw"

.
└── hw1_311833007/
    ├── bin/
    │   ├── main_flip.exe
    │   ├── main_quan.exe
    │   └── main_scaling.exe
    ├── dep/
    │   ├── bitmap.d
    │   ├── main_flip.d
    │   ├── main_quan.d
    │   └── main_scaling.d
    ├── obj/
    │   ├── bitmap.o
    │   ├── main_flip.o
    │   ├── main_quan.o
    │   └── main_scaling.o
    ├── img/
    │   ├── output1_1.bmp
    │   ├── output1_2.bmp
    │   ├── output1_3.bmp
    │   ├── output1_down.bmp
    │   ├── output1_up.bmp
    │   ├── output1_flip.bmp
    │   ├── output2_1.bmp
    │   ├── output2_2.bmp
    │   ├── output2_3.bmp
    │   ├── output2_down.bmp
    │   ├── output2_up.bmp
    │   └── output2_flip.bmp
    ├── report/
    │   └── report.pdf
    ├── bitmap.cpp
    ├── bitmap.h
    ├── input1.bmp
    ├── input2.bmp
    ├── main_flip.cpp
    ├── main_quan.cpp
    ├── main_scaling.cpp
    └── ReadMe.txt