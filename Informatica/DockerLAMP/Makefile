.PHONY: up up-attached down down-volumes logs

COMPOSE := docker compose

up:
	@$(COMPOSE) up --build -d

up-attached:
	@$(COMPOSE) up --build

down:
	@$(COMPOSE) down

down-volumes:
	@$(COMPOSE) down -v

logs:
	@$(COMPOSE) logs
