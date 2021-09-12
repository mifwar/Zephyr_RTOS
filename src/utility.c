#include "header.h"

struct k_fifo printk_fifo;

struct k_sem my_sem0;
struct k_sem my_sem1;
struct k_sem my_sem2;
struct k_sem my_sem3;

void singleBlink(const struct led *led, uint32_t sleep_ms, uint32_t id, int led_value)
{
	const struct gpio_dt_spec *spec = &led->spec;
	int ret;

	if (!device_is_ready(spec->port)) {
		printk("Error: %s device is not ready\n", spec->port->name);
		return;
	}

	ret = gpio_pin_configure_dt(spec, GPIO_OUTPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure pin %d (LED '%s')\n",
			ret, spec->pin, led->gpio_pin_name);
		return;
	}

	gpio_pin_set(spec->port, spec->pin, led_value);

	struct printk_data_t tx_data = { .led = id, .cnt = led_value};

	size_t size = sizeof(struct printk_data_t);
	char *mem_ptr = k_malloc(size);
	__ASSERT_NO_MSG(mem_ptr != 0);

	memcpy(mem_ptr, &tx_data, size);

	k_fifo_put(&printk_fifo, mem_ptr);
	struct printk_data_t *rx_data = k_fifo_get(&printk_fifo, K_FOREVER);
	k_free(rx_data);

	k_msleep(sleep_ms);
}