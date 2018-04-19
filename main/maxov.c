/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "sio.h"

void app_main()
{
    if(sio_init() == ESP_OK) {
      xTaskCreatePinnedToCore(sio_task, "sioTask", 2048, NULL, 5, NULL, 1);
      printf("Ready.\n");
    }
    vTaskDelete(NULL);
}
