#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "pins.h"
#include "sio.h"

esp_err_t sio_init() {
  esp_err_t err_code;
  const uart_config_t uart_config = {
    .baud_rate = SIO_BAUD_RATE,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  
  // initialize the UART
  uart_param_config(SIO_UART, &uart_config);
  uart_set_pin(SIO_UART, SIO_DATA_IN, SIO_DATA_OUT, UART_PIN_NO_CHANGE,
      UART_PIN_NO_CHANGE);
  err_code = uart_driver_install(SIO_UART, SIO_RX_BUF_SIZE*2, 0, 0, NULL, 0);
  
  // initialize GPIO pins
  gpio_set_direction(SIO_COMMAND, GPIO_MODE_DEF_INPUT);
  return err_code;
}

void sio_task() {
  static const char *SIO_TASK_TAG = "SIO_TASK";
  uint8_t cmd_state = 99;
  uint8_t prev_cmd_state = 99;
  uint8_t rx_bytes = 0;
  uint8_t *rx_buf = (uint8_t *)malloc(SIO_RX_BUF_SIZE);
  if(rx_buf == NULL) {
    ESP_LOGE(SIO_TASK_TAG, "malloc() failed; aborting.");
    vTaskDelete(NULL);
  }
  
  while(1) {
    // check status of COMMAND
    cmd_state = gpio_get_level(SIO_COMMAND);
    if(cmd_state != prev_cmd_state) {
      if(cmd_state == 0) {
        ESP_LOGI(SIO_TASK_TAG, "COMMAND is LOW");
      } else {
        ESP_LOGI(SIO_TASK_TAG, "COMMAND is HIGH");
      }
      prev_cmd_state = cmd_state;
    }
    
    // check for received data
    rx_bytes = uart_read_bytes(SIO_UART, rx_buf, SIO_RX_BUF_SIZE, 0);
    if(rx_bytes > 0) {
      rx_buf[rx_bytes] = 0;
      //ESP_LOGI(SIO_TASK_TAG, "Read %d bytes.", rx_bytes);
      ESP_LOG_BUFFER_HEXDUMP(SIO_TASK_TAG, rx_buf, rx_bytes, ESP_LOG_INFO);
    }
    vTaskDelay(1);   
  }  
}
