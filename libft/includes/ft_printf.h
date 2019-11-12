/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:28:34 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <float.h>

/*
** fl1 == '+'
** fl2 == '-'
** fl3 == '0'
** fl4 == '#'
** fl5 == ' '
**   t == '.'
*/

typedef struct		s_flags
{
	char			fl1;
	char			fl2;
	char			fl3;
	char			fl4;
	char			fl5;
	char			t;
	int				width;
	int				precision;
	char			dlina;
	char			spec;
	int				sign;
	int				counter;
	int				procent;
	int				re;
	int				help;
	int				y;
	int				j;
}					t_flags;

typedef struct		s_float
{
	int				accur;
	long long int	i;
	long long int	x;
	int				y;
	int				c;
	int				c1;
	int				len;
}					t_f;

/*
**------------ft_printf.c/printf2.c + putchar1/str1---------------------------->
*/
int					ft_printf(const char *format, ...);
int					ft_ifproc(const char **format, t_flags *all, va_list args);
int					ft_doubleproc(t_flags *all, const char **format);
int					ft_divisionproc(t_flags *all);
int					ft_nullspec(const char **format, t_flags *all);
void				ft_nullspecplus(t_flags *all);
int					ft_putchar1(char c, t_flags *all);
void				ft_putstr1(const char *str, t_flags *all);
/*
**-------------ft_checprocent.c------------------------------------------------>
*/
int					ft_checkproc(const char **format, t_flags *all);
void				ft_bzero2(t_flags *s);
void				ft_typesflags(const char **format, t_flags *all);
int					ft_width(const char *format);
void				ft_dlina(const char **format, t_flags *all);
/*
**-------------ft_help.c------------------------------------------------>
*/
int					ft_len(const char *format);
int					dlwidth(long int a);
int					dlwidtho(unsigned long int a);
char				*ft_itoa_base16(unsigned long int value, int base, int f);
int					dlwidthu(unsigned long int a);
/*
**-------------ft_checkstruct.c------------------------------------------------>
*/
int					ft_checkstruct(va_list args, t_flags *all);
/*
**-------------ft_decimal.c/decimalmin.c--------------------------------------->
*/
int					ft_decimal(va_list args, t_flags *all);
void				ft_preclessthanyx(int z, int y, long int x, t_flags *all);
void				ft_precmorethanyx(int z, int y, long int x, t_flags *all);
void				ft_xpreclessthany(int z, int y, long int x, t_flags *all);
void				ft_xprecmorethany(int z, int y, long int x, t_flags *all);

int					ft_decimalmin(va_list args, t_flags *all);
void				ft_dminprecmorethanyx(int y, long int x, t_flags *all);
void				ft_dminpreclessthanyx(int z, long int x, t_flags *all);
void				ft_xdminprecmorethany(int y, long int x, t_flags *all);
void				ft_xdminpreclessthany(int y, long int x, t_flags *all);

void				ft_dinintialx(long int *x, t_flags *all, va_list args);
void				ft_decimalhelp(const long int *x, int *y, t_flags *all);
void				ft_putnbrplus(long nb, t_flags *all);
void				ft_putnbrlong(long int nb, t_flags *all);
/*
**-------------ft_odecimal------------------------------------------------>
*/
int					ft_odecimal(va_list args, t_flags *all);
unsigned long int	ft_atoio(const char *str);
void				ft_odecpreclessy(unsigned long x, int z, t_flags *all);
void				ft_odecnott(unsigned long x, int z, char *v, t_flags *all);
void				ft_odecprecovery(unsigned long x, int z, t_flags *all);

int					ft_odecimalmin(va_list args, t_flags *all);
void				ft_oinitialx(unsigned long *x, t_flags *all, va_list args);
void				ft_odecminprecovery(unsigned int x, int y, t_flags *all);
void				ft_odecminpreclessy(unsigned int x, int z, t_flags *all);
void				ft_putnbro(unsigned long int n, t_flags *all);
/*
**-------------ft_udecimal.c/udecimalmin.c------------------------------------->
*/
int					ft_udecimal(va_list args, t_flags *all);
void				ft_uinitialx(unsigned long *x, t_flags *all, va_list args);
void				ft_udecpreclessy(unsigned long x, int y, int z,
t_flags *all);
void				ft_udecprecovery(unsigned long x, int y, int z,
t_flags *all);

int					ft_udecimalmin(va_list args, t_flags *all);
void				ft_udecminprecovery(unsigned int x, int y, t_flags *all);
void				ft_udecminpreclessy(unsigned long int x, int z,
t_flags *all);
void				ft_putnbru(unsigned long int nb, t_flags *all);
/*
**-------------ft_xhex.c/xhexmin.c/xhexx.c/xhexxmin.c-------------------------->
*/
int					ft_xhex(va_list args, t_flags *all);
void				ft_xxinitialx(unsigned long *x, t_flags *all, va_list args);
void				ft_xwitht(unsigned long x, int i, char *s, t_flags *all);
void				ft_xnotwidth(unsigned long x, int i, char *s, t_flags *all);

int					ft_xhexmin(va_list args, t_flags *all);
void				ft_xminwitht(unsigned long x, int i, char *s, t_flags *all);
void				ft_xminnot(unsigned long x, char *s, t_flags *all);

int					ft_xhexx(va_list args, t_flags *all);
void				ft_xxwitht(unsigned long x, int i, char *s, t_flags *all);
void				ft_xxnotwidth(unsigned long x, int i, char *s,
t_flags *all);

int					ft_xhexxmin(va_list args, t_flags *all);
void				ft_xxminwitht(unsigned long x, int i, char *s,
t_flags *all);
void				ft_xxminnot(unsigned long x, char *s, t_flags *all);
/*
**-------------ft_string.c/string2.c------------------------------------------->
*/
int					ft_str(va_list args, t_flags *all);
void				ft_strwitht(char *s, char *d, int i, t_flags *all);
void				ft_strwithoutt(char *s, char *d, int i, t_flags *all);

int					ft_strplus(va_list args, t_flags *all);
void				ft_strpluswitht(char *s, char *d, int i, t_flags *all);
void				ft_strpluswithoutt(char *s, char *d, int i, t_flags *all);
/*
**-------------ft_char.c------------------------------------------------------->
*/
int					ft_charc(va_list args, t_flags *all);
/*
**-------------ft_pointer.c---------------------------------------------------->
*/
int					ft_point(va_list args, t_flags *all);
char				*ft_itoa_base(long long int value, int base);
size_t				digit_count(unsigned long nb, int base);
void				ft_pwithfl2(char *f, unsigned int i, t_flags *all);
void				ft_pwithoutfl2(char *f, unsigned int i, long long x,
t_flags *all);
/*
**-------------ft_float.c/float2.c/float3.c------------------------------------>
*/
int					ft_float(va_list args, t_flags *all);
void				ft_finitialx(t_f *f, t_flags *all, long double *xx,
va_list args);
void				ft_fineedmorespace(t_f *f, long double *n, long double *xx,
t_flags *all);
long double			ft_sign2nol2(double t, t_flags *all, t_f *f);
void				ft_fcelayachast(t_f *f, char *v, const long double *xx);
void				ft_formiruemmassiv(t_f *f, long double *n, char *v);
void				ft_fnotninelastnum(t_f *f, t_flags *all, char *v);
t_flags				*config2(t_flags *all, char *v);
int					ft_flplus2(t_flags *all, char *v);
int					ft_flminus2(t_flags *all, char *v);
void				ft_fninelastnum(t_f *f, t_flags *all, char *v);
void				ft_fthreeother(t_flags *all, char *v);
/*
**-------------ft_floatprecnull1/2/3.c----------------------------------------->
*/
int					ft_precnull(t_flags *all, double d);
int					ft_lastnum(double a);
int					ft_sign(double t);
long long int		ft_nolnolnol(double t, int lastnum);
t_flags				*config(t_flags *all, int *counter, long long int i);
int					dlwidthfloat(long long int a);
int					ft_flminus(t_flags *all, long long int i, int count);
void				ft_putnbrfloat(long long int nb, t_flags *all);
int					ft_flplus(t_flags *all, long long int i, int count);
/*
**-------------dop_func-------------------------------------------------------->
*/
void				ft_checkspec(t_flags *all, const char **format);
void				ft_flagstr(const char **format, t_flags *all);
int					ft_whileee(const char **format);

#endif
