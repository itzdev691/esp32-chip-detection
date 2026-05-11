#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_psram.h"
#include <stdio.h>

const char* detect_esp32s3_variant() {
    uint32_t flash_size = 0;
    uint32_t psram_size = 0;
    
    // Get flash size
    esp_flash_get_size(NULL, &flash_size);
    flash_size /= (1024 * 1024); // Convert to MB
    
    // Get PSRAM size
    psram_size = esp_psram_get_size() / (1024 * 1024); // Convert to MB
    
    // Detect variant based on memory configuration
    if (flash_size == 0 && psram_size == 0) {
        return "ESP32-S3";
    }
    else if (flash_size == 8 && psram_size == 0) {
        return "ESP32-S3FN8";
    }
    else if (flash_size == 0 && psram_size == 2) {
        return "ESP32-S3RH2";
    }
    else if (flash_size == 0 && psram_size == 8) {
        return "ESP32-S3R8 or ESP32-S3R8V";
    }
    else if (flash_size == 0 && psram_size == 16) {
        return "ESP32-S3R16V";
    }
    else if (flash_size == 4 && psram_size == 2) {
        return "ESP32-S3FH4R2";
    }
    else {
        return "Unknown variant or external memory";
    }
}

void app_main() {
    printf("Chip variant: %s\n", detect_esp32s3_variant());
}