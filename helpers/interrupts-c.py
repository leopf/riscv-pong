texts = []
for i in range(32):
    texts.append("void intr_id" + str(i) + "() { asm(\"mret\"); }")

print("\n".join(texts))