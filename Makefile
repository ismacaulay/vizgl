
ORG=ismacaulay
APP=vizgl
SERVER=wasm-react-router-server
BUILD_DIR=src/.build/wasm
WASM_FILE=$(BUILD_DIR)/vizgl.wasm
JS_FILE =$(BUILD_DIR)/vizgl.js

baseimage:
	docker build -t $(ORG)/$(APP) .

get-server:
	docker pull $(ORG)/$(SERVER)

run-server:
	docker run --rm -d \
		-v $(shell pwd)/www:/usr/share/nginx/html \
		-p 8080:80 \
		--name=$(SERVER) \
		$(ORG)/$(SERVER)

dev:
	docker run --rm -it \
		-v $(shell pwd):/usr/src/app \
		$(ORG)/$(APP)

install:
	cp $(WASM_FILE) $(JS_FILE) www/

watch: install
	watchman-make -p '$(WASM_FILE)' '$(JS_FILE)' -t install
