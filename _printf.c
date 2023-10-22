#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, &buffer[0], *buff_ind);
        *buff_ind = 0;
    }
}

/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    if (format == NULL)
        return (-1);

    va_list args;
    va_start(args, format);

    int printed_chars = 0;
    int buffer_index = 0;
    char buffer[BUFF_SIZE];

    for (int i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buffer_index++] = format[i];
            if (buffer_index == BUFF_SIZE)
                print_buffer(buffer, &buffer_index);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buffer_index);

            int flags = get_flags(format, &i);
            int width = get_width(format, &i, args);
            int precision = get_precision(format, &i, args);
            int size = get_size(format, &i);
            i++;

            int printed = handle_print(format, &i, args, buffer,
                                       flags, width, precision, size);
            if (printed == -1)
            {
                va_end(args);
                return (-1);
            }
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buffer_index);

    va_end(args);
    return (printed_chars);
}

