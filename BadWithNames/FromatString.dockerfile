FROM ubuntu:20.04

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m -d /home/challenge -s /bin/bash challenge


WORKDIR /home/challenge/

COPY ["NameProblem" , "/home/challenge/"]
COPY ["flag.txt", "/home/challenge/"]

RUN chmod +x NameProblem
COPY xinetd_config.d /etc/xinted.d/challenge

EXPOSE 4569

# Set ownership of the files to the "challenge" user
RUN chown -R challenge:challenge /home/challenge

# Run xinetd as a service to handle incoming connections, with user `challenge`
USER challenge

# Start xinetd service to run your pwn service
CMD ["/usr/sbin/xinetd", "-dontfork"]