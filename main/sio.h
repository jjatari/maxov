#ifndef MINI850_SIO_H
#define MINI850_SIO_H

#define SIO_BAUD_RATE      19200
#define SIO_RX_BUF_SIZE    1024
#define SIO_UART           (UART_NUM_2)

typedef struct {
  uint8_t device;
  uint8_t command;
  uint8_t aux1;
  uint8_t aux2;
} sio_command_t;

esp_err_t sio_init();
void sio_task();

#endif
