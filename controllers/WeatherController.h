#pragma once
#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>
#include "models/City.h"
#include "models/Weather.h"

using namespace drogon;

class WeatherController : public HttpController<WeatherController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(WeatherController::GetAllCities, "/cities", Get);
    ADD_METHOD_TO(WeatherController::GetCityWeather, "/weather/{city}", Get);
    ADD_METHOD_TO(WeatherController::GetWeatherByCloudiness, "/weather/cloudiness/{type}", Get);
    METHOD_LIST_END

    void GetAllCities(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void GetCityWeather(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string& city);
    void GetWeatherByCloudiness(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string& cloudiness);
};
