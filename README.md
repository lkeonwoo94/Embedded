# Embedded
임베디드에 대해 학습해봅니다


---
> C 전처리문
```C
#define foo(x) #x    // # 연산자는 매개변수를 문자화 하는 연산자입니다              
#define foo(x) X##n   // ## 연산자는 토큰들을 결합합니다. X(1)이라고 하면 X1 변수를 입력한것과 동일합니다.
```

> Compiler vs Interpreter
```
             |       +----------+    +-------------+
   Translate |       | Compiler |    |             |
             v       +----------+    |             |
             |       +----------+    | Interpreter |
   Execute   |       |  Process |    |             |
             v       +----------+    +-------------+
              

```
> Build Process

```
<--------------------------------------------------------Build Process------------------------------------------------------>
        Compiler                     Linker     +-> map file         format converter
C/C++ -----------> Object file -------------------> ELF / DWARF -----------------------> hex file -----> Flash/ROM programmer
                  ^                                 ^
                  |                                 |
Assembly ---------+                                lib & 
          Assembler                            start-up code
```

---

> 역공학(Reversing) - Decompiler
```
+-----+                      +--------+
| ELF | ===> Decompiler ===> | C code |
+-----+                      +--------+
```
``` C/C++용 : IDA Hex-Rays(http://hex-rays.com) , REC(reverse engineering compiler)(http://www.backerstreet.com/rec/rec.htm) ```

> 역공학(Reversing) - Deassemble debugger
```
Tool : Ollydbg, IDA, W32DASM, Windbg, 
```

> 역공학(Reversing) - Disassembler
+-----+                        +-------------------+
| ELF | ===> Disassembler ===> | Assembly Language |
+-----+                        +-------------------+
```
``` 동일한 program이더라도 Compiler에 따라 동일한 binary로 변환되지 않는다. 따라서 역분석 전문가가 되기 위해서는 다양한 컴파일러를 통해 컴파일된 프로그램을 분석해 보아야 역분석을 원활히 진행할 수 다.``` 
