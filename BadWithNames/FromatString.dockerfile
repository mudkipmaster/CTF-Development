# Use a minimal base image
FROM debian:latest

# Install necessary packages
RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*

# Create a non-root user with restricted permissions
RUN useradd -m -s /bin/bash ctfuser

# Set up working directory
WORKDIR /home/ctfuser

# Copy the binary into the container and set correct permissions
COPY industry-guidelines /home/ctfuser/industry-guidelines
RUN chmod 555 /home/ctfuser/industry-guidelines && chown -R ctfuser:ctfuser /home/ctfuser

# Expose port
EXPOSE 1337

# Run socat to serve the binary
CMD su ctfuser -c "socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/home/ctfuser/industry-guidelines"