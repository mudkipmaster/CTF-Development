# Use a minimal base image
FROM debian:latest

# Install necessary packages
RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*

# Create a non-root user (ctfuser)
RUN useradd -m -s /bin/bash ctfuser

# Set up working directory
WORKDIR /home/ctfuser

# Copy the binary and flag into the container
COPY BadWithNames /home/ctfuser/BadWithNames
COPY flag.txt /home/ctfuser/flag.txt

# Secure the files by making them immutable and owned by root
RUN chmod 555 /home/ctfuser/BadWithNames && \
    chmod 444 /home/ctfuser/flag.txt && \
    chown root:root /home/ctfuser/BadWithNames /home/ctfuser/flag.txt && \
    chattr +i /home/ctfuser/BadWithNames /home/ctfuser/flag.txt

# Ensure ctfuser's home directory is not writable
RUN chown root:root /home/ctfuser && chmod 755 /home/ctfuser

# Expose port
EXPOSE 1337

# Run socat to serve the binary
CMD su ctfuser -c "socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/home/ctfuser/BadWithNames"
