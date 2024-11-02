#include <drogon/orm/DbClient.h>
#include <string>

struct City {
    inline static const std::string tableName = "cities";

    using PrimaryKeyType = int;
    static constexpr const char* primaryKeyName = "id";

    int id;
    std::string name;

    City() = default;

    City(const drogon::orm::Row& row) {
        id = row["id"].as<int>();
        name = row["name"].c_str();
    }
};