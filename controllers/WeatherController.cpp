#include "WeatherController.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/orm/DbClient.h>

#include <optional>

#include "models/Weather.h"

using namespace drogon::orm;

void ValidateCloudiness(const std::string& cloudiness) {
    if (cloudiness == "Облачно") return;
    if (cloudiness == "Солнечно") return;
    if (cloudiness == "Переменная облачность") return;

    throw std::invalid_argument("Wrong value. Expected \"Облачно\", \"Солнечно\", \"Переменная облачность\"");
}

void WeatherController::GetAllCities(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto dbClient = app().getDbClient();
    Mapper<City> cityMapper(dbClient);

    auto cities = cityMapper.findAll();

    Json::Value cityList(Json::arrayValue);
    for (const auto& city : cities) {
        cityList.append(city.name);
    }

    auto resp = HttpResponse::newHttpJsonResponse(cityList);
    callback(resp);
}

void WeatherController::GetCityWeather(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string& city) {
    auto dbClient = app().getDbClient();
    Mapper<City> cityMapper(dbClient);
    Mapper<Weather> weatherMapper(dbClient);

    try {
        auto foundCity = cityMapper.findOne(Criteria("name", city));
        auto weathers = weatherMapper.findBy(Criteria("city_id", foundCity.id));

        Json::Value result;
        result["city"] = foundCity.name;
        for (const auto& weather : weathers) {
            Json::Value day;
            day["date"] = weather.date;
            day["temperature"] = weather.temperature;
            day["cloudiness"] = weather.cloudiness;
            result["days"].append(day);
        }

        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);
    } catch(const std::exception& e) {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value(e.what()));
        resp->setStatusCode(k404NotFound);
        callback(resp);
    }
}

void WeatherController::GetWeatherByCloudiness(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string& cloudiness) {
    auto dbClient = app().getDbClient();

    try {
        ValidateCloudiness(cloudiness);

        std::string query = 
            "SELECT cities.name AS city_name, weather.date, weather.temperature, weather.cloudiness "
            "FROM weather "
            "INNER JOIN cities ON weather.city_id = cities.id "
            "WHERE weather.cloudiness = $1";

        auto result = dbClient->execSqlSync(query, cloudiness);
        Json::Value resultJson(Json::arrayValue);
        std::unordered_map<std::string, Json::Value> cityWeather;

        for (const auto& row : result) {
            std::string cityName = row["city_name"].c_str();

            Json::Value dayData;
            dayData["date"] = row["date"].c_str();
            dayData["temperature"] = row["temperature"].as<float>();
            dayData["cloudiness"] = row["cloudiness"].c_str();
            cityWeather[cityName]["days"].append(dayData);
        }

        for (const auto& [cityName, cityData] : cityWeather) {
            Json::Value cityEntry;
            cityEntry["city"] = cityName;
            cityEntry["days"] = cityData["days"];
            resultJson.append(cityEntry);
        }

        auto resp = HttpResponse::newHttpJsonResponse(resultJson);
        callback(resp);
    } catch (const std::invalid_argument& e) {
        Json::Value result;
        result["error"] = e.what();
        auto resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(resp);
    } catch(const std::exception& e) {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value(e.what()));
        resp->setStatusCode(HttpStatusCode::k500InternalServerError);
        callback(resp);
    }
}
