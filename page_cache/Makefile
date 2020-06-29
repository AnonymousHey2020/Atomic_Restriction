LLVM_PATH = #use your llvm path here
LLVM_BIN_PATH = $(LLVM_PATH)/build/bin
CFIHello_So_PATH = $(LLVM_PATH)/build/lib/LLVMCFIHello.so
CC = $(LLVM_PATH)/build/bin/clang -fPIC -fno-asynchronous-unwind-tables -fno-addrsig -mstackrealign -Xclang -load -Xclang $(CFIHello_So_PATH) -O0
CCA = $(LLVM_PATH)/build/bin/clang

TARGET_NAME = bench_branch

all:
	$(CC) -S $(TARGET_NAME).c -o $(TARGET_NAME).s
	$(CCA) -c $(TARGET_NAME).s -o $(TARGET_NAME).o
	clang -c preload.c -o preload.o
	clang -c extern.c -o extern.o
	clang -c transactionBegin.s -o transactionBegin.o
	$(CCA) preload.o extern.o transactionBegin.o $(TARGET_NAME).o -o $(TARGET_NAME)

clean:
	rm -f $(TARGET_NAME).s $(TARGET_NAME).o preload.o transactionBegin.o $(TARGET_NAME)