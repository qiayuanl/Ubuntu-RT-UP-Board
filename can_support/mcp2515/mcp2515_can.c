#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/can/platform/mcp251x.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

int can0_int = 27;
int can1_int = 22;

// module_param(busnum, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// MODULE_PARM_DESC(busnum, "busnum of spi bus to use");

// module_param(gpio_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// MODULE_PARM_DESC(gpio_int, "linux gpio number of INT gpio");

// module_param(chip_select, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// MODULE_PARM_DESC(chip_select, "spi chip select");

int can0_requested = 0;
int can1_requested = 0;

struct spi_device *can0, *can1;
static struct mcp251x_platform_data mcp251x_info = {
    .oscillator_frequency = 16000000,
};

static struct spi_board_info spi_device_info = {
    .modalias = "mcp2515",
    .platform_data = &mcp251x_info,
    .irq = -1,
    .max_speed_hz = 8 * 1000 * 1000,
};

static int __init mcp2515_init(void)
{
  int ret0, ret1;
  struct spi_master *master;

  printk("mcp2515_can: init.\n");

  spi_device_info.bus_num = 2;
  master = spi_busnum_to_master(spi_device_info.bus_num);
  if (!master)
  {
    printk("mcp2515_can: MASTER not found.\n");
    return -ENODEV;
  }

  ///////////////can0///////////////
  ret0 = gpio_request(can0_int, "sysfs");

  if (ret0)
  {
    printk("mcp2515_can: could not request gpio %d\n", can0_int);
    gpio_free(can0_int);
    return ret0;
  }
  can0_requested = 1;

  gpio_direction_input(can0_int);

  ret0 = gpio_to_irq(can0_int);
  printk("mcp2515_can: irq for pin %d is %d\n", can0_int, ret0);
  spi_device_info.irq = ret0;
  spi_device_info.chip_select = 0;

  // create a new slave device, given the master and device info
  can0 = spi_new_device(master, &spi_device_info);

  if (!can0)
  {
    printk("mcp2515_can: FAILED to create slave.\n");
    ret0 = -ENODEV;
    goto error_postcan0;
  }

  printk("mcp2515_can: CAN0 created!\n");

  ///////////////can1///////////////
  ret1 = gpio_request(can1_int, "sysfs");

  if (ret1)
  {
    printk("mcp2515_can: could not request gpio %d\n", can1_int);
    gpio_free(can1_int);
    return ret1;
  }
  can1_requested = 1;

  gpio_direction_input(can1_int);

  ret1 = gpio_to_irq(can1_int);
  printk("mcp2515_can: irq for pin %d is %d\n", can1_int, ret1);
  spi_device_info.irq = ret1;
  spi_device_info.chip_select = 1;

  // create a new slave device, given the master and device info
  can1 = spi_new_device(master, &spi_device_info);

  if (!can1)
  {
    printk("mcp2515_can: FAILED to create slave.\n");
    ret1 = -ENODEV;
    goto error_postcan1;
  }

  printk("mcp2515_can: CAN1 created!\n");

  return 0;

error_postcan0:
  gpio_free(can0_int);
  return ret0;
error_postcan1:
  gpio_free(can1_int);
  return ret1;
}

static void __exit mcp2515_exit(void)
{
  printk("mcp2515_can: exit\n");

  if (can0)
  {
    spi_unregister_device(can0);
  }
  if (can0_requested)
    gpio_free(can0_int);
  if (can1)
  {
    spi_unregister_device(can1);
  }
  if (can1_requested)
    gpio_free(can1_int);
}

module_init(mcp2515_init);
module_exit(mcp2515_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QiayuanLiao");
MODULE_DESCRIPTION("MCP2515 CAN module");