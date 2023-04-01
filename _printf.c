#include "main.h"
#include <unistd.h>

void print_buffer(char buffer[], int *buff_index);

/**
 * _printf - function
 * @format: format
 * Return: printed char
 */

int _printf(const char *format, ...)
{
	int just= 0;
	int printed = 0;
	int printed_chars = 0;
	int flags = 0;
	int width = 0;
	int precision = 0;
	int size = 0;
	int buff_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (just = 0; format && format[just] != '\0'; just++)
	{
		if (format[just] != '%')
		{
			buffer[buff_index++] = format[just];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
				
			
	
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &just);
			width = get_width(format, &just, list);
			precision = get_precision(format, &just, list);
			size = get_size(format, &just);
			++just;
			printed = handle_print(format, &just, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_index);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
