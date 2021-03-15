#ifndef __SYSLOG__
#define __SYSLOG__

#define XINFO(format, ...) \
	fprintf(stdout, "%s:%s:%d", __FILE__, __func__,__LINE__); \
	fprintf(stdout, " " format "\n", ##__VA_ARGS__);

#endif
