##################################################
# 単一パラメータ
OBJDIR = obj
SRCDIR = src
BINDIR = bin
PROGRAM = UqLibCppSample.exe

##################################################
# 複合パラメータ
OBJS = $(OBJDIR)/GameMain.o
CFLAGS = -Wall -O2 -Wl,-subsystem,windows
# -Wall : 全ての警告を出力する
# -O2 : コンパイラはサイズとコンパイル時間に妥協せずにコードのパフォーマンスを改善しようと試みる

##################################################
# make

$(PROGRAM): $(OBJS)
	g++ $(CFLAGS) -o $(BINDIR)/$(PROGRAM) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CFLAGS) -o $@ -c $<

##################################################
# make clean

clean:
	del $(BINDIR)\$(PROGRAM)
	del $(OBJDIR)\*.o