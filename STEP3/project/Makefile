# 自定义依赖关系，源文件（后缀为.cpp)经过编译汇编生成目标文件（后缀为.o)
# 目标文件执行生成可执行文件（类似与bmpout）
#-c 只允许执行到汇编步骤，不允许链接。
# 写gcc命令时候，前面要tab按键一下
# 不写-o参数，生成默认的可执行文件名为a.out，这里我们修改为bmpout

# OBJS   代替  依赖文件
# CC     代替  g++
# CFLAGS 代替  编译命令
# $^ 代替 上面的指令
# RM 代替 rm -f
# $@ 代替 目标文件

OBJS=main.o bmp.o
CC=g++
CFLAGS=-c

bmpout:$(OBJS)
	$(CC) $(OBJS) -o $@
main.o : main.cpp
	$(CC) $^ $(CFLAGS) -o $@ 
bmp.o : bmp.h bmp.cpp
	$(CC) bmp.cpp $(CFLAGS) -o $@
clean:
	$(RM) *.o bmpout -r