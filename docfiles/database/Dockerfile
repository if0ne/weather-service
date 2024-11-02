FROM postgres:17
EXPOSE 5432

COPY sql/01_create_tables.sql /docker-entrypoint-initdb.d
COPY sql/02_insert_data.sql /docker-entrypoint-initdb.d