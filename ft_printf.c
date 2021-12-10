#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> // убрать

int	ft_putchar_fd(char c, int fd)
{
	static int	size;
	//int			tp_size;

	if (!size)
		size = 0;
	//if (c != '\0')
		write(fd, &c, 1);
	/*if (c == '\0')
	{
		tp_size = size;
		size = 0;
	}*/
	size++;
	return (size);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd_base_u(unsigned int nbr, int fd, unsigned int base, char upp_or_low)
{
	/*unsigned int	nbr;

	nbr = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(-nb);
	}
	else
		nbr = (unsigned int)nb;*/
	if (nbr >= base)
		ft_putnbr_fd_base_u(nbr / base, fd, base, upp_or_low);
	if (nbr % base < 10)
		ft_putchar_fd((char)(nbr % base + 48), fd);
	if (nbr % base >= 10)
	{
		if (upp_or_low == 'u')
			ft_putchar_fd((char)(nbr % base + 55), fd);
		if (upp_or_low == 'l')
			ft_putchar_fd((char)(nbr % base + 87), fd);
	}
}

void	ft_putnbr_fd_base(int nb, int fd, unsigned int base, char upp_or_low)
{
	unsigned int	nbr;

	nbr = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(-nb);
	}
	else
		nbr = (unsigned int)nb;
	if (nbr >= base)
		ft_putnbr_fd_base(nbr / base, fd, base, upp_or_low);
	if (nbr % base < 10)
		ft_putchar_fd((char)(nbr % base + 48), fd);
	if (nbr % base >= 10)
	{
		if (upp_or_low == 'u')
			ft_putchar_fd((char)(nbr % base + 55), fd);
		if (upp_or_low == 'l')
			ft_putchar_fd((char)(nbr % base + 87), fd);
	}
}

/*char hex_digit(int v) {
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10; // <-- Here
}*/

void print_address_hex(void* p0)
{
    int i;
    size_t p = (size_t)p0;
	char	*s;

	ft_putstr_fd("0x", 1);
	char *str = "0123456789abcdef";
	i = 0;

	s = malloc(20);

	while (p >= 16)
	{
		s[i] = str[p % 16];
		i++;
		//write(1, &str[p % 16], 1);
		p /= 16; 	
	}
	s[i] = str[p % 16];
	//write(1, &str[p % 16], 1);

	while (i >= 0)
	{
		ft_putchar_fd(s[i], 1);
		i--;
	}
	free(s);
    // ft_putchar_fd('0',1); ft_putchar_fd('x',1);
    // for(i = (sizeof(p) << 3) - 4; i>=0; i -= 4) {
        // ft_putchar_fd(hex_digit((p >> i) & 0xf),1);

    //}
}

/*
void	print_address_hex(size_t p)
{
	ft_putstr_fd("0x", 1);
	ft_putnbr_fd_base(p, 1, 16, 'l');
}*/

void	print_format(const char *format, va_list ap)
{
	//char	c;

	while (*format)
	{
		if (*format != '%')
			ft_putchar_fd(*format, 1);
		else
		{
			format++;
			if (*format == 'c')
			{
				ft_putchar_fd(va_arg(ap, int), 1);
				//c = (char) va_arg(ap, int);
				//write(1, &c, 1);
			}
			if (*format == 'i' || *format == 'd')
				ft_putnbr_fd_base(va_arg(ap, int), 1, 10, 'l');
			if (*format == 's')
				ft_putstr_fd(va_arg(ap, char *), 1);
			if (*format == '%')
				ft_putchar_fd('%', 1);
			if (*format == 'x')
				ft_putnbr_fd_base_u(va_arg(ap, int), 1, 16, 'l');
			if (*format == 'X')
				ft_putnbr_fd_base_u(va_arg(ap, int), 1, 16, 'u');
			if (*format == 'u')
				ft_putnbr_fd_base_u(va_arg(ap, unsigned int), 1, 10, 'l');
			if (*format == 'p')
				print_address_hex(va_arg(ap, void *));
		}
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	int			size;
	va_list		ap;

	size = 0;
	va_start(ap, format);
	print_format(format, ap);
	va_end(ap);
	size = ft_putchar_fd('\0', 1) - 1;
	return (size);
}
/*
int main() {
  char a= 'a';
  int i= 111;
  int j= -20;
  char *s="asd";
  int *p ;
  int size1= 0;
  int size2= 0;
   //size1 = ft_printf("12345%c67%i8%s%%%x121212%X1212\n", a, i,s,i,i);
   printf("size1= %i\n", size1);
   //size2 = printf("12345%c67%i8%s%%%x121212%X1212\n", a, i,s,i,i);
   printf("size2= %i\n", size2);
  //ft_printf("%p - moe\n", s);
  printf("%p - ego\n", s);

	size1 = printf(" %c %c %c 1\n", '0', 0, '1');
	size2 = ft_printf(" %c %c %c 1\n", '0', 0, '1');
	printf("size1= %i\n", size1);
	printf("size2= %i\n", size2);

	printf(" %x ", 9223372036854775807LL);

	size1 = printf(" %llx \n", 9223372036854775807LL);
	size2 = ft_printf(" %x \n", 9223372036854775807LL);
	printf("size1= %i\n", size1);
	printf("size2= %i\n", size2);
  return 0;
}
*/
