#ifndef __CONF_MANAGER__
#define __CONF_MANAGER__
#include <stdint.h>

namespace config
{
typedef struct config_s {
	uint32_t tcp_port;
} config_t;

class ConfigManager
{
	public:
	ConfigManager(const char *conf_file);
	uint32_t getTcpPort() {return m_conf.tcp_port;};

	private:
	void initConfManager();
	bool parseConfigs();

	char m_conf_file[128];
	config_t m_conf;
};

}
#endif
