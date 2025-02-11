service challenge
{
    disable         = no
    socket_type     = stream
    protocol        = tcp
    wait            = no
    user            = root
    server          = /home/challenge/problem
    type            = UNLISTED
    port            = 4569
    bind            = 127.0.0.1
    banner_fail     = /etc/banner_fail
    per_source      = 10
    rlimit_cpu      = 60
    rlimit_as       = 512M
}
