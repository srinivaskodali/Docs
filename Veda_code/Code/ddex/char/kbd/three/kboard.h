/* definition of ports and other constants required by kboard driver
Version : 1.0
Author : team -C
*/
# define KBOARD_BASE_PORT 0x60
# define KBOARD_DATA_PORT KBOARD_BASE_PORT
# define KBOARD_STATUS_REG KBOARD_BASE_PORT + 0x4 /* for reading status */
# define KBOARD_CTL_REG KBOARD_BASE_PORT + 0x4 /* for writing commands */

/* commands for keyboard */

# define KB_SELFTEST_CMD  0xAA
# define KB_ENABLE_CMD  0xAE
# define KB_DISABLE_CMD  0xAD

/* status bits */

# define KB_TEST_SUCC  0x04


# define read_kbd_input()  inb(KBOARD_DATA_PORT)

# define read_kbd_status()  inb(KBOARD_STATUS_REG)

# define write_kbd_command(cmd)  outb(cmd,KBOARD_CTL_REG)

# define write_kbd_output(data)  outb(data,KBOARD_DATA_PORT)

