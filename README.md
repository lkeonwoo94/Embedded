# Embedded
임베디드에 대해 학습해봅니다


---
> C 전처리문
```C
#define foo(x) #x    // # 연산자는 매개변수를 문자화 하는 연산자입니다
#define foo(x) X##n   // ## 연산자는 토큰들을 결합합니다. X(1)이라고 하면 X1 변수를 입력한것과 동일합니다.
```

---

> 역공학(Reversing) - Decompiler
```
+-----+                      +--------+
| ELF | ===> Decompiler ===> | C code |
+-----+                      +--------+
```
```C/C++용 : IDA Hex-Rays(http://hex-rays.com) , REC(reverse engineering compiler)(http://www.backerstreet.com/rec/rec.htm)
