#include "header.h"

K_THREAD_DEFINE(t_blinkku0      , STACKSIZE, blinkku       , &led0, &my_sem0, NULL, PRIORITY_1, 0, 0);
K_THREAD_DEFINE(t_blinkku1      , STACKSIZE, blinkku       , &led1, &my_sem1, NULL, PRIORITY_1, 0, 0);
K_THREAD_DEFINE(t_blinkku2      , STACKSIZE, blinkku       , &led2, &my_sem2, NULL, PRIORITY_1, 0, 0);
K_THREAD_DEFINE(t_blinkku3      , STACKSIZE, blinkku       , &led3, &my_sem3, NULL, PRIORITY_1, 0, 0);
K_THREAD_DEFINE(t_thread_shifter, STACKSIZE, thread_shifter, NULL , NULL    , NULL, PRIORITY  , 0, 0);