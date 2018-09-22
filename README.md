# ft_printf


```c
int    i;
char   *s;

i = 42;
s = "Hi";

ft_printf("%{BLUE}.4s %{RED}*.1d", s, 7, i);
```

### About

A 42 project dedicated to reimplement the famous libc function printf ([Project subject](ressources/ft_printf.en.pdf))

At 42 all C project must be developed like the [norme](ressources/norme.en.pdf) want to.



### Performance

I don't use heap memory allocation at all, i use a buffer on stack to minimize number of system calls when allocating and printing. Buffer size can change, the size is set in includes/ft_printf.h.

Around 20 percent faster than original version of printf without compiler optimization flag. (with clang and osx)

Some bonus flag added like color flags, float print engine, boolean print, memory print..

Otherwise libc function like strlen, memcpy.. were optimized for faster processing.


#### Marks. 112/100
