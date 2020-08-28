.class public Exemplo2
.super java/lang/Object

.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method


.method public static imprime(I)I
	.limit stack 20
	.limit locals 2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload 0
	invokevirtual java/io/PrintStream/println(I)V
	iload 0
	iconst_1
	iadd
	ireturn
Label0:
	return
.end method


.method public static main([Ljava/lang/String;)V
	.limit stack 8
	.limit locals 4
	iconst_1
	istore 1
	iconst_2
	istore 2
	iload 1
	iload 2
	iadd
	istore 1
	iload 1
	invokestatic Exemplo2.imprime(I)I
	istore 2
	return
.end method
