# xchg_finder
Chrome沙箱逃逸的时候经常用到`xchg rsp, rax; ... ret;`形式的gadget，但是用ROPgadget找太慢了，于是用C写的小小小轮子。

## 编译

直接使用make指令编译。

## 运行效果

```
➜  xchg_finder ./xchg_finder ~/Desktop/mojo/chrome 
0x880dee8 (ret @ 0x880deec)
0x8c49bd2 (ret @ 0x8c49bd7)
0x8d078d6 (ret @ 0x8d078db)
0x901a564 (ret @ 0x901a56a)
0x93fdd94 (ret @ 0x93fdd99)
```

格式为`gadget起始地址 (ret指令预期所在的地址)`。

## 说明

1. 由于使用的是字符匹配来查找，所以很有可能找到的并不是有效gadget。但是挨个检验也比等ROPgadget快。

   ```
   		xchg rsp, rax         #4894 
   		rex.WR xchg rsp,rax   #4c94
   		ret                   #c3
   ```

2. 如果提供的地址保存的指令并不是xchg指令，试试将地址±0x1000再试试。



