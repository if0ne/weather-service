create table Cities (
    id SERIAL PRIMARY KEY,
    name varchar(255) UNIQUE NOT NULL
);

create table Weather (
    id SERIAL PRIMARY KEY,
    city_id INTEGER REFERENCES Cities(id) ON DELETE CASCADE,
    date DATE NOT NULL,
    temperature FLOAT NOT NULL,
    cloudiness VARCHAR(50) NOT NULL CHECK(cloudiness IN ('Облачно', 'Солнечно', 'Переменная облачность')),
    UNIQUE(city_id, date)
);