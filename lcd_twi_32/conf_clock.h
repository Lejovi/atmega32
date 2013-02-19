/*
 * conf_clock.h
 *
 * Created: 16-7-2011 22:07:14
 *  Author: ljv
 */ 


#ifndef CONF_CLOCK_H_
#define CONF_CLOCK_H_

// brief Maximum possible delay is 262.14 ms / F_CPU in MHz.
#define MAX_MS_DELAY (262.14 / (F_CPU / 1000000UL))

// brief Maximum possible delay is 768 us / F_CPU in MHz.
#define MAX_US_DELAY (768 / (F_CPU / 1000000UL))

#endif /* CONF_CLOCK_H_ */