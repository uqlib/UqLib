##################################################
# 単一パラメータ
OBJDIR = obj
SRCDIR = src
BINDIR = bin
PROGRAM = main.exe

##################################################
# 複合パラメータ
OBJS = $(OBJDIR)/main.o
CFLAGS = -Wall -O2
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