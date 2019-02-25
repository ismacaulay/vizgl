
BUILD_DIR=.build/src/wasm
WASM_FILE=$(BUILD_DIR)/index.wasm
JS_FILE =$(BUILD_DIR)/index.js

install:
	cp $(WASM_FILE) $(JS_FILE) www/

watch: install
	watchman-make -p '$(WASM_FILE)' '$(JS_FILE)' -t install
