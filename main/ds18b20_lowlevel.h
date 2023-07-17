#ifndef HEADER_DS18B20_H
#define HEADER_DS18B20_H

void ds18b20_init(u_int8_t pin);
float ds18b20_cmd_read_temp();

#endif