#!/bin/bash
# entrypoint.sh
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html
apache2-foreground
