FROM ghcr.io/userver-framework/ubuntu-userver-build-base:v1 as build

COPY . /project
WORKDIR /project
RUN git submodule update --init && make build-release

FROM postgres:14.8 as main
COPY --from=build /project/build_release build_release
COPY --from=build /project/configs configs
COPY --from=build /project/run_prod.sh /docker-entrypoint-initdb.d/
COPY db/db.sql /docker-entrypoint-initdb.d/

ENV POSTGRES_PASSWORD=postgres
ENV POSTGRES_DB=forum

RUN chmod 777 /docker-entrypoint-initdb.d/run_prod.sh

EXPOSE 5000
