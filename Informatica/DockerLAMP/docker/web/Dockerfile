FROM php:8.4-apache

RUN apt-get update
RUN apt-get install -y libzip-dev libpng-dev libicu-dev

RUN docker-php-ext-install mysqli
RUN docker-php-ext-install pdo
RUN docker-php-ext-install pdo_mysql
RUN docker-php-ext-install exif
RUN docker-php-ext-install zip
RUN docker-php-ext-install intl
RUN docker-php-ext-install gd

EXPOSE 80

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]
