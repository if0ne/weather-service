#pragma once
#include <drogon/orm/DbClient.h>
#include <string>

struct Weather {
    inline static const std::string tableName = "weather";

    using PrimaryKeyType = int;
    static constexpr const char* primaryKeyName = "id";

    int id;
    int city_id;
    std::string date;
    float temperature;
    std::string cloudiness;

    Weather() = default;

    Weather(const drogon::orm::Row& row) {
        id = row["id"].as<int>();
        city_id = row["city_id"].as<int>();
        date = row["date"].c_str();
        temperature = row["temperature"].as<float>();
        cloudiness = row["cloudiness"].c_str();
    }
};
