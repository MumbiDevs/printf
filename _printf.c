#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: The buffer containing characters to be printed
 * @buff_ind: Pointer to the buffer index
 */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];

			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);

			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);

			i++;
			printed = handle_print(format, &i, list, buffer,
						flags, width, precision, size);

			if (printed == -1)
				return (-1);

			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer and resets the index
 * @buffer: The buffer containing characters to be printed
 * @buff_ind: Pointer to the buffer index
 */
void print_buffer(char buffer[], int *buff_ind)
{
	int i;

	for (i = 0; i < *buff_ind; i++)
	{
		/* Use the appropriate method to print the character */
		_putchar(buffer[i]);
	}

	*buff_ind = 0;
}
