#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "config-manager/manager.h"
#include "log/syslog.h"

#define DEFAULT_CONF_FILE ".config"

static const char *conf_file = NULL;


int main(int argc, char **argv)
{
	int opt = 0;
	char path[PATH_MAX];

	while( (opt = getopt(argc, argv, "c:")) != -1)
	{
	switch(opt)
	{
	case 'c':
		if (optarg[0] == '/' || optarg[0] == '.' && optarg[1] == '.')
		{
			XINFO("You fucking shit! Don`t try to hack the server!");
			return -1;
		}
		conf_file = optarg;
		break;
	default:
		XINFO("Default option");
	}
	}

	if (!conf_file)
		conf_file = DEFAULT_CONF_FILE;
	config::ConfigManager manager(conf_file);

	XINFO("Server could be started on %d port", manager.getTcpPort());
}
