FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    useradd -m -d /home/challenge -s /bin/bash challenge


WORKDIR /home/challenge/

COPY [/home/mudwit/Desktop/DEVCTF/Parallel world] /home/challenge/
COPY [/home/mudwit/Desktop/DEVCTF/Parallel world/] /home/challenge/ 

RUN chmod +x problem


EXPOSE 4269

# Set ownership of the files to the "challenge" user
RUN chown -R challenge:challenge /home/challenge

# Run xinetd as a service to handle incoming connections, with user `challenge`
USER challenged

# Start xinetd service to run your pwn service
CMD ["/usr/sbin/xinetd", "-dontfork"]