ESP_IDF_DIR := esp-idf
ESP_IDF_COMMIT := $(shell cat esp-idf.commit)

.PHONY: esp-idf check-esp-idf update-esp-idf clean

## Clone esp-idf if missing and checkout pinned commit
esp-idf:
	@if [ ! -d "$(ESP_IDF_DIR)" ]; then \
		echo "Cloning ESP-IDF..."; \
		git clone --recursive https://github.com/espressif/esp-idf.git $(ESP_IDF_DIR); \
	fi
	@cd $(ESP_IDF_DIR) && \
		git fetch && \
		git checkout $(ESP_IDF_COMMIT) && \
		git submodule update --init --recursive

## Verify esp-idf is at the expected commit
check-esp-idf:
	@cd $(ESP_IDF_DIR) && \
		current=$$(git rev-parse HEAD); \
		if [ "$$current" != "$(ESP_IDF_COMMIT)" ]; then \
			echo "ERROR: esp-idf at $$current, expected $(ESP_IDF_COMMIT)"; \
			exit 1; \
		fi
	@echo "esp-idf is at expected commit $(ESP_IDF_COMMIT)"

## Update esp-idf.commit to the current checked-out commit
update-esp-idf:
	@cd $(ESP_IDF_DIR) && git rev-parse HEAD > ../esp-idf.commit
	@echo "Updated esp-idf.commit"

## Remove local esp-idf clone
clean:
	rm -rf $(ESP_IDF_DIR)
