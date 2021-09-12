#include "header.h"

void thread_shifter(void)
{
	k_fifo_init(&printk_fifo);
	
	int index = 0;

	k_sem_init(&my_sem0, 0, 1);
	k_sem_init(&my_sem1, 0, 1);
	k_sem_init(&my_sem2, 0, 1);
	k_sem_init(&my_sem3, 0, 1);

	static int led_mode = 0;
	static int ctr = 0;
	while (1) {
		index++;
		index %= 4;

		if(++ctr % 4 == 0)
		{
			ctr = 0;
			led_mode++;
			led_mode %= 2;
		}
		switch(index)
		{
			case 0: k_sem_give(&my_sem0);break;
			case 1: k_sem_give(&my_sem1);break;
			case 2: k_sem_give(&my_sem2);break;
			case 3: k_sem_give(&my_sem3);break;
		}
		k_msleep(100);
	}
}

void blinkku(const struct led *led, struct k_sem *my_sem)
{
	int led_mode = 0;
	int ctr = 0;
	while(1)
	{
		if (k_sem_take(my_sem, K_MSEC(50)) != 0)
			continue;
	
		if(++ctr % 4 == 0)
		{
			ctr = 0;
			led_mode++;
			led_mode %= 2;
		}
		
		singleBlink(led, 250, 1, led_mode);
		k_sem_reset(my_sem);
	}
}