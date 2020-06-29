LLVM_PATH = #use your llvm path here
LLVM_BIN_PATH = $(LLVM_PATH)/build/bin
CFIHello_So_PATH = $(LLVM_PATH)/build/lib/LLVMCFIHello.so
CC1 = $(LLVM_PATH)/build/bin/clang -fPIC -fno-asynchronous-unwind-tables -fno-addrsig -mstackrealign -Xclang -load -Xclang $(CFIHello_So_PATH)
CC1A = $(LLVM_PATH)/build/bin/clang
CC2 = clang -fPIC -fno-asynchronous-unwind-tables -mstackrealign
CC2A = clang

TARGET_NAME = bench

all:
	$(CC1) -S $(TARGET_NAME).c -o $(TARGET_NAME).s
	$(CC1A) -c $(TARGET_NAME).s -o $(TARGET_NAME).o
	clang -c transactionBegin.s -o transactionBegin.o
	clang -c external.c -o external.o
	@fallocate -l 100K ssblob
	@objcopy --add-section .ssblob=ssblob --set-section-flags .ssblob=alloc,data,code $(TARGET_NAME).o
	$(CC1A) $(TARGET_NAME).o external.o transactionBegin.o shadowstack.lds -o $(TARGET_NAME)

clean:
	rm -f $(TARGET_NAME).s $(TARGET_NAME).o external.o transactionBegin.o ssblob $(TARGET_NAME)