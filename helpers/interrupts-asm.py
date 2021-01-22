texts = []

for _ in range(10):
    texts.append("add x0, x0, x0")

texts.append("jal zero, intr_id" + str(10))

for _ in range(4):
    texts.append("add x0, x0, x0")

texts.append("jal zero, intr_id" + str(15))

for _ in range(16):
    texts.append("add x0, x0, x0")

print("\n".join(texts))