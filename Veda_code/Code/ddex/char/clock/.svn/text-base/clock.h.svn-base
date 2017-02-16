
/* clock.h -- definition of registers and commands to access RTC.
Version : 1.0
Author : Team -C
*/

# define RTC_PORT_BASE 0x70

# define RTC_DATA_PORT  0x71

# define RTC_CMD_PORT RTC_PORT_BASE

# define SECONDS_CMD 0
# define MINUTES_CMD 2
# define HOURS_CMD 4
# define DAY_CMD 7
# define MONTH_CMD 8
# define YEAR_CMD 9

/* cmd is SECONDS_CMD .... YEARS_CMD... */

# define READ_FROM_CLOCK(cmd,data)\
	outb_p(cmd,RTC_CMD_PORT);data=inb_p(RTC_DATA_PORT);

/* cmd is SECONDS_CMD .... YEARS_CMD... and value is the value to be set */
# define WRITE_TO_CLOCK(cmd,value) \
	outb_p(cmd,RTC_CMD_PORT); outb_p(value,RTC_DATA_PORT);


# define CLOCK_MAJOR 254

# define FILE_SIZE 6
