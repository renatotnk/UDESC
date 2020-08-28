.class public algumacoisa
.super java/lang/Object

.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method


.method public static fat(I)I
	.limit stack 20
	.limit locals 3
	iconst_1
	istore 1
Label1:
	iload 0
	bipush 0
	if_icmpgt Label2
	goto Label3
Label2:
	iload 1
	iload 0
	imul
	istore 1
	iload 0
	iconst_1
	isub
	istore 0
	goto Label1
Label3:
Label0:
	return
.end method


.method public static main([Ljava/lang/String;)V
	.limit stack 8
	.limit locals 4
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "Valor:"
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokevirtual java/io/InputStream/read()I
	istore 1
	iload 1
	invokestatic algumacoisa.fat(I)I
	istore 2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload 2
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
