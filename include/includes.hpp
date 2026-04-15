#ifndef _INCLUDES_HPP_
#define _INCLUDES_HPP_

#include "cppfile.hpp"
#include "cppheader.hpp"
#include "cppsocket.hpp"
#include "yaml-cpp/yaml.h"

namespace op {
    inline static const std::string AUTH = "AUTH";
    inline static const std::string SYNC = "SYNC";
}

namespace re {
    inline static const std::string TRUE  = "TRUE";
    inline static const std::string FALSE = "FALS";
    inline static const std::string DONE  = "DONE";
}

inline static const int DEFAULT_PORT = 8080;

#if defined(WIN32) || defined(WIN64)
inline static const fs::path HOME           = std::getenv("USERPROFILE");
#else
inline static const fs::path HOME           = std::getenv("HOME");
#endif

inline static const fs::path SHARED_FOLDER     = HOME / ".local/share/tmid";
inline static const fs::path GROUPS_FOLDER     = SHARED_FOLDER / "groups";

inline static const fs::path CONFIG_FILE       = SHARED_FOLDER / "config.yaml";
inline static const YAML::Node CONFIG_TEMPLATE = YAML::Load(R"(
port: 8080
)");

inline static const std::string GROUP_CONFIG_FILENAME = "group_config.yaml";
inline static const YAML::Node GROUP_CONFIG_TEMPLATE  = YAML::Load(R"(
group_name: ""
group_description: ""
)");

inline static const std::string GROUP_PARTICIPANTS_FILENAME = "group_participants.yaml";
inline static const YAML::Node GROUP_PARTICIPANTS_TEMPLATE  = YAML::Load(R"(
participants: []
)");

#endif