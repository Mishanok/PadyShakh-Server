#include <iostream>
#include <fstream>
#include <string.h>
#include <cassert>

#include "manager.h"
#include "log/syslog.h"

namespace config
{

ConfigManager::ConfigManager(const char *conf_file)
{
	XINFO("CSTR: ConfManager");
	strcpy(m_conf_file, conf_file);
	initConfManager();
	XINFO("CSTR: ConfManager out");
}

void ConfigManager::initConfManager()
{
	XINFO("Hi, I am config manager initializer");

	assert(this->parseConfigs());
}

bool ConfigManager::parseConfigs()
{
	XINFO("Start parsing config file");
	std::ifstream file(m_conf_file);
	std::string str;
	std::string config;
	const std::string delimiter = ": ";
	size_t pos = 0;

	if (file.is_open())
	{
		while (std::getline(file, str))
		{
			XINFO("received line %s", str.c_str());

			if ( (pos = str.find(delimiter)) != std::string::npos)
			{
				config = str.substr(0, pos);
				XINFO("Config %s", config.c_str());
				str.erase(0, pos + delimiter.length());
			}

			if (str.find(delimiter) != std::string::npos)
				goto BAD_CONFIG;

			XINFO("Value %s", str.c_str());

			if (config == "TCP_PORT")
			{
				m_conf.tcp_port = std::stoi(str);
				XINFO("Retrieved port: %d", m_conf.tcp_port);
				if (m_conf.tcp_port < 100 || m_conf.tcp_port > 655565)
				{
					XINFO("TCP Port is out of range");
					goto BAD_CONFIG;
				}
			}
			else
			goto BAD_CONFIG;
		}

		return true;
	}
	else
	{
		XINFO("Cannot open file %s", m_conf_file);
	}

BAD_CONFIG:
	XINFO("Config file is WRONG!");
	return false;
}

}
