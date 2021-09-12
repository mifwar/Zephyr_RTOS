/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <stdlib.h>
#include <device.h>
#include <string.h>
#include <sys/util.h>
#include <inttypes.h>
#include <sys/printk.h>
#include <drivers/gpio.h>
#include <sys/__assert.h>
#include <drivers/uart.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

#define PRIORITY_1 1
#define PRIORITY_2 2
#define PRIORITY_3 3
#define PRIORITY_4 4

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

extern struct k_sem my_sem0;
extern struct k_sem my_sem1;
extern struct k_sem my_sem2;
extern struct k_sem my_sem3;
extern struct k_fifo printk_fifo;
extern const struct device *uart_dev;

struct led {
	struct gpio_dt_spec spec;
	const char *gpio_pin_name;
};

struct printk_data_t {
	void *fifo_reserved; /* 1st word reserved for use by fifo */
	uint32_t led;
	uint32_t cnt;
};

static const struct led led0 = {
	.spec = GPIO_DT_SPEC_GET_OR(LED0_NODE, gpios, {0}),
	.gpio_pin_name = DT_PROP_OR(LED0_NODE, label, ""),
};

static const struct led led1 = {
	.spec = GPIO_DT_SPEC_GET_OR(LED1_NODE, gpios, {0}),
	.gpio_pin_name = DT_PROP_OR(LED1_NODE, label, ""),
};

static const struct led led2 = {
	.spec = GPIO_DT_SPEC_GET_OR(LED2_NODE, gpios, {0}),
	.gpio_pin_name = DT_PROP_OR(LED2_NODE, label, ""),
};

static const struct led led3 = {
	.spec = GPIO_DT_SPEC_GET_OR(LED3_NODE, gpios, {0}),
	.gpio_pin_name = DT_PROP_OR(LED3_NODE, label, ""),
};

void thread_shifter(void);
void blinkku(const struct led *led, struct k_sem *my_sem);
void singleBlink(const struct led *led, uint32_t sleep_ms, uint32_t id, int led_value);
