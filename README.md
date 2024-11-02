# WeatherService

## Запуск

1. Установите [Docker](https://www.docker.com/)
2. ```git clone https://github.com/if0ne/weather-service.git```
3. ```cd weather-service```
4. ```docker compose up -d --build```

## Админка

1. Зайдите по адресу _http://localhost:5555_

    * Логин: admin@admin.com
    * Пароль: admin

2. Зарегистрируйте сервер с параметрами:
    
    * _Host name/address_: db
    * _Port_: 5432
    * _Maintenance database_: weather_db
    * _Username_: postgres
    * _Password_: postgres

## API

* **Запрос всех городов**

```http://localhost:8002/cities```

* **Запрос на получение погоды для города**

```http://localhost:8002/weather/{city}```

* **Запрос на получение погоды по параметру "облачности"**

```http://localhost:8002/weather/cloudiness/{type}```