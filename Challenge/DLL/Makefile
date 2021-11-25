##################################################
# 単一パラメータ
OBJDIR = obj
SRCDIR = src
BINDIR = bin
PROGRAM = UqLib.dll

##################################################
# 複合パラメータ
OBJS = $(OBJDIR)/UqLib.o $(OBJDIR)/SystemClass.o $(OBJDIR)/DirectXManager.o
CFLAGS = -shared -O2
# -shared : DLL形式のライブラリ作成時に必要なコンパイルオプション
# -O2 : コンパイラはサイズとコンパイル時間に妥協せずにコードのパフォーマンスを改善しようと試みる

#WIN_LIB	= C:\Windows\SysWOW64
# WIN_LIBS= $(WIN_LIB)\user32.dll $(WIN_LIB)\gdi32.dll $(WIN_LIB)\kernel32.dll
#WIN_LIBS= $(WIN_LIB)\kernel32.dll
#LIBS = $(WIN_LIBS)
LDFLAGS=-mwindows
##################################################
# make

$(PROGRAM): $(OBJS)
	g++ $(CFLAGS) -o $(BINDIR)/$(PROGRAM) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CFLAGS) -o $@ -c $<

##################################################
# make clean

clean:
	del $(BINDIR)\$(PROGRAM)
	del $(OBJDIR)\*.o