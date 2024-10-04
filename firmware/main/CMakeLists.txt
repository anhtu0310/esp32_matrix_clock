set(srcs
    "main.c"
    "matrix.c"
    "led_driver.c"
    "wifi_time.c"
    )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS ".")
