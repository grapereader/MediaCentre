#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <syslog.h>

#include "Application.h"

#define VERSION "0.0.1"

int main(int argc, char **argv)
{
    std::cout << "Running ViaWare Control Server v" << VERSION << std::endl;

    int flag;
    bool daemon = false;
    char const *log = "/var/log/vmc.log";
    char const *config = "/etc/vmc/config.json";

    uid_t daemonUser = 0;
    gid_t daemonGroup = 0;

    while ((flag = getopt(argc, argv, "dl:c:u:g:")) != -1)
    {
        switch(flag)
        {
            case 'd':
                daemon = true;
                break;
            case 'l':
                log = optarg;
                break;
            case 'c':
                config = optarg;
                break;
            case 'u':
                daemonUser = atol(optarg);
                break;
            case 'g':
                daemonGroup = atol(optarg);
                break;
        }
    }

    openlog("vmc-application", LOG_PID, LOG_USER);

    if (daemon)
    {
        openlog("vmc-parent", LOG_PID, LOG_DAEMON);
        syslog(LOG_NOTICE, "Starting vmc daemon...");

        pid_t pid = fork();
        if (pid < 0)
        {
            syslog(LOG_NOTICE, "Could not fork");
        }

        if (pid > 0) exit(EXIT_SUCCESS);

        openlog("vmc", LOG_PID, LOG_DAEMON);

        umask(0);

        freopen(log, "a", stdout);

        pid_t sid = setsid();
        if (sid < 0)
        {
            syslog(LOG_NOTICE, "Could not setsid");
            exit(EXIT_FAILURE);
        }

        if (chdir("/") < 0)
        {
            syslog(LOG_NOTICE, "Could not chdir");
            exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDERR_FILENO);

        setgid(daemonGroup);
        setuid(daemonUser);
    }

    syslog(LOG_NOTICE, "Starting the vmc application...");
    vmc::Config conf(config);
    vmc::start(&conf);

    return 0;
}
