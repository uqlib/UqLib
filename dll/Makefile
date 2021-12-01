##################################################
# 単一パラメータ
OBJDIR = UqLib\x64\Gcc
SRCDIR = UqLib
BINDIR = x64\Debug
PROGRAM = UqLib.dll

##################################################
# 複合パラメータ
OBJS = $(OBJDIR)/UqLib.o $(OBJDIR)/SystemClass.o $(OBJDIR)/DirectXManager.o $(OBJDIR)/GraphicsManager.o $(OBJDIR)/SoundManager.o $(OBJDIR)/FileManager.o $(OBJDIR)/Logger.o
CFLAGS = -shared -O2
# -shared : DLL形式のライブラリ作成時に必要なコンパイルオプション
# -O2 : コンパイラはサイズとコンパイル時間に妥協せずにコードのパフォーマンスを改善しようと試みる

LIBS = -lole32 -luuid -ldxgi -ld3d11 -ld2d1 -ldwrite -lWindowsCodecs -ldxguid -ldsound -lwinmm
LDFLAGS=-mwindows
##################################################
# make

$(PROGRAM): $(OBJS)
	g++ $(CFLAGS) -o $(BINDIR)/$(PROGRAM) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CFLAGS) -o $@ -c $<

##################################################
# make clean

clean:
	del $(BINDIR)\$(PROGRAM)
	del $(OBJDIR)\*.o