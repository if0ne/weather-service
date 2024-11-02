INSERT INTO public.cities(id, name) VALUES 
    (1, 'Москва'),
    (2, 'Питер');

INSERT INTO public.weather(city_id, date, temperature, cloudiness) VALUES 
    (1, '2022-01-01', 24.5, 'Облачно'),
    (1, '2022-06-01', 24.5, 'Солнечно'),
    (2, '2022-01-01', 24.5, 'Облачно'),
    (2, '2022-02-01', 31.5, 'Облачно');