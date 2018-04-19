#ifndef MINI850_PINS_H
#define MINI850_PINS_H

#define SIO_DATA_OUT    (GPIO_NUM_16)
#define SIO_DATA_IN     (GPIO_NUM_17)
#define SIO_COMMAND     (GPIO_NUM_34)
#define SIO_PROCEED     (GPIO_NUM_15)
#define SIO_INTERRUPT   (GPIO_NUM_25)
#define SIO_READY       (GPIO_NUM_26)

// SIM: 4->34, 16->33, 17->32
#define SIM_DATA_OUT    (GPIO_NUM_33)
#define SIM_DATA_IN     (GPIO_NUM_32)
#define SIM_COMMAND     (GPIO_NUM_4)

#endif
