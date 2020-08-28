.class public testeBasico
.super java/lang/Object

.method public <init>()V
   aload_0

   invokenonvirtual java/lang/Object/<init>()V
   return
.end method

.method public static main([Ljava/lang/String;)V
   .limit stack 2
   .limit locals 4
   iconst_1
   istore 1
   bipush 20
   istore 2
   iload 2
   iload 1
   iadd
   iconst_2
   imul
   istore 3
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 3
   invokevirtual java/io/PrintStream/println(I)V
   return
.end method
