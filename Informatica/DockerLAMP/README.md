# Docker LAMP setup

Questa cartella contiene un setup minimale per uno stack LAMP
con Docker (più specificatamente Docker Compose).

## Configurazione

Il setup è configurabile con le seguenti variabili d'ambiente, messe in un apposito file `.env`:
- MYSQL_ROOT_PASSWORD (defualt: root): password root di MySQL
- MYSQL_DATABASE (default: database): database creato di default dal container di MySQL alla creazione
- MYSQL_USER (default: user): utente creato di default dal container di MySQL alla creazione con cui accedere a MYSQL_DATABASE
- MYSQL_PASSWORD (default: password): password dell' utente creato di default dal container di MySQL alla creazione con cui accedere a MYSQL_DATABASE

Per PHP è previsto un file di configurazione php.ini nella cartella php/

## Utilizzo

- Creazione e avvio dei container
```bash
docker compose up --build # -d per fare il detach della console dai log dei container
```

- Spegnimento dei container
```bash
docker compose down # -v per cancellare i volumi creati (database e mapping della cartella www per apache)
```
